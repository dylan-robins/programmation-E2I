#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "semaphores.h"

int main() {
    printf("Opening semaphore...\n");
    sem_t *sem = sem_open("key.semaphore", O_RDWR, 0666, 1, -1);
    
    sleep(3);
    
    sem_decr(sem, 0);
    printf("Decremented semaphore! Exiting...\n");

    return 0;
}
