// fprintf(), printf(), fopen(), fclose(), fgetc(), FILE *
#include <stdio.h>
// exit()
#include <stdlib.h>
// strcmp()
#include <string.h>
// isspace()
#include <ctype.h>

#define MAX_LEN 1024 // maximum length of a filename

typedef enum {ARG_NUM, NO_TARGET, BAD_OPT} error_t;

typedef enum {WORD, CHAR, LINE} cmode_t;

void error(error_t err) {
    switch (err)
    {
    case ARG_NUM:
        fprintf(stderr, "Error: incorrect number of arguments\n");
        fprintf(stderr, "Usage: my_wc <mode (optional)> <file> \n");
        fprintf(stderr, "Modes: w (word count), c (character count), l (line count). Default is w.\n");
        exit(1);
    
    case NO_TARGET:
        fprintf(stderr, "Error: file doesn't exist (check path and permissions)\n");
        exit(2);

    case BAD_OPT:
        fprintf(stderr, "Error: unknown mode\n");
        exit(3);

    default:
        break;
    }
}

long countChars(char *filename) {
    FILE *f;
    long nbChars = 0;

    f = fopen(filename, "r");
    if (f == NULL) {error(NO_TARGET);}
    
    fgetc(f);
    while (!feof(f)) {
        nbChars++;
        fgetc(f);
    }
    fclose(f);
    return nbChars;
}

long countWords(char *filename) {
    FILE *f;
    long nbWords = 0;
    char c;

    f = fopen(filename, "r");
    if (f == NULL) {error(NO_TARGET);}

    // read the first character
    c = fgetc(f);
    while (!feof(f)) {
        // skip until the end of the word
        while (!isspace(c) && !feof(f)) {
            c = fgetc(f);
        }
        nbWords++;
        // don't count while we've got whitespace
        while (isspace(c) && !feof(f)) {
            c = fgetc(f);
        }
    }
    fclose(f);
    return nbWords;
}

long countLines(char *filename) {
    FILE *f;
    long nbLines = 0;
    char c;

    f = fopen(filename, "r");
    if (f == NULL) {error(NO_TARGET);}

    while (!feof(f)) {
        c = fgetc(f);
        if (c == '\n') {
            nbLines++;
        }
    }
    fclose(f);
    return nbLines;
}

int main(int argc, char **argv) {
    cmode_t mode;
    char *filename;

    // set the mode and filename pointer according to the commandline args
    if (argc != 3 && argc != 2) {
        error(ARG_NUM);
    } else if (argc == 2) {
        mode = WORD;
        filename = argv[1];
    } else if (strcmp(argv[1], "l") == 0) {
        mode = LINE;
        filename = argv[2];
    } else if (strcmp(argv[1], "c") == 0) {
        mode = CHAR;
        filename = argv[2];
    } else if (strcmp(argv[1], "w") == 0) {
        mode = WORD;
        filename = argv[2];
    } else {
        error(BAD_OPT);
    }

    // Depending on what mode was set, run different functions
    switch (mode) {
    case WORD:
        printf("Number of words: %ld\n", countWords(filename));
        break;
    
    case LINE:
        printf("Number of lines: %ld\n", countLines(filename));
        break;
    
    case CHAR:
        printf("Number of characters: %ld\n", countChars(filename));
        break;
    }

    return 0;
}