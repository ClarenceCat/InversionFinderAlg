/**
 * @file P21.c
 * @author Daniel Grew - 0978547
 * @brief This file contains the implementation of a brute force algorithm which calculates the shortest path around a convex hull
 * @version 0.1
 * @date 2022-02-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "assignment2.h"

Point *findShortestPath(Point *convex_hull, int c_hull_len, int *ret_len, float *ret_distance, Point p1, Point p2)
{
    // if it is null return NULL
    if(convex_hull == NULL)
    {
        return NULL;
    }

    // get the index of p1 and p2 in the convex hull array
    int p1_index = FindPointIndex(convex_hull, c_hull_len, p1);
    int p2_index = FindPointIndex(convex_hull, c_hull_len, p2);

    // find the shortest path between the two points
    Point *path_1 = malloc(sizeof(Point) * c_hull_len);
    Point *path_2 = malloc(sizeof(Point) * c_hull_len);

    int path_1_len = 0;
    int path_2_len = 0;

    float path_1_dist = FindDistance(p1_index, p2_index, convex_hull, c_hull_len, path_1, &path_1_len);
    float path_2_dist = FindDistance(p2_index, p1_index, convex_hull, c_hull_len, path_2, &path_2_len);

    Point *shortest = NULL;
    float ret_dist = -1;
    int num_points = 0;

    // check which path is shortest
    if(path_2_dist < path_1_dist)
    {
        shortest = path_2;
        ret_dist = path_2_dist;
        num_points = path_2_len;
        free(path_1);
    }
    else
    {
        shortest = path_1;
        ret_dist = path_1_dist;
        num_points = path_1_len;
        free(path_2);
    }

    *ret_len = num_points;
    *ret_distance = ret_dist;
    return shortest;
}

/**
 * @brief Fincs the convex hull of a set of points
 * 
 * @param points 
 * @param len 
 * @param ret_len 
 * @return Point* 
 */
Point *BFGetConvexHull(Point *points, int len, int *ret_len)
{
    if(points == NULL)
    {
        return NULL;
    }

    Point *hull = malloc(sizeof(Point) * len);

    int i = 0;
    int j = 0;
    int k = 0;
    int hull_count = 0;

    // iterate over the entire array of points
    for(i = 0; i < len; i++)
    {
        Point p1 = points[i];
        for(j = 0; j < len; j++)
        {
            Point p2 = points[j];
            // if points at index i and j are the same point
            if (ComparePoints(&p1, &p2) == MATCH)
            {
                continue;
            }

            int side = 0;

            // calculate coefficients for equation of line between point at i point at j
            // eqn: ax + by = c 
            float c = (p1.x * p2.y) - (p1.y * p2.x);
            float a = p2.y - p1.y;
            float b = p1.x - p2.x;
            // loop through all points (except the two being considered) and see if they are all on the same side
            //      of the line
            for(k = 0; k < len; k++)
            {
                Point p3 = points[k];
                if(ComparePoints(&p1, &p3) == MATCH || ComparePoints(&p2, &p3) == MATCH)
                {
                    continue;
                }
                // calculate c value
                float point_c = (a * p3.x) + (b * p3.y);
                // check which half the point is on
                if(point_c > c)
                {
                    // check if the value has not been changed yet
                    if(side == 0)
                    {
                        side = GT;
                        continue;
                    }
                    
                    // check if the side is greater than c
                    if(side != GT)
                    {
                        break;
                    }
                }
                else if(point_c < c)
                {
                    if(side == 0)
                    {
                        side = LT;
                        continue;
                    }

                    // check if side is less than c
                    if(side != LT)
                    {
                        break;
                    }
                }
            }

            if(k == len)
            {
                hull[hull_count] = points[i];
                hull_count++;
                break;
            }
        }
    }

    // sort the convex hull
    SortConvexHull(hull, hull_count);

    *ret_len = hull_count;
    return hull;
}

