#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "strUtils.h"

static int promptUser(char* lineBuffer, unsigned int size) {
    printf(">>> ");

    int status = fgets(lineBuffer, size, stdin) != NULL;
    
    trim(lineBuffer);
    strupper(lineBuffer);

    return status;
}

int get_server_pid() {
    char buffer[2048];

    printf("Enter server processes pid:\n");
    promptUser(buffer, 2048);

    trim(buffer);
    strupper(buffer);

    return atoi(buffer);
}

int get_signal() {
    char buffer[2048];

    printf("Enter a signal name to send:\n");
    promptUser(buffer, 2048);

    if (strcmp(buffer, "SIGINT") == 0) {
        return SIGINT;
    } else if (strcmp(buffer, "SIGUSR1") == 0) {
        return SIGUSR1;
    } else if (strcmp(buffer, "SIGUSR2") == 0) {
        return SIGUSR2;
    } else if (strcmp(buffer, "SIGKILL") == 0) {
        return SIGKILL;
    } else {
        return -1;
    }
}

int main() {
    pid_t server_pid = get_server_pid();

    int signal_to_send;
    while (signal_to_send != SIGKILL) {
        signal_to_send = -1;

        // read signal from cli
        while (signal_to_send == -1) {
            signal_to_send = get_signal();
            if (signal_to_send == -1) {
                printf("Error: unspported signal\n");
            }
        }
        printf("Sending signal %d...\n", signal_to_send);

        // send signal to server
        kill(server_pid, signal_to_send);
    }

    return 0;
}