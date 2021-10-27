#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void usage(char * progName) {
    printf("Usage: '%s inode_name'\n", progName);
}

void waitForEnter() {
    printf("Hit enter to continue...");
    getc(stdin);
}

int file_exists (char *filename) {
  struct stat buffer;   
  return stat(filename, &buffer) == 0;
}

void createAndPopulateTextFile(char * filename) {
    int fileDescr = 0;

    int fileOpenFlags = 0;
    char * fileContent = "Quelque chose\n";

    if (file_exists(filename)) {
        fileOpenFlags = O_RDWR|O_TRUNC;
    } else {
        fileOpenFlags = O_CREAT|O_RDWR|O_TRUNC;
    }
    fileDescr = open(filename, fileOpenFlags, 0644);

    write(fileDescr, fileContent, strlen(fileContent));
    close(fileDescr);
}

void openAndReadTextFile(char * filename) {
    int fileDescr = 0;
    char fileContent[1024];

    fileDescr = open(filename, O_RDONLY);

    read(fileDescr, fileContent, 1024);
    printf("File content of '%s':\n", filename);
    printf("%s", fileContent);
    close(fileDescr);
}

void openUnlinkWriteAndCheck(char * filename) {
    int fileDescr = 0;
    fileDescr = open(filename, O_APPEND, 0644);

    unlink(filename);

    if (file_exists(filename)) {
        printf("File exists even though it was unlinked!\n");
    } else {
        printf("File doesn't exist after being unlinked!\n");
    }

    const char * fileContent = "Content written after deletion\n";
    write(fileDescr, fileContent, strlen(fileContent));
    
    if (file_exists(filename)) {
        printf("File exists after writing to stale handle!\n");
    } else {
        printf("File doesn't exist after writing to stale handle!\n");
    }

    waitForEnter();
    
    close(fileDescr);

    if (file_exists(filename)) {
        printf("File exists after closing!\n");
    } else {
        printf("File doesn't exist after closing!\n");
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Nombre incorrect d'arguments!\n");
        usage(argv[0]);
        exit(1);
    }

    char * filename = argv[1];

    createAndPopulateTextFile(filename);
    openAndReadTextFile(filename);
    waitForEnter();
    openUnlinkWriteAndCheck(filename);

    return 0;
}