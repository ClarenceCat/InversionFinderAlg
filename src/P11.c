/**
 * @file P11.c
 * @author Daniel Grew
 * @brief This file contains the implementation for the brute force algorithm for counting inversions
 * @version 0.1
 * @date 2022-01-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/**
 * @brief This is an function impliments a brute force algorithm for counting the numebr of 
 *      inversions present within a given array - inversion if A[j] > A[i] | j < i
 * 
 * @param numbers 
 * @param numElements 
 * @return int 
 */
int bruteForceInversions(int numbers[], int numElements)
{
    int count = 0;
    for(int i = 0; i <= numElements - 2; i++)
    {
        for(int j = i + 1; j <= numElements - 1; j++)
        {
            if(numbers[i] > numbers[j])
            {
                count++;
            }
        }
    }

    return count;
}
