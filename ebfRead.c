#include <stdlib.h>
#include <stdio.h>
#include "FileInfo.h"
#include "ebfRead.h"

/**
    Checks if the file associated with the given file information structure is valid.
    @param values The pointer to the FileInfo struct containing file information.
    @param filename The name of the file being checked.
    @return Returns SUCCESS if the file is valid, otherwise returns BAD_FILE.
    @remarks This function verifies if the file pointer within the struct FileInfo is not NULL.
    If the file pointer is NULL, it prints an error message indicating a bad file name and returns BAD_FILE.
    Otherwise, it returns SUCCESS to indicate a valid file.
    */

int BadFile(struct FileInfo* values, char *filename)
{
    //Checks for NULL file
    if (values->file == NULL)
    {
        //check file pointer
        printf("ERROR: Bad File Name (%s)\n", filename);
        return BAD_FILE;
    }
    return SUCCESS;
}

/**
    Retrieves the magic number from the file associated with the given file information structure.
    @param values The pointer to the FileInfo struct containing file information.
    @remarks This function reads the first two bytes from the file and assigns them to the magicNumber array
    within the struct FileInfo. It also assigns the address of the magicNumber array to the magicNumberValue pointer.
    The magic number is used to identify the format or file type.
    */

void getMagic(struct FileInfo *values)
{
    values->magicNumberValue = (unsigned short *)values->magicNumber;
    values->magicNumber[0] = getc(values->file);
    values->magicNumber[1] = getc(values->file);
}

/**
    Checks if the magic number of the file associated with the given file information structure is valid.
    @param values The pointer to the FileInfo struct containing file information.
    @param filename The name of the file being checked.
    @return Returns SUCCESS if the magic number is valid, otherwise returns BAD_MAGIC_NUMBER.
    @remarks This function compares the value of the magicNumberValue pointer within the FileInfo struct
    with the predefined constant MAGIC_NUMBER. If the values do not match, it prints an error message
    indicating a bad magic number and returns BAD_MAGIC_NUMBER. Otherwise, it returns SUCCESS to indicate
    a valid magic number.
    */

int CheckMagic(struct FileInfo* values, char *filename)
{
    //Checks for magic number
    if ((*values->magicNumberValue) != MAGIC_NUMBER)
    {
        //check magic number
        printf("ERROR: Bad Magic Number (%s)\n", filename);
        return BAD_MAGIC_NUMBER;
    }
    return SUCCESS;
}

/**
    Checks if the magic number of the file associated with the given file information structure is valid.
    @param values The pointer to the FileInfo struct containing file information.
    @param filename The name of the file being checked.
    @return Returns SUCCESS if the magic number is valid, otherwise returns BAD_MAGIC_NUMBER.
    @remarks This function compares the value of the magicNumberValue pointer within the FileInfo struct
    with the predefined constant MAGIC_NUMBER. If the values do not match, it prints an error message
    indicating a bad magic number and returns BAD_MAGIC_NUMBER. Otherwise, it returns SUCCESS to indicate
    a valid magic number.
    */

int CheckMagicB(struct FileInfo* values, char *filename)
{
    //Checking for magic number
    if ((*values->magicNumberValue) != MAGIC_NUMBER_B)
    {
        //check magic number
        printf("ERROR: Bad Magic Number (%s)\n", filename);
        return BAD_MAGIC_NUMBER;
    }
    return SUCCESS;
}

/**
    Checks if the magic number of the file associated with the given file information structure is valid.
    @param values The pointer to the FileInfo struct containing file information.
    @param filename The name of the file being checked.
    @return Returns SUCCESS if the magic number is valid, otherwise returns BAD_MAGIC_NUMBER.
    @remarks This function compares the value of the magicNumberValue pointer within the FileInfo struct
    with the predefined constant MAGIC_NUMBER. If the values do not match, it prints an error message
    indicating a bad magic number and returns BAD_MAGIC_NUMBER. Otherwise, it returns SUCCESS to indicate
    a valid magic number.
    */

int CheckMagicC(struct FileInfo* values, char *filename)
{
    //Checking for magic number
    if ((*values->magicNumberValue) != MAGIC_NUMBER_C)
    {
        //check magic number
        printf("ERROR: Bad Magic Number (%s)\n", filename);
        return BAD_MAGIC_NUMBER;
    }
    return SUCCESS;
}

