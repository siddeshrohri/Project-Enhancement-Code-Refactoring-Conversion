#include <stdio.h>
#include <stdlib.h>
#include "FileInfo.h"
#include "ebfRead.h"
#include "ebfWrite.h"
/**
    Entry point of the program.
    @param argc The number of command-line arguments.
    @param argv An array of strings containing the command-line arguments.
    @return Returns SUCCESS if the program executes successfully, otherwise returns an appropriate error code.
    @remarks This function is the main entry point of the program. It performs the following actions:
    Checks if the correct number of command-line arguments is provided. If not, then prints a message along with returning 
    SUCCESS
    Allocates memory to the inputfile and outputfile.
    Initializes the values of the inputfile.
    Checks for BAD arguments . If true, prints out the message along with the return of BAD_ARGS.
    Opens the inputfile, Checks for BadFile, MagicNumber, BadDimensions, Malloc and BadData. Closes the inputfile.
    Opens the outputfile, Checks for BadFile, writes the output using BadOutput. Closes both the files and frees the 
    data within the files. 
    Prints "ECHOED" indicating the successful execution of the program.
    Returns SUCCESS.
    */

int main(int argc, char **argv)
{
    struct FileInfo* inputFile = (struct FileInfo*) malloc (sizeof(struct FileInfo));
    initialise_file(inputFile);
    if(argc == 1)
    {
        printf("Usage: ebcEcho file1 file2\n");
        return SUCCESS;
    }
    if (argc != 3)
    {
        printf("ERROR: Bad Arguments\n");
         return BAD_ARGS;
    }

    inputFile->file = fopen(argv[1], "rb");
    int check;
    check = BadFile(inputFile, argv[1]);
    if (check == BAD_FILE)
    {
        return check;
    }
    getMagic(inputFile);
    check = CheckMagicC(inputFile, argv[1]);
    if (check == BAD_MAGIC_NUMBER)
    {
        return check;
    }
    check = BadDimension(inputFile, argv[1]);
    if (check == BAD_DIM)
    {
        return check;
    }

    check = BadMalloc2Cebc(inputFile);
    if (check == BAD_MALLOC)
    {
        return check;
    }
    check = readBinaryebc(inputFile, argv[1]);
    if(check == BAD_DATA)
    {
        return check;
    }
    fclose(inputFile->file);
    struct FileInfo* outputFile = (struct FileInfo*) malloc (sizeof(struct FileInfo));
    initialise_file(outputFile);
    outputFile->file = fopen(argv[2], "wb");

    check = BadFile(outputFile, argv[2]);
    if (check == BAD_FILE)
    {
        return check;
    }

    check  = writeBinaryebc(inputFile, argv[2], outputFile);
    if (check == BAD_OUTPUT)
    {
        return check;
    }

    fclose(outputFile->file);
    free(inputFile);
    free(outputFile);
    printf("ECHOED\n");
    return SUCCESS;
    
}
