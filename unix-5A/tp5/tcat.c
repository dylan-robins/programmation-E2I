#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>

char g_buffer = ' ';
pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t g_sync = PTHREAD_COND_INITIALIZER;

/* Consumes characters from stdin, appending them to the global keybuffer
 * \param NULL
 * \return NULL
 */
void* get_keys(void* arg) {
    pthread_mutex_lock(&g_lock);
    printf("[get_keys] - Starting get_keys...\n");

    while (g_buffer != 'F' && g_buffer != EOF && g_buffer != 4 /* EOT */) {
        g_buffer = getchar();
        pthread_cond_signal(&g_sync);
        pthread_cond_wait(&g_sync, &g_lock);
    }
    pthread_mutex_unlock(&g_lock);
    printf("[get_keys] - Exiting...\n");
    return NULL;
}

/* Consumes characters from the global string keybuffer, printing them to the screen
 * \param NULL
 * \return NULL
 */
void* print_keybuffer(void* arg) {
    pthread_mutex_lock(&g_lock);
    pthread_cond_signal(&g_sync);

    printf("[print_keybuffer] - Starting print_keybuffer...\n");
    while (g_buffer != 'F') {
        pthread_cond_wait(&g_sync, &g_lock);
        printf("%c", g_buffer);
        pthread_cond_signal(&g_sync);
    }
    printf("[print_keybuffer] - Exiting...\n");
    pthread_mutex_unlock(&g_lock);
    return NULL;
}

int main() {
    pthread_t tid[2];

    // Disable terminal buffering
    setvbuf(stdout, NULL, _IONBF, 0);
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON);
    tcsetattr(0, TCSANOW, &term);

    // Start worker threads
    pthread_mutex_lock(&g_lock);
    pthread_create(&tid[0], NULL, print_keybuffer, NULL);
    // wait for thread to be ready
    pthread_cond_wait(&g_sync, &g_lock);
    // start next thread
    pthread_create(&tid[0], NULL, get_keys, NULL);
    // thread init finished
    pthread_mutex_unlock(&g_lock);

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);


    // Reset terminal buffering
    tcgetattr(0, &term);
    term.c_lflag |= ICANON;
    tcsetattr(0, TCSANOW, &term);

    return 0;
}
