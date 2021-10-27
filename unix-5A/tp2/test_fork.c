#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void child_task(int childId) {
    printf("I'm child %d, running in process %d\n", childId, getpid());
    exit(0);
}


int main() {
    printf("Hello from the parent process (%d)\n", getpid());
    for (int child = 1; child <= 4; child++) {
        int pid = fork();
        if (pid == 0) {
            child_task(child);
        }
    }

    printf("Goodbye from the parent process\n");
    return 0;
}