/**
    Checks if the dimensions of the image file associated with the given file information structure are valid.
    @param values The pointer to the FileInfo struct containing file information.
    @param filename The name of the file being checked.
    @return Returns SUCCESS if the dimensions are valid, otherwise returns BAD_DIM.
    @remarks This function reads the height and width values from the file using fscanf. It checks if the fscanf
    successfully read both values and if the height and width are within the range of  MIN_DIMENSION and MAX_DIMENSION. 
    If these conditions are not satisfied, it closes the file, prints an error message indicating bad dimensions, 
    and returns BAD_DIM. Otherwise, it returns SUCCESS to indicate valid dimensions.
    */

int BadDimension(struct FileInfo *values, char *filename)
{
    //Reading height and width values
    values->check = fscanf(values->file, "%d %d", &(values->height), &(values->width));
    if (values->check != 2 || values->height < MIN_DIMENSION || values->width < MIN_DIMENSION || values->height > MAX_DIMENSION || values->width > MAX_DIMENSION)
    {
        fclose(values->file);
        printf("ERROR: Bad Dimensions (%s)\n", filename);
        return BAD_DIM;
    }
    return SUCCESS;
}

/**
    Allocates memory for the image data array in the given file information structure and performs necessary assignments.
    @param values The pointer to the FileInfo struct containing file information.
    @return Returns SUCCESS if memory allocation is successful, otherwise returns BAD_MALLOC.
    @remarks This function calculates the total number of bytes required to store the imageData based on the height
    and width values. It then allocates memory for the imageData array using malloc, with each element of the array
    representing a row of image data. It also allocates a memory block of the same size to store the actual image data.
    The imageData pointers are then assigned to the respective rows of the memory block. If the memory allocation
    fails at any step, it prints an error message indicating image malloc failure and returns BAD_MALLOC. Otherwise,
    it returns SUCCESS to indicate successful memory allocation.
    */

int BadMalloc(struct FileInfo *values)
{
    //Storing the value of numbytes
    values->numBytes = values->height * values->width;
    //Creating an array
    values->imageData = (unsigned int **)malloc(values->numBytes * sizeof(unsigned int *));
    //Creating a memory block for the array
    unsigned int* memoryblock = (unsigned int *)malloc(values->numBytes * sizeof(unsigned int));
    //Checking if the memory block is NULL
    if(memoryblock == NULL)
    {
        printf("ERROR: Image Malloc Failed\n");
        return BAD_MALLOC;
    }
    for(int i=0; i<values->height; i++)
    {
        values->imageData[i] = memoryblock + (i*values->width);
    }
    //if malloc is unsuccessful, it will return a null pointer
    if (values->imageData == NULL)
    {
        //check malloc
        printf("ERROR: Image Malloc Failed\n");
        return BAD_MALLOC;
    }
    return SUCCESS;
}

/**
    Checks if the pixel data of the image file associated with the given file information structure is valid.
    @param values The pointer to the FileInfo struct containing file information.
    @param filename The name of the file being checked.
    @return Returns SUCCESS if the pixel data is valid, otherwise returns BAD_DATA.
    @remarks This function reads each pixel value from the file and assigns it to the corresponding element
    in the imageData array. It checks if the pixel value exceeds the maximum allowed value of 31. If so,
    it frees the allocated imageData memory, closes the file, prints an error message indicating bad data,
    and returns BAD_DATA. It also checks for the operation of fscanf. In such cases, it frees the allocated imageData
    memory, closes the file, prints an error message indicating bad data, and returns BAD_DATA. If all the pixel
    values are successfully read and there are no extra values in the file, it returns SUCCESS to indicate valid data.
    */

