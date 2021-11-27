#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void SIGUSER1_handler(const int signal) {
    printf("Received signal SIGUSER1!\n");
}

void SIGUSER2_handler(const int signal) {
    printf("Received signal SIGUSER2!\n");
}

int parent_task(pid_t child1_pid, pid_t child2_pid) {
    for (;;) {
        sleep(2);
        kill(child1_pid, SIGUSR1);
        sleep(2);
        kill(child2_pid, SIGUSR2);
    }
    
    return 0;
}

int child_task(int sig, void (*handler)(const int)) {
    signal(sig, handler);
    for (;;) {};
    return 0;
}

int main() {
    int ret_code;

    pid_t pid1 = fork();
    if (pid1 == 0) {
        ret_code = child_task(SIGUSR1, SIGUSER1_handler);
    }
    pid_t pid2 = fork();
    if (pid2 == 0) {
        ret_code = child_task(SIGUSR2, SIGUSER2_handler);
    }

    if (pid1 != 0 && pid2 != 0) {
        ret_code = parent_task(pid1, pid2);
        // wait for children to return
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
    }

    return ret_code;
}
