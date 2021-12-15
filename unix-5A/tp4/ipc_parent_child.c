#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "semaphores.h"

int parent_task() {
    sem_t *sem = sem_open("key.semaphore", O_RDWR, 0666, 1, 1);
    printf("[P] - Parent set semaphore to 1...\n");
    if (sem_wait_for_0(sem, 0) == 0) {
        printf("[P] - Child decremented semaphore! Parent exiting...\n");
        return 0;
    } else {
        printf("[P] - Error while waiting to semaphore to be 0! Exiting!\n");
        printf("[P] - Errno = %d '%s'\n", errno, strerror(errno));
        return 1;
    }
}

int child_task() {
    sem_t *sem = sem_open("key.semaphore", O_RDWR, 0666, 1, -1);
    printf("[C] - Child opened semaphore...\n");
    sleep(3);
    sem_decr(sem, 0);
    printf("[C] - Child decremented semaphore! Child exiting...\n");

    return 0;
}

int main() {
    int ret_code;

    pid_t pid1 = fork();

    if (pid1 == 0) {
        ret_code = child_task();
        printf("[C] - Child process returned.\n");
    } else {
        ret_code = parent_task();
        // wait for children to return
        waitpid(pid1, NULL, 0);
        printf("[P] - Parent process returned.\n");
    }

    return ret_code;
}
