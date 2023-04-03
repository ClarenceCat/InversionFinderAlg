/**
 * @file P12.c
 * @author Daniel Grew - 0978547
 * @brief Implementation of an algorithm which counts inversions - uses a recursive divide and conquer approach
 * @version 0.1
 * @date 2022-01-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "assignment2.h"

int DCInversions(int numbers[], int numElements)
{
    if(numElements == 1)
    {
        return 0;
    }

    // claculate the middle element
    int middle = floor(numElements/2);

    // allocate int arrays to copy data into
    int *lower = malloc(sizeof(int) * middle);
    int *upper = malloc(sizeof(int) * (numElements - middle));

    // copy data into the new arrays
    copyArray(lower, numbers, numElements, middle, 0);
    copyArray(upper, numbers, numElements, (numElements - middle), middle);

    int lower_inversions = DCInversions(lower, middle);
    int upper_inversions = DCInversions(upper, (numElements - middle));
    
    int ret = InversionsMerge(lower, middle, upper, (numElements - middle), numbers, numElements) + upper_inversions + lower_inversions;

    free(upper);
    free(lower);

    return ret;
}

int InversionsMerge(int *lower, int lower_num, int *upper, int upper_num, int *numbers, int num_numbers)
{
    int inversions = 0;
    int i = 0;
    int j = 0;
    int k = 0;

    while(i < lower_num && j < upper_num)
    {
        // if the lower array element at index i is less than element in upper at index j
        if(lower[i] <= upper[j])
        {
            numbers[k] = lower[i];
            if(i < lower_num - 1)
            {
                inversions += j;
            }
            i++;
        }
        else
        {
            // if the lower index is of a greater value than the value in the upper array
            numbers[k] = upper[j];
            if(lower[i] != upper[j])
            {
                inversions++;
            }
            j++;
        }
        k++;
    }
    // if the end of the sorted lower array has been reached
    if(i == lower_num)
    {
        // add rest of sorted upper index to the end of the sorted array
        for(int index = j; index < upper_num; index++)
        {
            numbers[k] = upper[index];
            k++;
        }
    }
    else
    {
        numbers[k] = lower[i];
        i++;
        k++;
        for(int index = i; index < lower_num; index++)
        {
            numbers[k] = lower[index];
            inversions += j;
            k++;
        }
    }

    return inversions;
}


// void copyArray(int *dest, int *target, int size)
// {
//     for(int i = 0; i < size; i++)
//     {
//         dest[i] = target[i];
//     }
// }

void copyArray(int *dest, int *src, int src_size, int elements_to_copy, int target_start_index)
{
    int dest_index = 0;
    int src_index = target_start_index;
    while(dest_index < elements_to_copy && src_index < src_size)
    {
        dest[dest_index] = src[src_index];
        dest_index++;
        src_index++;
    }
}

