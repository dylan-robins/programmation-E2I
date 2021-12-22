#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Number of philosophers
#define PHILO_COUNT 5

// Philosopher type
typedef pthread_t philosopher;

typedef enum fork_state {
    FREE,
    USED
} fork_state_t;

// State of all forks on the table
fork_state_t g_forks[PHILO_COUNT];

// Mutex to restrict access to g_forks
pthread_mutex_t g_mutex;

/*
* Condition is
* - lifted when a philosopher releases a fork.
* - set when a philosopher is waiting for a fork.
*/
pthread_cond_t g_waitingToEat;

/* Philosophers have two things to do: think and eat.
 * In order to eat they need two forks: one to their left (index i) and
 * another to their right (index i+1).
 * If the forks aren't available, they think for a bit and try again later.
 */
void *philosopher_task(void *i) {
    long philo_id = (long)i;

    size_t left_fork_idx = philo_id;
    size_t right_fork_idx = (philo_id + 1) % PHILO_COUNT;

    do {
        // Lock mutex to check if our forks are free
        pthread_mutex_lock(&g_mutex);
        if (g_forks[left_fork_idx] == FREE && g_forks[right_fork_idx] == FREE) {
            // Forks are free, we can eat!
            printf("[philosopher %ld] Eating!\n", philo_id);
            g_forks[left_fork_idx] = USED;
            g_forks[right_fork_idx] = USED;
            pthread_mutex_unlock(&g_mutex);
            
            // eat for a second
            usleep((int)1e6);
            
            // we're done: release the forks
            printf("[philosopher %ld] Finished eating!\n", philo_id);
            pthread_mutex_lock(&g_mutex);
            g_forks[left_fork_idx] = FREE;
            g_forks[right_fork_idx] = FREE;
            pthread_mutex_unlock(&g_mutex);

            break;
            

        } else {
            // Forks aren't free, we have to think for a bit.
            // Start by releasing the mutex as we won't be touching the fork array
            pthread_mutex_unlock(&g_mutex);

            // Compute a random duration (in µsecs) between 1 and 2 secs
            int sleep_duration = (int)1e6 + rand() % (int)1e6;
            // Think for that amount of time
            printf("[philosopher %ld] Thinking for %.3f seconds\n", philo_id, sleep_duration * 1e-6);
            usleep(sleep_duration);
        }
    } while (1);

    return 0;
}

int main() {
    // Initialize philosopher table
    philosopher philos[PHILO_COUNT];

    // Set all forks to be free at the start
    for (size_t i = 0; i < PHILO_COUNT; i++) {
        g_forks[i] = FREE;
    }

    // Initialize mutex and condition variable
    pthread_mutex_init(&g_mutex, NULL);
    pthread_cond_init(&g_waitingToEat, NULL);

    // Set random seed
    srand(time(NULL));

    // Tell all philosophers to start doing their thing
    for (size_t i = 0; i < PHILO_COUNT; i++) {
        // Some pointer magic to pass i to the function without having
        // to store all values of i in an array somewhere
        pthread_create(&(philos[i]), NULL, philosopher_task, (void *)(long)i);
    }

    // Wait for all philosophers to finish
    for (size_t i = 0; i < PHILO_COUNT; i++) {
        pthread_join(philos[i], NULL);
    }

    // Clean up and exit
    pthread_cond_destroy(&g_waitingToEat);
    pthread_mutex_destroy(&g_mutex);
    return 0;
}
