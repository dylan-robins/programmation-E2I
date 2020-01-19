#include <stdio.h>
#include <string.h>

typedef enum {
    PDF
} file_type;

int is_filetype(FILE *f, file_type filetype) {
    // read file's magic number:
    char mgknum[6];
    mgknum[5] = '\0';
    for (int i = 0; i < 5; i++) {
        mgknum[i] = fgetc(f);
    }
    // check magic number against filetype's one
    switch (filetype)
    {
    case PDF:
        return strcmp(mgknum, "%PDF-") == 0;
        break;
    default:
        return 0;
    }
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Error, incorrect number of arguments\n");
        fprintf(stderr, "Usage: %s <inputfile> <filetype>\n", argv[0]);
        return 1;
    }

    // Parse file type
    file_type type;
    if (strcmp(argv[2], "pdf") || strcmp(argv[2], "PDF")) {
        type = PDF;
    } else {
        fprintf(stderr, "Error, unsupported file type %s\n", argv[2]);
        return 2;
    }

    // open file
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "Error, unable to open file %s. Please check the filename and permissions.\n", argv[1]);
        return 3;
    }

    // check file type and print result
    if (is_filetype(f, type)) {
        printf("Yes, %s is a %s file.\n", argv[1], argv[2]);
    } else {
        printf("No, %s is not a %s file.\n", argv[1], argv[2]);
    }

    // close file and exit
    fclose(f);
    return 0;
}