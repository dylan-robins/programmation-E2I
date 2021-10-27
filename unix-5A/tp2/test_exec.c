#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char ** argv) {
    int pid = fork();
    int status = 0;

    if (pid == 0) {
        char ** args = malloc((argc) * sizeof(char *));
        args[0] = "ls";
        args[1] = "-al";
        for (int i = 1; i <= argc; i++) {
            args[i+1] = argv[i];
        }

        execvp("ls", args);

    } else {
        waitpid(pid, &status, 0);
    }
    
    return status;
}