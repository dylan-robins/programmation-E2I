#include "processPool.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

processPool* newProcessPool(size_t capacity) {
    processPool* pp = (processPool*) malloc(sizeof(processPool));
    pp->capacity = capacity;
    pp->size = 0;
    pp->pids = (pid_t*)malloc(capacity * sizeof(pid_t));
    return pp;
}

void deleteProcessPool(processPool* pp) {
    free(pp->pids);
    free(pp);
}

static int getProcessIndex(processPool* pp, pid_t pid) {
    for (int i = 0; i < pp->size; i++) {
        if (pp->pids[i] == pid) return i;
    }
    return -1;
}

int reserveProcessPoolSlot(processPool* pp) {
    int newProcessIndex;

    if (pp->size >= pp->capacity) {
        int status = 0;
        printf("Waiting...\n");
        pid_t deadPID = wait(&status);
        newProcessIndex = getProcessIndex(pp, deadPID);
    } else {
        newProcessIndex = pp->size;
        pp->size++;
    }

    printf("Launching new subprocess...\n");
    pid_t pid = fork();
    if (pid != 0) {
        pp->pids[newProcessIndex] = pid;
    }

    return pid;
}

void waitForProcessesInPool(processPool* pp) {
    for (int processIndex = 0; processIndex < pp->size; processIndex++) {
        waitpid(pp->pids[processIndex], NULL, 0);
    }
}
