#include <stdlib.h>
#include <stdio.h>
#include "FileInfo.h"
#include "ebfWrite.h"
#include "ebfRead.h"

/**
    Writes the image data to a file and checks for any errors in the output.
    @param values The pointer to the FileInfo struct containing file information.
    @param filename The name of the file being read.
    @param values2 The pointer to the FileInfo struct containing file information.
    @return Returns SUCCESS if the image data is successfully written, otherwise BAD_OUTPUT.
    @remarks This function writes the image data, along with the height and width, to a file specified by the filename
    parameter. It uses the fprintf function to write the data and stores the return value in "check" to check for
    any writing errors. If an error occurs during writing, the function returns BAD_OUTPUT.
    The function iterates over each pixel in the image data and writes it to the file.
    If a writing error occurs during the iteration, it closes the file pointed to by file, frees the memory 
    allocated for imageData.Prints an error message indicating a bad output with the corresponding filename.Returns BAD_OUTPUT.
    If the writing process is successful for the entire image data, the function returns SUCCESS.
    */

int BadOutput(struct FileInfo* values, char* filename, struct FileInfo* values2) 
{
    int result = writeImageData(values, filename, values2);
    if (result == BAD_OUTPUT) 
    {
        return BAD_OUTPUT;
    }

    return SUCCESS;
}
int writeImageData(struct FileInfo* values, char* filename, struct FileInfo* values2) 
{
    values->check = fprintf(values2->file, "eb\n%d %d\n", values->height, values->width);
    if (checkValues(values, filename, values2)) 
    {
        return BAD_OUTPUT;
    }
    values->Row = 0, values->Col = 0;
    for (values->Row = 0; values->Row < values->height; values->Row++) 
    {
        for (values->Col = 0; values->Col < values->width; values->Col++) 
        {
            writePixel(values, filename, values2, values->imageData[values->Row][values->Col]);
        }
    }

    return SUCCESS;
}
void writePixel(struct FileInfo* values, char* filename, struct FileInfo* values2, unsigned int pi) 
{
    if (values->Row != values->height - 1 || values->Col != values->width - 1) 
    {
        values->check = fprintf(values2->file, "%u%c", pi, (values->Col == values->width - 1) ? '\n' : ' ');
    } 
    else 
    {
        values->check = fprintf(values2->file, "%u", pi);
    }
    checkValues(values, filename, values2);
}

/**
    Checks for any errors in the output during the writing process.
    @param values The pointer to the FileInfo struct containing file information.
    @param filename The name of the file being read.
    @param values2 The pointer to the FileInfo struct containing file information.
    @return Returns SUCCESS if the output is valid, otherwise BAD_OUTPUT.
    @remarks This function is called to check if any errors occurred during the writing process in the BadOutput function.
    It verifies the value of values->check to determine if any error occurred during the writing of the image data.
    If values->check is equal to 0, it indicates a writing error.
    If a writing error occurs during the iteration, it closes the file pointed to by file, frees the memory 
    allocated for imageData.Prints an error message indicating a bad output with the corresponding filename.
    If no writing errors are detected, the function returns SUCCESS.
    */

int checkValues(struct FileInfo *values,char *filename, struct FileInfo *values2)
{
    if (values->check == 0)
    {
        fclose(values->file);
        fclose(values2->file);
        free(values->imageData);
        free(values->imageData2B);
        printf("ERROR: Bad Output (%s)\n", filename);
    }
    return SUCCESS;
}

/**
    Writes the image data in binary format to a file and checks for any errors in the output.
    @param values The pointer to the FileInfo struct containing file information.
    @param filename The name of the file being read.
    @param values2 The pointer to the FileInfo struct containing file information.
    @return Returns SUCCESS if the binary image data is successfully written, otherwise BAD_OUTPUT.
    @remarks This function writes the image data in binary format. It starts by writing the height and width information 
    to the file using the fprintf function. The return value of fprintf is stored in check to check for any writing errors. 
    If an error occurs during writing, the function returns BAD_OUTPUT.
    If a writing error occurs during the iteration, it closes the file pointed to by file, frees the memory 
    allocated for imageData.Prints an error message indicating a bad output with the corresponding filename.
    If the writing process is successful for the entire binary image data, the function returns SUCCESS.
    */

