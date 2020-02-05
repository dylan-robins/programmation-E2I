#ifndef __RECOGNITION_H__
#define __RECOGNITION_H__

#include <stdio.h>

typedef enum {
    PDF,
    GIF,
    PS,
    JPEG,
    RTF,
    MP3v1,
    MP3v2
} file_type;


int recog_PDF(FILE *f);
int recog_GIF(FILE *f);
int recog_PS(FILE *f);
int recog_JPEG(FILE *f);
int recog_RTF(FILE *f);
int recog_MP3v1(FILE *f);
int recog_MP3v2(FILE *f);

int is_filetype(FILE *f, file_type t);

#endif