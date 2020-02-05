#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recognition.h"

void test_file(FILE *f) {
    if (is_filetype(f, PDF)) {
       printf("File is a PDF\n");
    } else if (is_filetype(f, GIF)){
       printf("File is a GIF\n");
    } else if (is_filetype(f, JPEG)){
       printf("File is a JPEG\n");
    } else if (is_filetype(f, PS)){
       printf("File is a PS\n");
    } else if (is_filetype(f, RTF)){
       printf("File is a RTF\n");
    } else if (is_filetype(f, MP3v1)){
       printf("File is a MP3 (no metadata or ID3v1)\n");
    } else if (is_filetype(f, MP3v2)){
       printf("File is a MP3 (ID3v2 tags)\n");
    } else {
        printf("Unknown file type\n");
    }
}

void file_is_of_type(FILE *f, char *filetype) {
    // Parse file type
    file_type type = -1;
    if (strcmp(filetype, "pdf")==0 || strcmp(filetype, "PDF")==0) {
        type = PDF;
    } else if (strcmp(filetype, "gif")==0 || strcmp(filetype, "GIF")==0) {
        type = GIF;
    } else if (strcmp(filetype, "jpeg")==0 || strcmp(filetype, "JPEG")==0) {
        type = JPEG;
    } else if (strcmp(filetype, "jpg")==0 || strcmp(filetype, "JPG")==0) {
        type = JPEG;
    } else if (strcmp(filetype, "rtf")==0 || strcmp(filetype, "RTF")==0) {
        type = RTF;
    } else if (strcmp(filetype, "ps")==0 || strcmp(filetype, "PS")==0) {
        type = PS;
    } else if (strcmp(filetype, "mp3v1")==0 || strcmp(filetype, "MP3v1")==0) {
        type = PS;
    } else if (strcmp(filetype, "mp3v2")==0 || strcmp(filetype, "MP3v2")==0) {
        type = PS;
    } else {
        fprintf(stderr, "Error, unsupported file type %s\n", filetype);
        exit(2);
    }
    // check file type and print result
    if (is_filetype(f, type)) {
        printf("Is a %s file.\n", filetype);
    } else {
        printf("Not a %s file.\n", filetype);
    }
}

int main(int argc, char **argv) {
    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Error, incorrect number of arguments\n");
        fprintf(stderr, "Usage: %s <inputfile>\n", argv[0]);
        fprintf(stderr, "       %s <inputfile> <filetype_to_check>\n", argv[0]);
        return 1;
    }

    // open file
    FILE *f = fopen(argv[1], "r");

    if (f == NULL) {
        fprintf(stderr, "Error, unable to open file %s. Please check the filename and permissions.\n", argv[1]);
        return 3;
    }

    if (argc == 2) {
        test_file(f);
    } else if (argc == 3) {
        file_is_of_type(f, argv[2]);
    }

    // close file and exit
    fclose(f);
    return 0;
}