#include "printInodeStats.h"

#include <stdio.h>
#include <sys/stat.h>

void printInodeStats(char * inodeName) {
    struct stat inode_stat;
    stat(inodeName, &inode_stat);

    printf("i-node info for %s:\n", inodeName);
    printf("ID of device containing file:    %ld\n", inode_stat.st_dev);
    printf("Inode number:                    %ld\n", inode_stat.st_ino);
    printf("File type and mode:              %d\n", inode_stat.st_mode);
    printf("Number of hard links:            %ld\n", inode_stat.st_nlink);
    printf("User ID of owner:                %d\n", inode_stat.st_uid);
    printf("Group ID of owner:               %d\n", inode_stat.st_gid);
    printf("Device ID (if special file):     %ld\n", inode_stat.st_rdev);
    printf("Total size, in bytes:            %ld\n", inode_stat.st_size);
    printf("Block size for filesystem I/O:   %ld\n", inode_stat.st_blksize);
    printf("Number of 512B blocks allocated: %ld\n", inode_stat.st_blocks);
}