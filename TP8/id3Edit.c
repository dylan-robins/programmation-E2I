#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

typedef struct {
    char tag[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
    char comment[30];
    char genre;
} id3Metadata;

typedef struct {
    uint32_t version : 1;
    uint32_t layer : 2;
    uint32_t error_protection : 1;
    uint32_t bit_rate : 4;
    uint32_t frequency : 2;
} Mp3Header;

void readMp3(FILE *mp3, Mp3Header *header, id3Metadata *metadata) {
    uint32_t buff;

    // read header (32 first bits of file)
    fseek(mp3, 0, SEEK_SET);
    fread(&buff, sizeof(uint32_t), 1, mp3);
    // if the sync block (first 12 bits) aren't FFF, try flipping endienness
    if (((buff & 0xFFF00000) >> 20) != 0xFFF) {
        buff = ((buff>>24)&0xff) | // move byte 3 to byte 0
               ((buff<<8)&0xff0000) | // move byte 1 to byte 2
               ((buff>>8)&0xff00) | // move byte 2 to byte 1
               ((buff<<24)&0xff000000); // byte 0 to byte 3

        // if still not good, we're stuffed
        if (((buff & 0xFFF00000) >> 20) != 0xFFF) {
            fprintf(stderr, "Error: file isn't an MP3!\n");
            exit(2);
        }
    }
    // fill in header data
    header->version = (buff & 0x00080000) >> 19;
    header->layer = (buff & 0x00060000) >> 17;
    header->error_protection = (buff & 0x00010000) >> 16;
    header->bit_rate = (buff & 0x0000F000) >> 12;
    header->frequency = (buff & 0x00000C00) >> 10;

    // ID3v1.1 block is the last 128 bytes of the file
    fseek(mp3, -128, SEEK_END);
    // read the metadata block into a struct to parse it easily
    fread(metadata, sizeof(id3Metadata), 1, mp3);
    // If we've read gibberish, don't bother
    if (strncmp(metadata->tag, "TAG", 3) != 0) {
        fprintf(stderr, "No metadata found\n");
        exit(4);
    }

}

void displayHeader(Mp3Header *header) {
    // Meaning of bytes taken from http://www.mp3-tech.org/programmer/frame_header.html
    printf("Version: ");
    switch (header->version) {
        case 0:
            printf("MPEG2\n");
            break;
        case 1:
            printf("MPEG1\n");
            break;
        default:
            printf("Unknown MPEG version ID\n");
            break;
    }

    printf("Layer: ");
    switch (header->layer) {
        case 1:
            printf("Layer III\n");
            break;
        case 2:
            printf("Layer II\n");
            break;
        case 0:
            printf("Layer I\n");
            break;
        default:
            printf("Unknown MPEG version ID\n");
            break;
    }

    printf("CRC protection: %s\n", (header->error_protection == 0)?"yes":"no");

    printf("Bitrate: ");
    if (header->version == 1 && header->layer == 0) {
        int bitrates[] = {0, 32, 64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, -1};
        printf("%d kbps\n", bitrates[header->bit_rate]);
    } else if (header->version == 1 && header->layer == 2) {
        int bitrates[] = {0, 32, 48, 56,  64,  80,  96, 112, 128, 160, 192, 224, 256, 320, 384, -1};
        printf("%d kbps\n", bitrates[header->bit_rate]);
    } else if (header->version == 1 && header->layer == 1) {
        int bitrates[] = {0, 32, 40, 48,  56,  64,  80,  96, 112, 128, 160, 192, 224, 256, 320, -1};
        printf("%d kbps\n", bitrates[header->bit_rate]);
    } else if (header->version == 0 && header->layer == 0) {
        int bitrates[] = {0, 32, 48, 56,  64,  80,  96, 112, 128, 144, 160, 176, 192, 224, 256, -1};
        printf("%d kbps\n", bitrates[header->bit_rate]);
    } else if (header->version == 0 && (header->layer == 1 || header->layer == 2)) {
        int bitrates[] = {0, 8,  16, 24,  32,  40,  48,  56,  64,  80,  96, 112, 128, 144, 160, -1};
        printf("%d kbps\n", bitrates[header->bit_rate]);
    } else {
        printf("Unknown\n");
    }

    printf("Sample rate: ");
    if (header->version == 1) {
        int samplerates[] = {44100, 48000, 32000};
        printf("%d Hz\n", samplerates[header->frequency]);
    } else if (header->version == 0) {
        int samplerates[] = {22050, 24000, 16000};
        printf("%d Hz\n", samplerates[header->frequency]);
    } else {
        printf("Unknown\n");
    }
}

void displayMetadata(id3Metadata *metadata) {
    printf("title: %.30s\n", metadata->title);
    printf("artist: %.30s\n", metadata->artist);
    printf("album: %.30s\n", metadata->album);
    printf("year: %.4s\n", metadata->year);
    printf("comment: %.30s\n", metadata->comment);
    printf("genre: ");
    // Genres ripped from here https://mutagen-specs.readthedocs.io/en/latest/id3/id3v1-genres.html with a little bit of JS magic
    // Only took the ones in the original spec, not the Winamp extention
    switch (metadata->genre) {
        case 0:
            printf("Blues");
            break;
        case 1:
            printf("Classic Rock");
            break;
        case 2:
            printf("Country");
            break;
        case 3:
            printf("Dance");
            break;
        case 4:
            printf("Disco");
            break;
        case 5:
            printf("Funk");
            break;
        case 6:
            printf("Grunge");
            break;
        case 7:
            printf("Hip-Hop");
            break;
        case 8:
            printf("Jazz");
            break;
        case 9:
            printf("Metal");
            break;
        case 10:
            printf("New Age");
            break;
        case 11:
            printf("Oldies");
            break;
        case 12:
            printf("Other");
            break;
        case 13:
            printf("Pop");
            break;
        case 14:
            printf("R&B");
            break;
        case 15:
            printf("Rap");
            break;
        case 16:
            printf("Reggae");
            break;
        case 17:
            printf("Rock");
            break;
        case 18:
            printf("Techno");
            break;
        case 19:
            printf("Industrial");
            break;
        case 20:
            printf("Alternative");
            break;
        case 21:
            printf("Ska");
            break;
        case 22:
            printf("Death Metal");
            break;
        case 23:
            printf("Pranks");
            break;
        case 24:
            printf("Soundtrack");
            break;
        case 25:
            printf("Euro-Techno");
            break;
        case 26:
            printf("Ambient");
            break;
        case 27:
            printf("Trip-Hop");
            break;
        case 28:
            printf("Vocal");
            break;
        case 29:
            printf("Jazz+Funk");
            break;
        case 30:
            printf("Fusion");
            break;
        case 31:
            printf("Trance");
            break;
        case 32:
            printf("Classical");
            break;
        case 33:
            printf("Instrumental");
            break;
        case 34:
            printf("Acid");
            break;
        case 35:
            printf("House");
            break;
        case 36:
            printf("Game");
            break;
        case 37:
            printf("Sound Clip");
            break;
        case 38:
            printf("Gospel");
            break;
        case 39:
            printf("Noise");
            break;
        case 40:
            printf("Alt. Rock");
            break;
        case 41:
            printf("Bass");
            break;
        case 42:
            printf("Soul");
            break;
        case 43:
            printf("Punk");
            break;
        case 44:
            printf("Space");
            break;
        case 45:
            printf("Meditative");
            break;
        case 46:
            printf("Instrumental Pop");
            break;
        case 47:
            printf("Instrumental Rock");
            break;
        case 48:
            printf("Ethnic");
            break;
        case 49:
            printf("Gothic");
            break;
        case 50:
            printf("Darkwave");
            break;
        case 51:
            printf("Techno-Industrial");
            break;
        case 52:
            printf("Electronic");
            break;
        case 53:
            printf("Pop-Folk");
            break;
        case 54:
            printf("Eurodance");
            break;
        case 55:
            printf("Dream");
            break;
        case 56:
            printf("Southern Rock");
            break;
        case 57:
            printf("Comedy");
            break;
        case 58:
            printf("Cult");
            break;
        case 59:
            printf("Gangsta Rap");
            break;
        case 60:
            printf("Top 40");
            break;
        case 61:
            printf("Christian Rap");
            break;
        case 62:
            printf("Pop/Funk");
            break;
        case 63:
            printf("Jungle");
            break;
        case 64:
            printf("Native American");
            break;
        case 65:
            printf("Cabaret");
            break;
        case 66:
            printf("New Wave");
            break;
        case 67:
            printf("Psychedelic");
            break;
        case 68:
            printf("Rave");
            break;
        case 69:
            printf("Showtunes");
            break;
        case 70:
            printf("Trailer");
            break;
        case 71:
            printf("Lo-Fi");
            break;
        case 72:
            printf("Tribal");
            break;
        case 73:
            printf("Acid Punk");
            break;
        case 74:
            printf("Acid Jazz");
            break;
        case 75:
            printf("Polka");
            break;
        case 76:
            printf("Retro");
            break;
        case 77:
            printf("Musical");
            break;
        case 78:
            printf("Rock & Roll");
            break;
        case 79:
            printf("Hard Rock");
            break;
        default:
            printf("Unknown");
            break;
    }
    printf("\n");
}

void read_id3(char *filename) {
    FILE *mp3File;
    Mp3Header header;
    id3Metadata metadata;

    mp3File = fopen(filename, "r");
    if (mp3File == NULL) {
        fprintf(stderr, "%s couldn't be opened. Check path and permissions.\n", filename);
        exit(3);
    }

    // read the header and metadata blocks into structs to access the info easily
    readMp3(mp3File, &header, &metadata);
    // get the filesize by moving to the end and printing the position in the file
    fseek(mp3File, 0, SEEK_END);
    printf("File size: %ld bytes\n", ftell(mp3File));
    // display all the data
    displayHeader(&header);
    displayMetadata(&metadata);

    fclose(mp3File);
}

void fill_id3(id3Metadata *metadata) {
    char buffer[2048]; // buffer for fgets
    int genre;
    /* can't strncpy because it causes a warning. IRL would totally do it, but because it's an
       assignment I'll be pedantic about it */
    metadata->tag[0] = 'T';
    metadata->tag[1] = 'A';
    metadata->tag[2] = 'G';
    
    // prompt for title
    printf("Title : \n");
    fgets(buffer, 2048, stdin);
    buffer[strlen(buffer)-1] = '\0'; // get rid of the trailing \n
    strncpy(metadata->title, buffer, 30);
    
    // prompt for artist
    printf("Artist : \n");
    fgets(buffer, 2048, stdin);
    buffer[strlen(buffer)-1] = '\0'; // get rid of the trailing \n
    strncpy(metadata->artist, buffer, 30);
    
    // prompt for album
    printf("Album : \n");
    fgets(buffer, 2048, stdin);
    buffer[strlen(buffer)-1] = '\0'; // get rid of the trailing \n
    strncpy(metadata->album, buffer, 30);
    
    // prompt for year
    printf("Year : \n");
    fgets(buffer, 2048, stdin);
    buffer[strlen(buffer)-1] = '\0'; // get rid of the trailing \n
    strncpy(metadata->year, buffer, 30);
    
    // prompt for comment
    printf("Comment : \n");
    fgets(buffer, 2048, stdin);
    buffer[strlen(buffer)-1] = '\0'; // get rid of the trailing \n
    strncpy(metadata->comment, buffer, 30);

    // prompt for genre number (and validate it)
    do {
        printf("Genre number: \n");
        fgets(buffer, 2048, stdin);
    } while (sscanf(buffer, "%d", &genre) == 0 || genre < -1 || genre > 79);
    metadata->genre = (char)genre;

}

void write_id3(char *filename) {
    FILE *mp3File;
    id3Metadata metadata;

    // r+ mode to be able to write to the end of the file without destroying the rest
    mp3File = fopen(filename, "r+");
    if (mp3File == NULL) {
        fprintf(stderr, "%s couldn't be opened. Check path and permissions.\n", filename);
        exit(5);
    }

    // read metadata from stdin
    fill_id3(&metadata);

    // write it to the file
    fseek(mp3File, -128, SEEK_END);
    fwrite(&metadata, sizeof(id3Metadata), 1, mp3File);

    // print out what was written to the file
    printf("\nTags written :\n");
    displayMetadata(&metadata);

    // don't forget to close the file...
    fclose(mp3File);
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Error, incorrect number of arguments\n");
        fprintf(stderr, "Usage: %s <mp3 file> <r/w>\n", argv[0]);
        return 1;
    }

    if (access(argv[1], F_OK) != 0) {
        fprintf(stderr, "Error, %s couldn't be opened\n", argv[1]);
        return 2;
    } else if (strcmp(argv[2], "w") == 0 || strcmp(argv[2], "W") == 0) {
        write_id3(argv[1]);
    } else if (strcmp(argv[2], "r") == 0 || strcmp(argv[2], "R") == 0) {
        read_id3(argv[1]);
    }

    return 0;
}