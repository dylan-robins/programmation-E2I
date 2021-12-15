#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#include "semaphores.h"

int parent_task(pid_t pid0, pid_t pid1) {
    return 0;
}

int child_task(unsigned int child_id) {
    printf("[C%d] - Child 0 opening semaphore...\n", child_id);
    sem_t *sem = sem_open("key.semaphore", O_RDWR, 0666, 2, -1);
    
    if (sem == NULL)
        printf("[C%d] - Error opening semaphore: Errno %d (%s)\n", child_id, errno, strerror(errno));
    
    printf("[C%d] - Opened semaphore\n", child_id);
    sem_print(sem);


    for (;;) {
        if (sem_decr(sem, child_id) != 0) {
            printf("[C%d] - Error waiting for 0: Errno %d (%s)\n", child_id, errno, strerror(errno));
        }
        printf("[C%d] - Semaphore unlocked!\n", child_id);
        sem_incr(sem, child_id);
    }

    return 0;
}


int main() {
    printf("[P] - Parent setting semaphores to 0...\n");
    sem_t *sem = sem_open("key.semaphore", O_RDWR, 0666, 2, 0);
    if (sem == NULL)
        printf("[P] - Error opening semaphore: Errno %d (%s)\n", errno, strerror(errno));

    pid_t pid0 = fork();
    if (pid0 == 0) {
        return child_task(0);
    }
    pid_t pid1 = fork();
    if (pid1 == 0) {
        return child_task(1);
    }

    if (pid0 != 0 && pid1 != 0) {
        sleep(1);

        for (unsigned int i = 0; i < 10; i++) {
            sleep(1);
            printf("[P] - Unlocking child %d...\n", i%2);
            sem_incr(sem, i%2);
            sem_decr(sem, i%2);
        }
        
        kill(pid0, SIGTERM);
        kill(pid1, SIGTERM);
        sem_destroy(sem);

        // wait for children to return
        waitpid(pid0, NULL, 0);
        waitpid(pid1, NULL, 0);
        return 0;
    }
}