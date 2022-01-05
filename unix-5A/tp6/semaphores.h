#ifndef __SEMAPHORES_H_
#define __SEMAPHORES_H_

#include <sys/sem.h>
#include <stdarg.h>

typedef struct {
    unsigned int key;
    const char *name;
    unsigned int id;
    unsigned int count;
} sem_t;

/* Creates and initializes a new semaphore
 * \param sem: a sem_t struct identifying the semaphore to display
 */
void sem_print(sem_t *sem);

/* Creates and initializes a new semaphore
 * \param key: key to use when creating the semaphore
 * \param count: number of counters to create
 * \param val: value to initialize the counters to
 * \return A sem_t structure containing information about the semaphore
 */
sem_t *sem_init(unsigned int key, int count, int val);

/* Destroys a semaphore and frees the provided struct
 * \param sem: a sem_t struct identifying the semaphore to destroy
 * \return 1 if success, else 0
 */
int sem_destroy(sem_t *sem);

/* Creates and initializes a new semaphore
 * \param key_file: file to use to sync the semaphore IDs
 * \param options: file open options
 * \param mode: file open mode
 * \param count: number of counters to create
 * \param val: value to initialize the semaphore to (-1 to disable initialization)
 * \return a sem_t structure containing information about the semaphore
 */
sem_t *sem_open(const char *key_file, int options, mode_t mode, unsigned int count, int val);

/* Decrements a semaphore's value
 * \param sem: a sem_t struct identifying the semaphore to manipulate
 * \return 1 if success, else 0
 */
int sem_decr(sem_t *id, unsigned int idx);

/* Waits until the provided semaphore has value 0
 * \param sem: a sem_t struct identifying the semaphore to manipulate
 * \return 1 if success, else 0
 */
int sem_wait_for_0(sem_t *id, unsigned int idx);

/* Increments a semaphore's value
 * \param sem: a sem_t struct identifying the semaphore to manipulate
 * \return 1 if success, else 0
 */
int sem_incr(sem_t *id, unsigned int idx);

/* Wrapper around semaphore functions to handle errors cleanly
 * \param err_flag: return value of the called function
 * \param msg: message to display in case the call failed
 */
void sem_wrapper(int err_flag, char * msg);

#endif