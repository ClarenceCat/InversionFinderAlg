/**
 * @file filehandler.c
 * @author Daniel Grew
 * @brief This file contains functions that read the list of integers from a file
 * @version 0.1
 * @date 2022-02-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "assignment2.h"

/**
 * @brief Extracts all integers from file into a list of 
 * 
 * @param filename 
 * @param dest
 * @return int - the number of elements in the file or -1 if error 
 */
int *extractFromFile(char *filename, int* lines)
{
    // check for null filename
    if(filename == NULL)
    {
        return NULL;
    }

    int num_lines = linesInFile(filename);

    // check if the getFileSize() returned an error
    if(num_lines == ERROR || num_lines == FILE_ERROR)
    {
        return NULL;
    }

    // extract the contents from the file
    char **contents = readFromFile(filename, num_lines);

    // check for error
    if (contents == NULL)
    {
        return NULL;
    }

    int *nums = stringsToInts(contents, num_lines);
    
    if(nums == NULL)
    {
        free(contents);
        return NULL;
    }

    // free the contents
    freeStringList(contents, num_lines);

    // set dest to the array of nums that has been generated
    *lines = num_lines * 5;

    return nums;
}

/**
 * @brief Read contents of file into char list
 * 
 * @param filename 
 * @return char* 
 */
char **readFromFile(char *filename, int file_size)
{
    if(filename == NULL)
    {
        return NULL;
    }

    FILE *file = fopen(filename, READ);

    if(file == NULL)
    {
        return NULL;
    }

    // allocate memory to store the contents of the file
    char **lines = malloc(sizeof(char *) * file_size);

    // read through the file loading lines from file into the char double array
    int index = 0;
    char tmp[MAX_LINE_LEN] = "";
    while(fgets(tmp, MAX_LINE_LEN, file) && index < file_size)
    {
        lines[index] = malloc(sizeof(char) * (strlen(tmp) + 1));
        strcpy(lines[index], tmp);
        index++;
    }

    // close file
    fclose(file);

    // return the char array
    return lines;
}

/**
 * @brief Get the number of integers stored in a file
 * 
 * @param filename 
 * @return int - number of lines in the file or -1 if there is an error reading from file
 */
int linesInFile(char *filename)
{
    // make sure filename isn't null
    if(filename == NULL)
    {
        return ERROR;
    }
    // open file
    FILE *file = fopen(filename, READ);

    // check if file exists
    if(file == NULL)
    {
        return FILE_ERROR;
    }

    int lines = 0;
    char tmp[MAX_LINE_LEN] = "";

    while(fgets(tmp, MAX_LINE_LEN, file))
    {
        if(strcmp(tmp, EMPTY_LINE) != 0)
        {
            lines++;
        }
    }

    //close file
    if(fclose(file) != 0)
    {
        return FILE_ERROR;
    }

    return lines;
}

int *stringsToInts(char **strings, int lines)
{
    // check if strings is null
    if(strings == NULL)
    {
        return NULL;
    }

    // allocate an array of ints
    int *nums = malloc(sizeof(int) * (lines) * INTS_PER_LINE);

    int num_index = 0;

    // loop through the list of strings converting them to ints
    for(int i = 0; i < lines; i++)
    {
        // check if the string is null
        if(strcmp(strings[i], EMPTY_STR) != 0)
        {
            int n1 = 0;
            int n2 = 0;
            int n3 = 0;
            int n4 = 0;
            int n5 = 0;

            // scan line for all integers
            sscanf(strings[i], "%d %d %d %d %d", &n1, &n2, &n3, &n4, &n5);
            
            // insert integers into nums array
            nums[num_index] = n1;
            num_index++;
            nums[num_index] = n2;
            num_index++;
            nums[num_index] = n3;
            num_index++;
            nums[num_index] = n4;
            num_index++;
            nums[num_index] = n5;
            num_index++;
        }
    }

    return nums;
}

void freeStringList(char **strings, int lines)
{
    for(int i = 0; i < lines; i++)
    {
        free(strings[i]);
    }
    free(strings);
}


Point *ExtractPointsFromFile(char *filename, int *lines)
{
    if(filename == NULL || strcmp(filename, EMPTY_STR) == 0)
    {
        return NULL;
    }

    // get the number of lines in the file
    int num_lines = linesInFile(filename);

    char **contents = readFromFile(filename, num_lines);

    if(contents == NULL)
    {
        return NULL;
    }

    Point *points = extractPoints(contents, num_lines);

    if(points == NULL)
    {
        freeStringList(contents, num_lines);
        return NULL;
    }

    freeStringList(contents, num_lines);

    *lines = num_lines;
    return points;
}

Point *extractPoints(char **lines, int num_lines)
{
    if(lines == NULL || num_lines < 0)
    {
        return NULL;
    }

    Point *ret = malloc(sizeof(Point) * num_lines);

    if(ret == NULL)
    {
        return NULL;
    }

    // loop through lines of data to extract the point information
    for(int i = 0; i < num_lines; i++)
    {
        float x = 0;
        float y = 0;

        sscanf(lines[i], "%f   %f", &x, &y);

        ret[i].x = x;
        ret[i].y = y;
    }

    return ret;
}


// List *ExtractPointsFromFileList(char *filename)
// {
//     if(filename == NULL || strcmp(filename, EMPTY_STR) == 0)
//     {
//         return NULL;
//     }

//     // get the number of lines in the file
//     int num_lines = linesInFile(filename);

//     char **contents = readFromFile(filename, num_lines);

//     if(contents == NULL)
//     {
//         return NULL;
//     }

//     List *points = extractPointsList(contents, num_lines);

//     if(points == NULL)
//     {
//         freeStringList(contents, num_lines);
//         return NULL;
//     }

//     freeStringList(contents, num_lines);

//     return points;
// }


// List *extractPointsList(char **lines, int num_lines)
// {
//     if(lines == NULL || num_lines < 0)
//     {
//         return NULL;
//     }

//     List *ret = initializeList(deletePoint, Compare);

//     if(ret == NULL)
//     {
//         return NULL;
//     }

//     // loop through lines of data to extract the point information
//     for(int i = 0; i < num_lines; i++)
//     {
//         float x = 0;
//         float y = 0;

//         sscanf(lines[i], "%f   %f", &x, &y);

//         Point *p = NewPoint(x, y);

//         ListAppend(ret, p);
//     }

//     return ret;
// }

