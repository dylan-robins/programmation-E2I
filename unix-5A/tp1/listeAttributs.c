#include <stdio.h>
#include <stdlib.h>
#include "printInodeStats.h"

void usage(char * progName) {
    printf("Usage: '%s inode_name'\n", progName);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Nombre incorrect d'arguments!\n");
        usage(argv[0]);
        exit(1);
    }

    printInodeStats(argv[1]);

    
    return 0;
}