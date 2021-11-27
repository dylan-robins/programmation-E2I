#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define TIME_STR_LENGTH 24

volatile bool SIGNAL_RECEIVED = false;

void SIGUSER1_handler(const int signal) {
    printf("Received signal SIGUSER1!\n");
    SIGNAL_RECEIVED = true;
}

void SIGUSER2_handler(const int signal) {
    printf("Received signal SIGUSER2!\n");
    SIGNAL_RECEIVED = true;
}

void parent_task(pid_t child1_pid, pid_t child2_pid, int pipe[2]) {
    char time_str[TIME_STR_LENGTH];
    for (;;) {
        sleep(2);
        kill(child1_pid, SIGUSR1);
        read(pipe[0], time_str, TIME_STR_LENGTH);
        printf("Got time '%s' from child 1\n", time_str);
        
        sleep(2);
        kill(child2_pid, SIGUSR2);
        read(pipe[0], time_str, TIME_STR_LENGTH);
        printf("Got time '%s' from child 2\n", time_str);
    }
}

int child_task(int sig, void (*handler)(const int), int pipe[2]) {
    signal(sig, handler);
    char *time_str;
    for (;;) {
        if (SIGNAL_RECEIVED) {
            time_t timestamp = time(NULL);
            time_str = ctime(&timestamp);
            sleep(1);
            write(pipe[1], time_str, TIME_STR_LENGTH);
            SIGNAL_RECEIVED = false;
        }
    };
    return 0;
}

int main() {
    int p[2];
    pipe(p);

    pid_t pid1 = fork();
    if (pid1 == 0) {
        return child_task(SIGUSR1, SIGUSER1_handler, p);
    }
    pid_t pid2 = fork();
    if (pid2 == 0) {
        return child_task(SIGUSR2, SIGUSER2_handler, p);
    }

    if (pid1 != 0 && pid2 != 0) {
        parent_task(pid1, pid2, p);
        // wait for children to return
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
        return 0;
    }
}
