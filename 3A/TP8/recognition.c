#include <stdio.h>
#include <string.h>
#include "recognition.h"

int recog_PDF(FILE *f) {
    char mgknum[6];
    fseek(f, 0, SEEK_SET);
    // read PDF magic number:
    mgknum[5] = '\0';
    for (int i = 0; i < 5; i++) {
        mgknum[i] = fgetc(f);
    }
    return strcmp(mgknum, "%PDF-") == 0;
}

int recog_GIF(FILE *f) {
    char mgknum[7];
    fseek(f, 0, SEEK_SET);
    // read GIF magic number:
    mgknum[6] = '\0';
    for (int i = 0; i < 6; i++) {
        mgknum[i] = fgetc(f);
    }
    return (strcmp(mgknum, "GIF89a") == 0)||(strcmp(mgknum, "GIF89b") == 0);
}
int recog_PS(FILE *f) {
    char mgknum[3];
    fseek(f, 0, SEEK_SET);
    // read PS magic number:
    mgknum[2] = '\0';
    for (int i = 0; i < 2; i++) {
        mgknum[i] = fgetc(f);
    }
    return strcmp(mgknum, "%!") == 0;
}
int recog_JPEG(FILE *f) {
    unsigned char mgkStart[3];
    unsigned char mgkEnd[3];
    fseek(f, 0, SEEK_SET);
    mgkStart[2] = 0x0;
    mgkEnd[2] = 0x0;
    // read start magic
    for (int i = 0; i < 2; i++) {
        mgkStart[i] = fgetc(f);
    }
    // read end magic
    fseek(f, -2, SEEK_END);
    for (int i = 0; i < 2; i++) {
        mgkEnd[i] = fgetc(f);
    }
    return (
           (mgkStart[0] == 0xFF && mgkStart[1] == 0xD8)
        || (mgkEnd[0] == 0xFF && mgkEnd[1] == 0xD9)
    );
}
int recog_RTF(FILE *f) {
    char mgknum[7];
    fseek(f, 0, SEEK_SET);
    // read RTF magic number:
    mgknum[6] = '\0';
    for (int i = 0; i < 6; i++) {
        mgknum[i] = fgetc(f);
    }
    return strcmp(mgknum, "{\\rtf1") == 0;
}

int recog_MP3v1(FILE *f){
    unsigned char mgknum[3];
    fseek(f, 0, SEEK_SET);
    // read MP3 magic number:
    mgknum[2] = '\0';
    for (int i = 0; i < 2; i++) {
        mgknum[i] = fgetc(f);
    }
    return (mgknum[0] == 0xFF && mgknum[1] == 0xFB);
}

int recog_MP3v2(FILE *f){
    char mgknum[4];
    fseek(f, 0, SEEK_SET);
    // read ID3 magic number:
    mgknum[3] = '\0';
    for (int i = 0; i < 3; i++) {
        mgknum[i] = fgetc(f);
    }
    return strncmp(mgknum, "ID3", 3);
}

int is_filetype(FILE *f, file_type filetype) {
    switch (filetype)
    {
    case PDF:
        return recog_PDF(f);
    case GIF:
        return recog_GIF(f);
    case PS:
        return recog_PS(f);
    case JPEG:
        return recog_JPEG(f);
    case RTF:
        return recog_RTF(f);
    case MP3v1:
        return recog_MP3v1(f);
    case MP3v2:
        return recog_MP3v2(f);
    default:
        return 0;
    }
}