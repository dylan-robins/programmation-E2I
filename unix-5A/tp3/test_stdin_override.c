#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define TIME_STR_LENGTH 25

static volatile bool SIGINT_RECEIVED = false;
static volatile bool SIGUSR1_RECEIVED = false;
static volatile bool SIGUSR2_RECEIVED = false;

void SIGINT_handler(const int signal) {
    printf("Received signal SIGINT!\n");
    SIGINT_RECEIVED = true;
}

void SIGUSR1_handler(const int signal) {
    printf("Received signal SIGUSR1!\n");
    SIGUSR1_RECEIVED = true;
}

void SIGUSR2_handler(const int signal) {
    printf("Received signal SIGUSR2!\n");
    SIGUSR2_RECEIVED = true;
}

void parent_task(pid_t child1_pid, pid_t child2_pid, int pipe[2]) {
    signal(SIGINT, SIGINT_handler);

    while (!SIGINT_RECEIVED) {
        sleep(1);
        kill(child1_pid, SIGUSR1);
    }
    kill(child1_pid, SIGUSR2);
    sleep(1);
    kill(child1_pid, SIGINT);
}

int child1_task(int pipe[2]) {
    signal(SIGUSR1, SIGUSR1_handler);
    signal(SIGUSR2, SIGUSR2_handler);

    char *buffer;

    sleep(1);
    for (;;) {
        if (SIGUSR1_RECEIVED) {
            time_t timestamp = time(NULL);
            buffer = ctime(&timestamp);
            // Remove extra \n at end of ctime string
            //buffer[TIME_STR_LENGTH-1] = '\0';

            write(pipe[1], buffer, TIME_STR_LENGTH);
            SIGUSR1_RECEIVED = false;
        }
        if (SIGUSR2_RECEIVED) {
            strcpy(buffer, "$");
            write(pipe[1], buffer, 2);
            break;
        }
    };
    return 0;
}

int child2_task(int pipe[2]) {
    const int STDIN_FD = 0;
    close(STDIN_FD);
    dup(pipe[0]);
    close(pipe[0]);
    close(pipe[1]);
    execlp("./echo_dollar", "./echo_dollar", NULL);
    
    printf("Error running echo_dollar!\n");
    exit(1);
}

int main() {
    int p[2];
    pipe(p);

    pid_t pid1 = fork();
    if (pid1 == 0) {
        return child1_task(p);
    }
    pid_t pid2 = fork();
    if (pid2 == 0) {
        return child2_task(p);
    }

    if (pid1 != 0 && pid2 != 0) {
        parent_task(pid1, pid2, p);
        // wait for children to return
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
        return 0;
    }
}