int writeBinary(struct FileInfo* values, char* filename, struct FileInfo* values2) 
{
    writeHeader(values);
    if (checkValues(values, filename, values2)) 
    {
        return BAD_OUTPUT;
    }

    int result = writeImageDataBinary(values, values2);
    if (result == BAD_OUTPUT) 
    {
        return BAD_OUTPUT;
    }

    return SUCCESS;
}
void writeHeader(struct FileInfo* values) 
{
    fprintf(values->file, "eu\n%d %d\n", values->height, values->width);
}

int writeImageDataBinary(struct FileInfo* values, struct FileInfo* values2) 
{
    for (values->Row = 0; values->Row < values->height; values->Row++) 
    {
        for (values->Col = 0; values->Col < values->width; values->Col++) 
        {
            if (fwrite(&values->imageData2B[values->Row][values->Col], sizeof(unsigned char), 1, values2->file) != 1) {
                return BAD_OUTPUT;
            }
        }
    }
    return SUCCESS;
}

/**
    Writes the image data in ASCII format to a file and checks for any errors in the output.
    @param values The pointer to the FileInfo struct containing file information.
    @param filename The name of the file being read.
    @param values2 The pointer to the FileInfo struct containing file information.
    @return Returns SUCCESS if the ASCII image data is successfully written, otherwise BAD_OUTPUT.
    @remarks This function writes the image data in ASCII format. It starts by writing the height and width information 
    to the file using the fprintf function. The return value of fprintf is stored in check to check for any writing errors. 
    If an error occurs during writing, the function returns BAD_OUTPUT.
    If a writing error occurs during the iteration, it closes the file pointed to by file, frees the memory 
    allocated for imageData.Prints an error message indicating a bad output with the corresponding filename.
    If the writing process is successful for the entire binary image data, the function returns SUCCESS.
    */

int TOASCII(struct FileInfo* values, char* filename, struct FileInfo* values2) 
{
    writeHeader(values);
    if (checkValues(values, filename, values2)) 
    {
        return BAD_OUTPUT;
    }

    int result = writeImageDataASCII(values, values2);
    if (result == BAD_OUTPUT) 
    {
        return BAD_OUTPUT;
    }

    return SUCCESS;
}
void writeHeaderASCII(struct FileInfo* values) 
{
    fprintf(values->file, "eb\n%d %d\n", values->height, values->width);
}

int writeImageDataASCII(struct FileInfo* values, struct FileInfo* values2) 
{
    for (values->Row = 0; values->Row < values->height; values->Row++) 
    {
        for (values->Col = 0; values->Col < values->width; values->Col++) 
        {
            if (values->Row != values->height - 1 || values->Col != values->width - 1) 
            {
                fprintf(values2->file, "%2u%c", values->imageData2B[values->Row][values->Col], (values->Col == values->width - 1) ? '\n' : ' ');
            } 
            else 
            {
                fprintf(values2->file, "%2u", values->imageData2B[values->Row][values->Col]);
            }
        }
    }
    return SUCCESS;
}

/**
    Writes the image data in binary format to a file and checks for any errors in the output.
    @param values The pointer to the FileInfo struct containing file information.
    @param filename The name of the file being read.
    @param values2 The pointer to the FileInfo struct containing file information.
    @return Returns SUCCESS if the binary image data is successfully written, otherwise BAD_OUTPUT.
    @remarks This function writes the image data in binary format. It starts by writing the height and width information 
    to the file using the fprintf function. The return value of fprintf is stored in check to check for any writing errors. 
    If an error occurs during writing, the function returns BAD_OUTPUT.
    If a writing error occurs during the iteration, it closes the file pointed to by file, frees the memory 
    allocated for imageData.Prints an error message indicating a bad output with the corresponding filename.
    If the writing process is successful for the entire binary image data, the function returns SUCCESS.
    */