void SortConvexHull(Point * points, int size)
{
    if(points == NULL)
    {
        return;
    }
    // find leftmost and rightmost indices
    int leftmost_index = 0;
    int rightmost_index = 0;

    for(int i = 0; i < size; i++)
    {
        if(points[i].x < points[leftmost_index].x)
        {
            leftmost_index = i;
        }
        else if(points[i].x > points[rightmost_index].x)
        {
            rightmost_index = i;
        }
    }

    // separate hulls
    Point upper[size];
    Point lower[size];

    int upper_size = SplitHull(points[leftmost_index], points[rightmost_index], points, upper, size, UPPER_HULL);
    int lower_size = SplitHull(points[leftmost_index], points[rightmost_index], points, lower, size, LOWER_HULL);
    
    // sort upper and lower hull in terms of x
    SortHull(upper, upper_size);
    SortHull(lower, lower_size);

    // merge the sorted hulls and overwrite points with the sorted array
    int merge_index = 0;
    Point leftmost = points[leftmost_index];
    Point rightmost = points[rightmost_index];

    points[merge_index] = leftmost;
    merge_index++;

    // add sorted upper hull first
    for(int i = 0; i < upper_size; i++)
    {
        points[merge_index] = upper[i];
        merge_index++;
    }

    // add the rightmost 
    points[merge_index] = rightmost;

    // add sorted lower hull list in reverse order
    for(int j = lower_size - 1; j >= 0; j--)
    {
        points[merge_index] = lower[j];
        merge_index++;
    }
}

/**
 * @brief MergeSort algorithm which sorts the points in a list by their x values
 * 
 * @param points 
 * @param size 
 */
 void SortHull(Point *points, int size)
{
    // check if the array size is 1 (base case of mergesort)
    if(size <= 1)
    {
        return;
    }
    // find middle array index
    int middle = floor(size/2);

    // allocate upper and lower half arrays
    Point *lower = malloc(sizeof(Point) * middle);
    Point *upper = malloc(sizeof(Point) * (size - middle));

    // copy data into new arrays
    CopyPointArr(lower, points, size, middle, 0);
    CopyPointArr(upper, points, size, (size - middle), middle);

    SortHull(lower, middle);
    SortHull(upper, (size - middle));

    MergeSortHull(lower, middle, upper, (size - middle), points, size);

    free(upper);
    free(lower);
}

/**
 * @brief Merge algorithm for mergesort used to sort set of points in ascending order
 * 
 * @param lower 
 * @param lower_size 
 * @param upper 
 * @param upper_size 
 * @param arr 
 * @param arr_size 
 */
void MergeSortHull(Point *lower, int lower_size, Point *upper, int upper_size, Point *arr, int arr_size)
{
    if(!lower || !upper || !arr)
    {
        return;
    }

    int i = 0;
    int j = 0;
    int k = 0;

    while(i < lower_size && j < upper_size)
    {
        // check if the array element's x value at i is less than the one at index j
        if(lower[i].x <= upper[j].x)
        {
            arr[k].x = lower[i].x;
            arr[k].y = lower[i].y;
            i++;
        }
        // if i's x value is greater than j's
        else 
        {
            arr[k].x = upper[j].x;
            arr[k].y = upper[j].y;
            j++;
        }
        k++;
    }

    // if the lower index has all been copied
    if(i == lower_size)
    {
        for(int index_j = j; index_j < upper_size; index_j++)
        {
            arr[k].x = upper[index_j].x;
            arr[k].y = upper[index_j].y;
            k++;
        }
    }
    else
    {
        for(int index_i = i; index_i < lower_size; index_i++)
        {
            arr[k].x = lower[index_i].x;
            arr[k].y = lower[index_i].y;
            k++;
        }
    }
}

void CopyPointArr(Point *dest, Point *src, int src_size, int to_copy, int start)
{
    int dest_index = 0;
    for(int src_index = start; dest_index < to_copy && src_index < src_size; src_index++)
    {
        dest[dest_index].x = src[src_index].x;
        dest[dest_index].y = src[src_index].y;
        dest_index++;
    }
}
