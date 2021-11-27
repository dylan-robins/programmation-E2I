#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int parent_task(int pipe[2]) {
    const int parentPID = getpid();
    const char *msg = "Hello from the other side";
    size_t msg_length = strlen(msg) + 1;

    sleep(2);
    write(pipe[1], &parentPID, sizeof(int));
    
    sleep(2);
    write(pipe[1], &msg_length, sizeof(size_t));
    write(pipe[1], msg, msg_length);

    return 0;
}

int child_task(int pipe[2]) {
    int parent_pid;
    size_t msg_length;
    char * msg;
    int read_bytes_count;

    read_bytes_count = read(pipe[0], &parent_pid, sizeof(int));
    if (read_bytes_count == 0) {
        printf("Child was unable to read data from the pipe!\n");
        return 1;
    }
    printf("Child process (pid %d) read parent pid from pipe: %d\n", getpid(), parent_pid);

    read_bytes_count = read(pipe[0], &msg_length, sizeof(size_t));
    if (read_bytes_count == 0) {
        printf("Child was unable to read message length from the pipe!\n");
        return 1;
    }

    printf("Child process read message length from pipe: %ld\n", msg_length);
    
    // Allocate buffer to receive message
    msg = (char *) malloc(msg_length * sizeof(char));
    
    read_bytes_count = read(pipe[0], msg, msg_length);
    if (read_bytes_count == 0) {
        printf("Child was unable to read message content from the pipe!\n");
        return 1;
    }

    printf("Child process read message content from pipe: '%s'\n", msg);

    return 0;
}

int main() {
    int p[2];
    int ret_code;

    printf("Parent process pid: %d\n", getpid());

    if (pipe(p) == -1) {
        // Pipe wasn't created
        printf("Error: unable to create pipe!\n");
        exit(1);
    }

    int pid = fork();
    if (pid == 0) {
        ret_code = child_task(p);
    } else {
        ret_code = parent_task(p);
        // wait for child to return
        waitpid(pid, NULL, 0);
    }

    // Close the pipe
    close(p[0]);
    close(p[1]);

    return ret_code;
}