int BadData(struct FileInfo *values, char *filename)
{
    //read in each grey value from the file
    values->Row = 0, values->Col = 0;
    for (values->Row = 0; values->Row < values->height; values->Row++)
    {
        for (values->Col = 0; values->Col < values->width; values->Col++)
        {
            //Reading the pixel values
            values->check = fscanf(values->file, "%u", &(values->imageData[values->Row][values->Col]));
            //Checkign for greater pixel values
            if (values->imageData[values->Row][values->Col] > 31)
            {
                //Closing and freeing the values
                free(values->imageData);
                fclose(values->file);
                printf("ERROR: Bad Data (%s)\n", filename);
                return BAD_DATA;
            }
            if (values->check != 1)
            {
                //ensure that allocated data is freed before exit.
                free(values->imageData);
                fclose(values->file);
                printf("ERROR: Bad Data (%s)\n", filename);
                return BAD_DATA;
            }
            if (values->Row == values->height - 1 && values->Col == values->width - 1 && fscanf(values->file, "%u", &(values->check)) == 1)
            {
                //ensure that allocated data is freed before exit.
                free(values->imageData);
                fclose(values->file);
                printf("ERROR: Bad Data (%s)\n", filename);
                return BAD_DATA;
            }
        }
    }
    return SUCCESS;
}

/**
    Initializes the file information structure with default values.
    @param values The pointer to the struct FileInfo to be initialized.
    @remarks This function sets all the variables of the struct FileInfo to their default values.
    It sets the width, height, numBytes, check, Row, and Col members to 0, ensuring a clean slate
    before populating the structure with actual file information.
    */

void initialise_file(struct FileInfo* values)
{
    values->width = 0;
    values->height = 0;
    values->numBytes = 0;
    values->check = 0;
    values->Row = 0;
    values->Col = 0;
}

/**
    Allocates memory for the image data array in the given file information structure and performs necessary assignments.
    @param values The pointer to the FileInfo struct containing file information.
    @return Returns SUCCESS if memory allocation is successful, otherwise returns BAD_MALLOC.
    @remarks This function calculates the total number of bytes required to store the imageData based on the height
    and width values. It then allocates memory for the imageData array using malloc, with each element of the array
    representing a row of image data. It also allocates a memory block of the same size to store the actual image data.
    The imageData pointers are then assigned to the respective rows of the memory block. If the memory allocation
    fails at any step, it prints an error message indicating image malloc failure and returns BAD_MALLOC. Otherwise,
    it returns SUCCESS to indicate successful memory allocation.
    */

int BadMalloc2C(struct FileInfo *values)
{
    //Storing the values of numBytes
    values->numBytes = values->height * values->width;
    values->x = (unsigned int *) malloc(values->numBytes * sizeof(unsigned int));
    //Creating an array
    values->imageData2B = (unsigned char **)malloc(values->numBytes * sizeof(unsigned char *));
    //Creating a memory block
    unsigned char* memoryblock = (unsigned char *)malloc(values->numBytes * sizeof(unsigned char));
    //Checking for memory block for NULL
    if(memoryblock == NULL)
    {
        printf("ERROR: Image Malloc Failed\n");
        return BAD_MALLOC;
    }
    for(int i=0; i<values->height; i++)
    {
        values->imageData2B[i] = memoryblock + (i*values->width);
    }
    if (values->imageData2B == NULL)
    {
        // check malloc
        printf("ERROR: Image Malloc Failed\n");
        return BAD_MALLOC;
    }
    return SUCCESS;
}

/**
    Allocates memory for the image data array in the given file information structure and performs necessary assignments.
    @param values The pointer to the FileInfo struct containing file information.
    @return Returns SUCCESS if memory allocation is successful, otherwise returns BAD_MALLOC.
    @remarks This function calculates the total number of bytes required to store the imageData based on the height
    and width values. It then allocates memory for the imageData array using malloc, with each element of the array
    representing a row of image data. It also allocates a memory block of the same size to store the actual image data.
    The imageData pointers are then assigned to the respective rows of the memory block. If the memory allocation
    fails at any step, it prints an error message indicating image malloc failure and returns BAD_MALLOC. Otherwise,
    it returns SUCCESS to indicate successful memory allocation.
    */

int BadMalloc2Cebc(struct FileInfo *values)
{
    //Storing the values in numBytes
    values->numBytes = (values->height * values->width);
    //Creating an array
    values->imageData2C = (unsigned char **)malloc(values->numBytes * sizeof(unsigned char *));
    //Creating a memoryblock
    unsigned char* memoryblock = (unsigned char *)malloc(values->numBytes * sizeof(unsigned char));
    //Checking for memoryblock for NULL
    if(memoryblock == NULL)
    {
        printf("ERROR: Image Malloc Failed\n");
        return BAD_MALLOC;
    }
    for(int i=0; i<values->height; i++)
    {
        values->imageData2C[i] = memoryblock + (i*values->width);
    }
    //if malloc is unsuccessful, it will return a null pointer
    if (values->imageData2C == NULL)
    {
        printf("ERROR: Image Malloc Failed\n");
        return BAD_MALLOC;
    }
    return SUCCESS;
}

