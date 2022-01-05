#include "semaphores.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void sem_print(sem_t *sem) {
    printf("    Id: %d\n", sem->id);
    printf("    Name: %s\n", sem->name);
    printf("    Key: %d\n", sem->key);
    printf("    Count: %d\n", sem->count);
}

sem_t *sem_init(unsigned int key, int count, int val) {
    // Create semaphore
    sem_t *sem = (sem_t *)malloc(sizeof(sem_t));
    sem->key = key;
    sem->count = count;
    sem->id = semget(key, count, IPC_CREAT | 0666);
    sem->name = NULL;

    if (sem->id == -1) {
        // Error occured, errno is set
        return NULL;
    }

    if (val >= 0) {
        // Initialize created semaphore
        unsigned short *buffer = calloc(count, sizeof(unsigned short));
        for (size_t i = 0; i < count; i++) {
            buffer[i] = (unsigned short) val;
        }
        semctl(sem->id, 0, SETALL, buffer);
        free(buffer);
    }
    return sem;
}

int sem_destroy(sem_t *sem) {
    int ret_val = 0;
    for (unsigned int i = 0; i < sem->count; i++)
        ret_val |= semctl(sem->id, i, IPC_RMID);
    free(sem);
    return ret_val;
}

sem_t *sem_open(const char *key_file, int options, mode_t mode, unsigned int count, int val) {
    // Create key file if it doesn't exist
    int fd = open(key_file, options | mode);
    close(fd);

    key_t key = ftok(key_file, 0);
    sem_t *sem = sem_init(key, count, val);
    if (sem != NULL)
        sem->name = key_file;
    return sem;
}

int sem_decr(sem_t *sem, unsigned int idx) {
    struct sembuf sb;
    sb.sem_num = idx;
    sb.sem_op = -1;
    sb.sem_flg = SEM_UNDO;
    return semop(sem->id, &sb, 1);
}

int sem_wait_for_0(sem_t *sem, unsigned int idx) {
    struct sembuf sb;
    sb.sem_num = idx;
    sb.sem_op = 0;
    sb.sem_flg = 0;
    return semop(sem->id, &sb, 1);
}


int sem_incr(sem_t *sem, unsigned int idx) {
    struct sembuf sb;
    sb.sem_num = idx;
    sb.sem_op = 1;
    sb.sem_flg = SEM_UNDO;
    return semop(sem->id, &sb, 1);
}


void sem_wrapper(int err_flag, char * msg) {
    if (err_flag == -1) {
        printf("%s\nError %d: %s\n", msg, errno, strerror(errno));
        exit(1);
    }
}