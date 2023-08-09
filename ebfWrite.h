#include <stdlib.h>
#include <stdio.h>
#include "FileInfo.h"

#define SUCCESS 0
#define BAD_ARGS 1
#define BAD_FILE 2
#define BAD_MAGIC_NUMBER 3
#define BAD_DIM 4
#define BAD_MALLOC 5
#define BAD_DATA 6
#define BAD_OUTPUT 7
#define MAGIC_NUMBER 0x6265
#define MAX_DIMENSION 262144
#define MIN_DIMENSION 1


int BadOutput(struct FileInfo *values, char *filename, struct FileInfo *values2);
int checkValues(struct FileInfo *values,char *filename, struct FileInfo *values2);
int writeBinary(struct FileInfo *values, char *filename, struct FileInfo *values2);
int TOASCII(struct FileInfo *values, char *filename, struct FileInfo *values2);
int TOBINARY(struct FileInfo *values, char *filename, struct FileInfo *values2);
int writeBinaryebc(struct FileInfo *values, char *filename, struct FileInfo *values2);
void writeTwiddledBits(struct FileInfo* values, unsigned int imageData, int* increment, int* counter, unsigned int* twiddled);
void writePixel(struct FileInfo* values, char* filename, struct FileInfo* values2, unsigned int pi);
int writeImageData(struct FileInfo* values, char* filename, struct FileInfo* values2);
void writeHeader(struct FileInfo* values);
int writeImageDataBinary(struct FileInfo* values, struct FileInfo* values2);
void writeHeaderASCII(struct FileInfo* values);
int writeImageDataASCII(struct FileInfo* values, struct FileInfo* values2);
void writeBinaryHeader(struct FileInfo* values);
int writeBinaryData(struct FileInfo* values, struct FileInfo* values2);