/**
    Reads binary data from the file and stores the image data array in the given file information structure.
    @param values The pointer to the FileInfo struct containing file information.
    @param filename The name of the file being read.
    @return Returns SUCCESS if the binary data is successfully read and processed, otherwise returns BAD_DATA.
    @remarks This function reads binary data from the file and assigns it to the imageData2B array within the
    FileInfo struct. It reads each byte of data using "fread" and assigns it to the element in the
    imageData2B array.If a pixel value is found to be greater than 31, it frees the allocated imageData2B memory,
    closes the file, prints an error message indicating bad data, and returns BAD_DATA. It also checks for the 
    success of the fread operation. In such cases, it frees the allocated imageData2B memory, closes the file, 
    prints an error message indicating bad data, and returns BAD_DATA.
    If all the binary data is successfully read and there are no extra values in the file, it returns SUCCESS
    to indicate successful reading of binary data.
    */

int readBinary(struct FileInfo *values, char *filename)
{
    unsigned char readNewLine;
    fread(&readNewLine, sizeof(unsigned char), 1, values->file);
    //read in each grey value from the file
    values->Row = 0, values->Col = 0;
    for (values->Row = 0; values->Row < values->height; values->Row++)
    {
        for (values->Col = 0; values->Col < values->width; values->Col++)
        {
            //Reading the values in binary
            values->check = fread(&(values->imageData2B[values->Row][values->Col]), sizeof(unsigned char), 1 , values->file);
            //Checking if the pixel value is greater than 31
            if (values->imageData2B[values->Row][values->Col] > 31)
            {
                //ensure that allocated data is freed before exit.
                free(values->imageData2B);
                fclose(values->file);
                printf("ERROR: Bad Data (%s)\n", filename);
                return BAD_DATA;
            }
            //Checking the value of 1
            if (values->check != 1) 
            {
                // ensure that allocated data is freed before exit.
                free(values->imageData2B);
                fclose(values->file);
                printf("ERROR: Bad Data (%s)\n", filename);
                return BAD_DATA;
            }
            //Checking for too high and too low
            if (values->Row == values->height - 1 && values->Col == values->width - 1 && fscanf(values->file, "%u", &(values->check)) == 1) 
            {
                //ensure that allocated data is freed before exit.
                free(values->imageData2B);
                fclose(values->file);
                printf("ERROR: Bad Data (%s)\n", filename);
                return BAD_DATA;
            }
        }
    }
    return SUCCESS;
}

/**
    Reads binary data from the file and stores the image data array in the given file information structure.
    @param values The pointer to the FileInfo struct containing file information.
    @param filename The name of the file being read.
    @return Returns SUCCESS if the binary data is successfully read and processed, otherwise returns BAD_DATA.
    @remarks This function reads binary data from the file and assigns it to the imageData2C array within the
    FileInfo struct. It reads each byte of data using "fread" and assigns it to the element in the
    imageData2C array.If a pixel value is found to be greater than 31, it frees the allocated imageData2C memory,
    closes the file, prints an error message indicating bad data, and returns BAD_DATA. It also checks for the 
    success of the fread operation. In such cases, it frees the allocated imageData2C memory, closes the file, 
    prints an error message indicating bad data, and returns BAD_DATA.
    If all the binary data is successfully read and there are no extra values in the file, it returns SUCCESS
    to indicate successful reading of binary data.
    */

int readBinaryebc(struct FileInfo *values, char *filename)
{
    //read in each grey value from the file
    values->Row = 0, values->Col = 0;
    for (values->Row = 0; values->Row < values->height; values->Row++)
    {
        for (values->Col = 0; values->Col < values->width; values->Col++)
        {
            //Reading the values in binary
            values->check = fread(&(values->imageData2C[values->Row][values->Col]), 1, 1 , values->file);
            if (values->check != 1)
            {
                //ensure that allocated data is freed before exit.
                free(values->imageData2C);
                fclose(values->file);
                printf("ERROR: Bad Data (%s)\n", filename);
                return BAD_DATA;
            }
        }
    }
    return SUCCESS;
}