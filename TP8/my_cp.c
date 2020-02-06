#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_LEN 1024 // maximum length of a filename

typedef enum {ARG_NUM, NO_TARGET, NO_SRC, SRC_NOT_REG, TOO_MANY_FILES, TARGET_NULL} error_t;

void error(error_t err) {
    switch (err)
    {
    case ARG_NUM:
        fprintf(stderr, "Error: incorrect number of arguments\n");
        fprintf(stderr, "Usage: my_cp <source_1> <source_2>... <destination>\n");
        exit(1);
    
    case NO_TARGET:
        fprintf(stderr, "Error: target directory doesn't exist (check path and permissions)\n");
        exit(2);

    case NO_SRC:
        fprintf(stderr, "Error: source file doesn't exist (check path and permissions)\n");
        exit(3);

    case SRC_NOT_REG:
        fprintf(stderr, "Error: can only copy regular files\n");
        exit(4);

    case TOO_MANY_FILES:
        fprintf(stderr, "Error: multiple sources provided but target isn't a directory\n");
        exit(5);

    case TARGET_NULL:
        fprintf(stderr, "Error: target path couldn't be opened (ran out of space?)\n");
        exit(6);

    default:
        break;
    }
}

void fcopy(const char *target, const char *source) {
    // open files and copy byte by byte
    FILE *f_in = fopen(source, "r");
    FILE *f_out = fopen(target, "w");

    if (f_in == NULL) {error(NO_SRC);} // should never happen because we've check it beforehand
    if (f_out == NULL) {error(TARGET_NULL);}

    while (!feof(f_in))
    {
        fputc(fgetc(f_in), f_out);
    }
    
    fclose(f_in);
    fclose(f_out);
}

int main(int argc, char **argv) {
    struct stat source_stats;
    struct stat target_stats;
    char target_name[MAX_LEN];

    if (argc < 3) {
        error(ARG_NUM);
    } else {
        // check existance of all source files
        for (int i = 1; i < argc-1; i++) {
            if (access(argv[i], F_OK) != 0) {
                error(NO_SRC);
            } else {
                // make sure we're only copying files and not dirs or fifos etc
                stat(argv[1], &source_stats);
                if (!S_ISREG(source_stats.st_mode)) {
                    error(SRC_NOT_REG);
                }
            }
        }
    }

    if (argc == 3) {
        // if only one source file and target is a directory, copy source inside it
        stat(argv[2], &target_stats);
        if (access(argv[2], F_OK) == 0 && S_ISDIR(target_stats.st_mode)) {
            // build target name
            strcpy(target_name, argv[2]);
            strcat(target_name, "/");
            strcat(target_name, argv[1]);

            // copy the file to the target
            fcopy(target_name, argv[1]);
        } else {
            // otherwise overwrite (or create) the target with the source file
            fcopy(argv[2], argv[1]);
        }
    } else {
        // if several source files, target must be a directory
        stat(argv[argc-1], &target_stats);
        if (access(argv[argc-1], F_OK) != 0 || !S_ISDIR(target_stats.st_mode)) {
            error(NO_TARGET);
        }
        // copy all sources to identically named files in target directory
        for (int i = 1; i < argc-1; i++) {
            // build this target's filename = targetDirectory/basename(source)
            strcpy(target_name, argv[argc-1]);
            strcat(target_name, "/");
            strcat(target_name, basename(argv[i]));

            // copy the file to the target
            fcopy(target_name, argv[i]);
        }
    }
    
    return 0;

}