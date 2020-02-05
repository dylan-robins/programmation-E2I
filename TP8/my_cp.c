#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LEN 1024 // maximum length of a filename

typedef enum {ARG_NUM, NO_TARGET, NO_SRC, TOO_MANY_FILES} error_t;

void error(error_t err) {
    switch (err)
    {
    case ARG_NUM:
        fprintf(stderr, "Error: incorrect number of arguments\n");
        fprintf(stderr, "Usage: my_cp <source_1> <source_2>... <destination>\n");
        exit(1);
    
    case NO_TARGET:
        fprintf(stderr, "Error: target file doesn't exist (check path and permissions)\n");
        exit(2);

    case NO_SRC:
        fprintf(stderr, "Error: source file doesn't exist (check path and permissions)\n");
        exit(3);

    case TOO_MANY_FILES:
        fprintf(stderr, "Error: multiple sources provided but target isn't a directory\n");
        exit(4);

    default:
        break;
    }
}

void fcopy(const char *target, const char *source) {
    // open files and copy byte by byte
    FILE *f_in = fopen(source, "r");
    FILE *f_out = fopen(target, "w");

    while (!feof(f_in))
    {
        fputc(fgetc(f_in), f_out);
    }
    
    fclose(f_in);
    fclose(f_out);
}

int main(int argc, char **argv) {
    int target;
    struct stat target_stats;
    char target_name[MAX_LEN];

    if (argc < 3) {
        error(ARG_NUM);
    }

    // open target and read it's stats
    target = open(argv[argc-1], O_RDONLY);
    if (target == -1) {
        // if target doesn't exist and will be a directory, create it
        // no need to create a file, it will be created on opening for writing
        if (argc != 3) {
            mkdir(argv[argc-1], 0700);
        }
    } else {
        // read the targets stats
        fstat(target, &target_stats);
    }

    // check if target is file or directory
    if (S_ISDIR(target_stats.st_mode)) {
        // if target is directory, copy all sources to identically named files in target directory
        for (int i = 1; i < argc-1; i++) {
            // build target name
            strcpy(target_name, argv[argc-1]);
            strcat(target_name, "/");
            strcat(target_name, argv[i]);

            // copy the file to the target
            fcopy(target_name, argv[i]);
        }
    } else if (S_ISREG(target_stats.st_mode)) {
        if (argc == 3) {
            // if target is a regular file and only one source
            fcopy(argv[2], argv[1]);
        } else {
            // can't copy multiple files to the same target
            error(TOO_MANY_FILES);
        }
    } else 

    return 0;

}