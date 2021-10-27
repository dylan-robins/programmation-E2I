#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <time.h>
#include "processPool.h"

#define min(a, b) a < b ? a : b

static void run_sleep() {
    time_t t;
    srand((unsigned) time(&t) + getpid());
    
    char sleepTime[512];
    double randTime = rand() * 3.0f / RAND_MAX;
    
    sprintf(sleepTime, "%f", randTime);
    
    printf("Running '/bin/sleep %s'\n", sleepTime);
    execlp("/bin/sleep", "/bin/sleep", sleepTime, NULL);
}

static void run_grep(char* path, char* pattern) {
    printf("Running '/bin/grep -HnT --color=always %s %s'\n", pattern, path);
    execlp("/bin/grep", "/bin/grep", "-HnT", "--color=always", pattern, path, NULL);
}

void mgrep(int nbPaths, char** paths, char* pattern, int nbProcs) {
    processPool* pp = newProcessPool(nbProcs);
    printf("Created process pool:\n");
    printf("    - Capacity = %ld\n", pp->capacity);
    printf("    - Size = %ld\n", pp->size);        
    printf("    - PIDs = %p\n", (void *) pp->pids);        

    while (*paths != NULL) {
        int slotID = reserveProcessPoolSlot(pp);
        if (slotID == 0) {
            run_grep(paths[0], pattern);
            // run_sleep();
            exit(0);
        }
        // move to the next path
        paths++;
    }
    waitForProcessesInPool(pp);
    deleteProcessPool(pp);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("Error: incorrect number of arguments!\n");
        printf("Usage: %s pattern file1 [file2 file3...]\n", argv[0]);
        exit(1);
    }

    int nbProcs = get_nprocs();

    int nbPaths = argc - 3;
    char* pattern = argv[1];
    char** searchPaths = &(argv[2]);

    mgrep(nbPaths, searchPaths, pattern, nbProcs);

    return 0;
}