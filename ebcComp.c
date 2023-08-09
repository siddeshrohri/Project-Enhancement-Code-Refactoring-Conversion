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
    Allocates memory to the inputfile1 and inputfile2.
    Initializes the values of the inputfile1.
    Checks for BAD arguments . If true, prints out the message along with the return of BAD_ARGS.
    Opens the inputfile, Checks for BadFile, MagicNumber, BadDimensions, Malloc and BadData. Closes the inputfile.
    Opens the outputfile, Checks for BadFile, writes the output using BadOutput. Closes both the files and frees the 
    data within the files.
    Initializes the values of the inputfile2.
    Checks for BAD arguments . If true, prints out the message along with the return of BAD_ARGS.
    Opens the inputfile, Checks for BadFile, MagicNumber, BadDimensions, Malloc and BadData. Closes the inputfile.
    Opens the outputfile, Checks for BadFile, writes the output using BadOutput. Closes both the files and frees the 
    data within the files.
    Checks whether the files are different and prints out "DIFFERENT"
    Prints "IDENTICAL"
    Returns SUCCESS.
    */

int main(int argc, char **argv)
{

    // validate that user has enter 2 arguments (plus the executable name)
    if(argc == 1)
    {
        printf("Usage: ebcComp file1 file2\n");
        return SUCCESS;
    }
    if (argc != 3)
    { // check arg count
        printf("ERROR: Bad Arguments\n");
        return BAD_ARGS;
    } // check arg count
    struct FileInfo* inputFile1 = (struct FileInfo*) malloc (sizeof(struct FileInfo));
    initialise_file(inputFile1);
    inputFile1->file = fopen(argv[1], "rb");
    int check;
    check = BadFile(inputFile1, argv[1]);
    if (check == BAD_FILE)
    {
        return check;
    }
    getMagic(inputFile1);
    check = CheckMagicC(inputFile1, argv[1]);
    if (check == BAD_MAGIC_NUMBER)
    {
        return check;
    }
    check = BadDimension(inputFile1, argv[1]);
    if (check == BAD_DIM)
        {
        return check;
    }
    check = BadMalloc2Cebc(inputFile1);
    if (check == BAD_MALLOC)
    {
        return check;
    }
    check = readBinaryebc(inputFile1, argv[1]);
    if(check == BAD_DATA)
    {
        return check;
    }
    fclose(inputFile1->file);

    struct FileInfo* inputFile2= (struct FileInfo*) malloc (sizeof(struct FileInfo));
    initialise_file(inputFile2);
    //create a char array to hold magic number
    inputFile2->file = fopen(argv[2], "rb");

    check = BadFile(inputFile2, argv[2]);
    if (check == BAD_FILE)
    {
        return check;
    }
    getMagic(inputFile2);
    check = CheckMagicC(inputFile2, argv[2]);
    if (check == BAD_MAGIC_NUMBER)
    {
        return check;
    }
    check = BadDimension(inputFile2, argv[2]);
    if (check == BAD_DIM)
    {
        return check;
    }
    check = BadMalloc2C(inputFile2);
    if (check == BAD_MALLOC)
    {
        return check;
    }

    check = readBinaryebc(inputFile2, argv[2]);
    if(check == BAD_DATA)
    {
        return check;
    }

    fclose(inputFile2->file);
    // compare the data from the two files:
    // start with magic number values
    if (*inputFile1->magicNumberValue != *inputFile2->magicNumberValue)
    {
        free(inputFile1->imageData2C);
        free(inputFile2->imageData2C);
        printf("DIFFERENT\n");
        return SUCCESS;
    }

    // check dimensions
    if ((inputFile1->height != inputFile2->height) || (inputFile1->width!= inputFile2->width))
    {
        free(inputFile1->imageData2C);
        free(inputFile2->imageData2C);
        printf("DIFFERENT\n");
        return SUCCESS;
    }

    // and check the pixel values
    for (int i=0; i<inputFile1->height; i++)
    {
        for(int j=0; j<inputFile1->width; j++)
        {
        if(inputFile1->imageData2C[i][j]!=inputFile2->imageData2C[i][j])
        {
            free(inputFile1->imageData2C);
            free(inputFile2->imageData2C);
            printf("DIFFERENT\n");
            return SUCCESS;
        }        
        }
    }

    // free allocated memory before exit
    free(inputFile1->imageData2C);
    free(inputFile2->imageData2C);

    // if we have not exited on different data, must be identical
    printf("IDENTICAL\n");
    return SUCCESS;
}