#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define KEYBUFFER_CAPACITY 1024
char keybuffer[KEYBUFFER_CAPACITY];
pthread_mutex_t keybuffer_lock = PTHREAD_MUTEX_INITIALIZER;

/* Appends a character onto a string. The string must be sufficently big! */
void strcatc(char * src, char c) {
    size_t len = strlen(src);
    src[len] = c;
    src[len + 1] = '\0';
}

/* Consumes characters from stdin, appending them to the global keybuffer
 * \param NULL
 * \return NULL
 */
void * get_keys(void * arg) {
    int c = ' ';

    printf("[get_keys] - Starting get_keys...\n");

    while (c != 'F') {
        c = getchar();

        if (strlen(keybuffer) < KEYBUFFER_CAPACITY) {
            pthread_mutex_lock(&keybuffer_lock);
            strcatc(keybuffer, c);
            pthread_mutex_unlock(&keybuffer_lock);
        } else {
            printf("[get_keys] - Buffer overflow, exiting...\n");
            break;
        }
    }
    printf("[get_keys] - Exiting...\n");
    return NULL;
}

/* Consumes characters from the global string keybuffer, printing them to the screen
 * \param NULL
 * \return NULL
 */
void * print_keybuffer(void * arg) {
    int last_idx = 0;

    printf("[print_keybuffer] - Starting print_keybuffer...\n");

    while (1) {
        pthread_mutex_lock(&keybuffer_lock);

        if (last_idx < strlen(keybuffer)) {
            printf("%c", keybuffer[last_idx]);
            last_idx++;
        }
        if (keybuffer[last_idx-1] == 'F') {
            printf("\n");
            break;
        }
        
        pthread_mutex_unlock(&keybuffer_lock);
    }
    printf("[print_keybuffer] - Exiting...\n");
    return NULL;
}

int main() {
    pthread_t tid[2];

    // Initialize global keybuffer to empty string
    strcpy(keybuffer, "");

    pthread_create(&tid[0], NULL, get_keys, NULL);
    pthread_create(&tid[0], NULL, print_keybuffer, NULL);
    pthread_join(tid[0], NULL) ;
    pthread_join(tid[1], NULL) ;
    return 0;
}