#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#include "semaphores.h"

typedef struct {
    char buff[1024];
    bool end;
} shared_buffer;

void child_task(int child_id, int shmid, sem_t* sem) {
    printf("[C%d] Started subprocess\n", child_id);

    shared_buffer* ptr = (shared_buffer*)shmat(shmid, NULL, 0);

    if (ptr == NULL) {
        printf("[C%d] Error: couldn't open shared buffer\n", child_id);
        exit(1);
    }

    // Do something with ptr
    while (true) {
        printf("[C%d] Waiting...\n", child_id);

        sem_wrapper(
            sem_wait_for_0(sem, child_id),
            "Error waiting for 0!\n");

        // If the parent signals that it's finished, exit now
        if (ptr->end) break;

        sem_wrapper(
            sem_incr(sem, child_id),
            "Error incrementing semaphore!\n");

        sem_wrapper(
            sem_decr(sem, 2),
            "Couldn't take mutex!");

        printf("[C%d] Found message: '%s'\n", child_id, ptr->buff);

        sem_wrapper(
            sem_incr(sem, 2),
            "Couldn't reset mutex!");
    }

    if (shmdt(ptr) == -1) {
        printf("[C%d] Error: couldn't close shared buffer\n", child_id);
    }

    printf("[C%d] Child process exiting\n", child_id);
    exit(0);
}

void parent_task(int shmid, sem_t* sem) {
    shared_buffer* ptr = (shared_buffer*)shmat(shmid, NULL, 0);
    if (ptr == NULL) {
        printf("[P] Error: couldn't open shared buffer\n");
        exit(1);
    }

    // Do something with ptr
    for (int i = 0; i <= 10; i++) {
        sem_wrapper(
            sem_decr(sem, 2),
            "Couldn't take mutex!");
        sprintf(ptr->buff, "Hello from parent! %d", i);

        sem_wrapper(
            sem_incr(sem, 2),
            "Couldn't reset mutex!");

        printf("[P] Unlocking child %d\n", i % 2);

        sem_wrapper(
            sem_decr(sem, i % 2),
            "Error waiting for 0!\n");

        sleep(1);
    }

    ptr->end = true;
    sem_decr(sem, 0);
    sem_decr(sem, 1);

    if (shmdt(ptr) == -1) {
        printf("[P] Error: couldn't close shared buffer\n");
    }
}

int main() {
    // Allocate a shared buffer
    int shmid = shmget(IPC_PRIVATE, sizeof(shared_buffer), IPC_CREAT | 0666);
    if (shmid == -1) {
        printf("Error: couldn't get shared buffer\n");
        return 1;
    }

    // Create a semaphore
    sem_t* sem = sem_init(IPC_PRIVATE, 3, 1);

    pid_t pid1 = fork();
    if (pid1 == 0) {
        child_task(0, shmid, sem);
    }
    pid_t pid2 = fork();
    if (pid2 == 0) {
        child_task(1, shmid, sem);
    }

    parent_task(shmid, sem);

    // wait for children to return
    printf("[P] Waiting for child 0\n");
    waitpid(pid1, NULL, 0);
    printf("[P] Waiting for child 1\n");
    waitpid(pid2, NULL, 0);

    // Remove shared memory
    int status = shmctl(shmid, IPC_RMID, NULL);
    if (status == -1) {
        printf("Error: couldn't remove shared buffer\n");
    }
    // remove semaphore
    sem_destroy(sem);

    printf("[P] Parent process exiting\n");

    return 0;
}