int TOBINARY(struct FileInfo* values, char* filename, struct FileInfo* values2) 
{
    writeBinaryHeader(values);
    if (checkValues(values, filename, values2)) 
    {
        return BAD_OUTPUT;
    }

    int result = writeBinaryData(values, values2);
    if (result == BAD_OUTPUT) 
    {
        return BAD_OUTPUT;
    }

    return SUCCESS;
}
void writeBinaryHeader(struct FileInfo* values) 
{
    fprintf(values->file, "eu\n%d %d\n", values->height, values->width);
}

int writeBinaryData(struct FileInfo* values, struct FileInfo* values2) 
{
    for (values->Row = 0; values->Row < values->height; values->Row++) 
    {
        for (values->Col = 0; values->Col < values->width; values->Col++) 
        {
            values->check = fwrite(&values->imageData[values->Row][values->Col], sizeof(unsigned char), 1, values2->file);
        }
    }
    return SUCCESS;
}

/**
    Writes the image data in compressed binary format to a file and checks for any errors in the output.
    @param values The pointer to the FileInfo struct containing file information.
    @param filename The name of the file being read.
    @param values2 The pointer to the FileInfo struct containing file information.
    @return Returns SUCCESS if the compressed binary image data is successfully written, otherwise BAD_OUTPUT.
    @remarks This function writes the image data in compressed binary format. It starts by writing the height and width information 
    to the file using the fprintf function. The return value of fprintf is stored in check to check for any writing errors. 
    If an error occurs during writing, the function returns BAD_OUTPUT.
    If a writing error occurs during the iteration, it closes the file pointed to by file, frees the memory 
    allocated for imageData.Prints an error message indicating a bad output with the corresponding filename.
    If the writing process is successful for the entire binary image data, the function returns SUCCESS.
    */

int writeBinaryebc(struct FileInfo* values, char* filename, struct FileInfo* values2) {
    values->check = fprintf(values2->file, "ec \n%d %d\n", values->height, values->width);
    if (checkValues(values, filename, values2)) {
        return BAD_OUTPUT;
    }

    int increment = 0;
    int counter = 8;
    unsigned int twiddled = 0;

    for (values->Row = 0; values->Row < values->height; values->Row++) {
        for (values->Col = 0; values->Col < values->width; values->Col++) {
            values->imageData2B[values->Row][values->Col] = values->imageData2B[values->Row][values->Col] << 3;
            writeTwiddledBits(values, values->imageData2B[values->Row][values->Col], &increment, &counter, &twiddled);
        }
    }

    for (int i = 0; i < values->numBytes; i++) {
        // Writing the file in binary
        values->check = fwrite(&values->x[i], sizeof(unsigned char), 1, values2->file);
        if (checkValues(values, filename, values2)) {
            return BAD_OUTPUT;
        }
    }

    return SUCCESS;
}
void writeTwiddledBit(struct FileInfo* values, unsigned int bitValue, int* increment, int* counter, unsigned int* twiddled) 
{
    *twiddled |= (bitValue ? (1 << (*counter - 1)) : 0);
    (*counter) -= 1;
    values->x[*increment] = *twiddled;
    *increment += (*counter == 0);
    *counter = (*counter == 0) ? 8 : *counter;
    *twiddled = (*counter == 8) ? 0 : *twiddled;
}

void writeTwiddledBits(struct FileInfo* values, unsigned int imageData, int* increment, int* counter, unsigned int* twiddled) 
{
    for (int i = 5; i > 0; i--) 
    {
        unsigned int bitReading = ((imageData >> (i + 2)) & 1);
        writeTwiddledBit(values, bitReading, increment, counter, twiddled);
    }
}