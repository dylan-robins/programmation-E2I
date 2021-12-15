#include <fcntl.h>
#include <stdio.h>

#include "semaphores.h"

int main() {
    int ok = 0;

    printf("Creating semaphore: ");
    // sem_t * sem = sem_init(0, 1, 4);
    sem_t *sem = sem_open("key.semaphore", O_CREAT, 0666, 1, 1);
    printf("%d\n", sem != NULL);

    sem_print(sem);

    printf("Decrementing semaphore: ");
    ok = sem_decr(sem, 0);
    printf("%d\n", ok == 0);

    printf("Incrementing semaphore: ");
    ok = sem_incr(sem, 0);
    printf("%d\n", ok == 0);

    printf("Destroying semaphore: ");
    ok = sem_destroy(sem);
    printf("%d\n", ok == 0);

    return 0;
}