#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

static void run_grep(char * path, char * pattern) {
    execle("/bin/grep", "/bin/grep", "-HnT", "--color=always", pattern, path, NULL);
    exit(0);
}

void mgrep(int nbPaths, char ** paths, char * pattern) {
    int * childrenPIDs = malloc(nbPaths * sizeof(int));

    for (int pathIndex = 0; pathIndex <= nbPaths; pathIndex++) {
        int pid = fork();
        if (pid == 0) {
            run_grep(paths[pathIndex], pattern);
        } else {
            childrenPIDs[pathIndex] = pid;
        }
    }

    for (int pathIndex = 0; pathIndex <= nbPaths; pathIndex++) {
        waitpid(childrenPIDs[pathIndex], NULL, 0);
    }
    
    free(childrenPIDs);
}

int main(int argc, char ** argv) {
    if (argc < 3) {
        printf("Error: incorrect number of arguments!\n");
        printf("Usage: %s pattern file1 [file2 file3...]\n", argv[0]);
        exit(1);
    }
    
    int nbPaths = argc - 3;
    char * pattern = argv[1];
    char ** searchPaths = &(argv[2]);

    mgrep(nbPaths, searchPaths, pattern);
    
    return 0;
}