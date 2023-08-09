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
    //Checking for arguments
    if(argc == 1)
    {
        printf("Usage: ebuComp file1 file2\n");
        return SUCCESS;
    }
    //Creating a struct for the inputfile
    struct FileInfo* inputFile1 = (struct FileInfo*) malloc (sizeof(struct FileInfo));
    //Creating struct for inputfile1
    struct FileInfo* inputFile2= (struct FileInfo*) malloc (sizeof(struct FileInfo));
    if (argc != 3)
    //Checking for BAD Arguments
    {
        printf("ERROR: Bad Arguments\n");
        return BAD_ARGS;
    }
    //Initializing the input file values
    initialise_file(inputFile1);
    //Opening the inputfile1
    inputFile1->file = fopen(argv[1], "r");
    int check;
    //Checking for bad file
    check = BadFile(inputFile1, argv[1]);
    if (check == BAD_FILE)
    {
        return check;
    }
    //Getting magic number
    getMagic(inputFile1);
    //Checking the magic number
    check = CheckMagicB(inputFile1, argv[1]);
    if (check == BAD_MAGIC_NUMBER)
    {
        return check;
    }
    //Checking bad dimensions
    check = BadDimension(inputFile1, argv[1]);
    if (check == BAD_DIM)
    {
        return check;
    }
    //Checking for malloc
    check = BadMalloc2C(inputFile1);
    if (check == BAD_MALLOC)
    {
        return check;
    }
    //Reading in binary
    check = readBinary(inputFile1, argv[1]);
    if (check == BAD_DATA)
    {
        return check;
    }
    //closing the inputfile1
    fclose(inputFile1->file);
    //Initialize values for inputfile2
    initialise_file(inputFile2);
    //Opening the inputfile2
    inputFile2->file = fopen(argv[2], "r");
    //Checkign for bad file
    check = BadFile(inputFile2, argv[2]);
    if (check == BAD_FILE)
    {
        return check;
    }
    //Getting magic number
    getMagic(inputFile2);
    //Checking for bad magic number
    check = CheckMagicB(inputFile2, argv[2]);
    if (check == BAD_MAGIC_NUMBER)
    {
        return check;
    }
    //Checking for bad dimensions
    check = BadDimension(inputFile2, argv[2]);
    if (check == BAD_DIM)
    {
        return check;
    }
    //Checking for malloc
    check = BadMalloc2C(inputFile2);
    if (check == BAD_MALLOC)
    {
        return check;
    }
    //Reading in binary
    check = readBinary(inputFile2, argv[2]);
    if (check == BAD_DATA)
    {
        return check;
    }
    //Closing the inputfile2
    fclose(inputFile2->file);
    // compare the data from the two files:
    // start with magic number values
    if (*inputFile1->magicNumberValue != *inputFile2->magicNumberValue)
    {
        free(inputFile1->imageData2B);
        free(inputFile2->imageData2B);
        printf("DIFFERENT\n");
        return SUCCESS;
    }
    //Checking for height and width
    if ((inputFile1->height != inputFile2->height) || (inputFile1->width!= inputFile2->width))
    {
        free(inputFile1->imageData2B);
        free(inputFile2->imageData2B);
        printf("DIFFERENT\n");
        return SUCCESS;
    }
    //and check the pixel values
    for (int i=0; i<inputFile1->height; i++)
    {
        for(int j=0; j<inputFile1->width; j++)
        {
            if(inputFile1->imageData2B[i][j]!=inputFile2->imageData2B[i][j])
            {
                free(inputFile1->imageData2B);
                free(inputFile2->imageData2B);
                printf("DIFFERENT\n");
                return SUCCESS;
            }        
        }
    }
    //free allocated memory before exit
    free(inputFile1->imageData2B);
    free(inputFile2->imageData2B);
    // if we have not exited on different data, must be identical
    printf("IDENTICAL\n");
    return SUCCESS;
}