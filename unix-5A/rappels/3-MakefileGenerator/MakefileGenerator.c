#include <stdio.h>
#include <stdlib.h>
#include "stringArray.h"


stringArray * readPrograms() {
    printf("Enter a list of programs to build (one per line)\n");
    return readStrings();
}

stringArray * readSourceFiles(char * programName) {
    printf("Enter a list of source files needed to build %s (one per line)\n", programName);
    return readStrings();
}

void generateMakefileHeader(FILE * makefile, stringArray * programs) {
    fprintf(makefile, "BUILD_DIR := ./build\n");
    fprintf(makefile, "OBJ_DIR := ./build/obj\n");

    fprintf(makefile, "$(BUILD_DIR):\n\tmkdir -p $(BUILD_DIR)\n");
    fprintf(makefile, "$(OBJ_DIR):\n\tmkdir -p $(OBJ_DIR)\n");
    fprintf(makefile, "clean:\n\trm -rf $(BUILD_DIR)\n");

    fprintf(makefile, "all:");
    for (unsigned int i = 0; i < programs->count; i++) {
        fprintf(makefile, " $(BUILD_DIR)/%s", programs->strings[i]);
    }
    fprintf(makefile, "\n");
    fprintf(makefile, ".PHONY: all clean\n");
    fprintf(makefile, "\n");
    fprintf(makefile, "$(OBJ_DIR)/%%.o: %%.c\n");
    fprintf(makefile, "\tgcc -c -o $@ $<\n");
}

void generateMakefileBody(FILE * makefile, stringArray * programs, stringArray ** programSourceCode) {
    for (unsigned int i = 0; i < programs->count; i++) {
        fprintf(makefile, "$(BUILD_DIR)/%s:", programs->strings[i]);
        for (unsigned int j = 0; j < programSourceCode[i]->count; j++) {
            fprintf(makefile, " $(OBJ_DIR)/%s.o", programSourceCode[i]->strings[j]);
        }
        fprintf(makefile, "\n");
        fprintf(makefile, "\tgcc -o %s $^\n", programs->strings[i]);
    }
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        printf("Usage: %s path_to_makefile\n", argv[0]);
        return 1;
    }

    // Commencer par lire la liste des executables à créer
    stringArray * programs = readPrograms();

    // Allouer une liste de stringArray pour contenir les fichiers source de chaque programme
    stringArray ** programSourceCode = (stringArray **) malloc(programs->count * sizeof(stringArray *));
    
    for (unsigned int i = 0; i < programs->count; i++) {
        programSourceCode[i] = readSourceFiles(programs->strings[i]);
    }

    FILE * makefile = fopen(argv[1], "w");

    generateMakefileHeader(makefile, programs);
    generateMakefileBody(makefile, programs, programSourceCode);

    fclose(makefile);

    deleteStringArray(programs);
    
    return 0;
}