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
    //Checking for arguments
    if(argc == 1)
    {
        printf("Usage: ebfEcho file1 file2");
        return SUCCESS;
    }
    //Creating a struct for the inputfile
    struct FileInfo* inputFile = (struct FileInfo*) malloc (sizeof(struct FileInfo));
    //Creating a struct for outputfile
    struct FileInfo* outputFile = (struct FileInfo*) malloc (sizeof(struct FileInfo));
    //Initializing the input file values
    initialise_file(inputFile);
    //Checking for BAD Arguments
    if (argc != 3)
    {
        //check arg count
        printf("ERROR: Bad Arguments\n");
        return BAD_ARGS;

    }
    //Opening the inputfile
    inputFile->file = fopen(argv[1], "r");
    int check;
    //Checking for bad file
    check = BadFile(inputFile, argv[1]);
    if (check == BAD_FILE)
    {
        return check;
    }
    //Getting magic number values
    getMagic(inputFile);
    //Checking for magic number
    check = CheckMagic(inputFile, argv[1]);
    if (check == BAD_MAGIC_NUMBER)
    {
        return check;
    }
    //Checking for bad dimensions
    check = BadDimension(inputFile, argv[1]);
    if (check == BAD_DIM)
    {
        return check;
    }
    //Checking fro bad malloc
    check = BadMalloc(inputFile);
    if (check == BAD_MALLOC)
    {
        return check;
    }
    //Checking for bad data
    check = BadData(inputFile, argv[1]);
    if (check == BAD_DATA)
    {
        return check;
    }
    //Closing the inputfile
    fclose(inputFile->file);
    //Initializing the outputfile
    initialise_file(outputFile);
    //Opening the outputfile
    outputFile->file = fopen(argv[2], "w");
    //Checking for the bad file
    check = BadFile(outputFile, argv[2]);
    if (check == BAD_FILE)
    {
        return check;
    }
    //Checking for bad output
    if(BadOutput(inputFile, argv[2], outputFile) == BAD_OUTPUT)
    {
        return BAD_OUTPUT;
    }
    //Closing the output file
    fclose(outputFile->file);
    //Free the inputfile file
    free(inputFile);
    //Free the outputfile
    free(outputFile);
    //Printing ECHOED
    printf("ECHOED\n");
    return SUCCESS;
}
