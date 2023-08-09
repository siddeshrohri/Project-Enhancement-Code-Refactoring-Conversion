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
#define MAGIC_NUMBER_B 0x7565
#define MAGIC_NUMBER_C 0x6365
#define DECIMAL 5/8

void getMagic(struct FileInfo *values);
int BadFile(struct FileInfo *values, char *filename);
int CheckMagic(struct FileInfo *values, char *filename);
int BadDimension(struct FileInfo *values, char *filename);
int BadMalloc(struct FileInfo *values);
int BadData(struct FileInfo *values, char *filename);
void initialise_file(struct FileInfo* values);
int readBinary(struct FileInfo* values, char *filename);
int BadMalloc2C(struct FileInfo *values);
int CheckMagicB(struct FileInfo* values, char *filename);
int CheckMagicC(struct FileInfo* values, char *filename);
int readBinaryebc(struct FileInfo *values, char *filename);
int BadMalloc2Cebc(struct FileInfo *values);
int readASCII(struct FileInfo *values, char *filename);
