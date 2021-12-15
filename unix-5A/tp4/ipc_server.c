#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "semaphores.h"

int main() {
    sem_t *sem = sem_open("key.semaphore", O_RDWR, 0666, 1, 1);
    printf("Server set semaphore to 1...\n");

    if (sem_wait_for_0(sem, 0) == 0) {
        printf("Client decremented semaphore! Exiting...\n");
        return 0;
    } else {
        printf("Error while waiting to semaphore to be 0! Exiting!\n");
        printf("Errno = %d: '%s'\n", errno, strerror(errno));
        return 1;
    }
}
