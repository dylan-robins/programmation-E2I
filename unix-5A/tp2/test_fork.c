#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

void child_task(int childId) {
    printf("I'm child %d, running in process %d\n", childId, getpid());
    exit(0);
}


int main() {
    int childrenPIDs[4];
    printf("Hello from the parent process (%d)\n", getpid());

    for (int child = 1; child <= 4; child++) {
        int pid = fork();
        if (pid == 0) {
            child_task(child);
        } else {
            childrenPIDs[child] = pid;
        }
    }

    for (int child = 1; child <= 4; child++) {
        waitpid(childrenPIDs[child], NULL, 0);
    }

    printf("Goodbye from the parent process\n");
    return 0;
}