#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void handler(const int sig) {
    switch (sig) {
        case SIGUSR1:
            printf("Received signal SIGUSER1!\n");
            break;
        case SIGUSR2:
            printf("Received signal SIGUSER2!\n");
            break;
        case SIGINT:
            printf("Received signal SIGINT!\n");
            break;
        default:
            signal(sig, SIG_DFL);
    }
    
}

int main() {
    printf("Server started with pid %d\n", getpid());
    signal(SIGINT, handler);
    signal(SIGUSR1, handler);
    signal(SIGUSR2, handler);

    // wait forever using signal handlers to do stuff
    for (;;) {}

    return 0;
}