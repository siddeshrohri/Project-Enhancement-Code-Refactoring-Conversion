#ifndef FILEINFO
#define FILEINFO

typedef struct FileInfo{
    unsigned char magicNumber[2];
    unsigned short *magicNumberValue;
    int width;
    int height;
    long numBytes;
    unsigned int **imageData;
    int check;
    int Row;
    int Col;
    unsigned char **imageData2B;
    unsigned char **imageData2C;
    unsigned int *x;
    FILE *file;

}FileInfo;
#endif