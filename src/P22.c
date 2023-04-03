/**
 * @file P22.c
 * @author Daniel Grew - 0978547
 * @brief This file contains the functions which implement the quickhull algorithm
 * @version 0.1
 * @date 2022-02-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "assignment2.h"


/**
 * @brief This function retrieves the set of points that make up the convex hull in an ordered manner
 * 
 * @param points 
 * @param len 
 * @param size_hull 
 * @return Point* - array of points ordered from the leftmost point along the upper hull to the rightmost point, and then along the lower hull
 */
Point *DCGetConvexHull(Point *points, int len, int *size_hull)
{
    // make sure points isnt null
    if(points == NULL)
    {
        return NULL;
    }

    // find the leftmost and rightmost points
    Point leftmost = points[0];
    Point rightmost = points[0];

    for(int i = 0; i < len; i++)
    {
        if(points[i].x < leftmost.x)
        {
            leftmost = points[i];
            continue;
        }
        if(points[i].x > rightmost.x)
        {
            rightmost = points[i];
            continue;
        }
    }

    // create list for hull
    Point upper_hull[len];
    Point lower_hull[len];

    // get the upper points and lower points
    Point upper_points[len]; 
    Point lower_points[len];

    int upper_count = SplitHull(leftmost, rightmost, points, upper_points, len, UPPER_HULL);
    int lower_count = SplitHull(leftmost, rightmost, points, lower_points, len, LOWER_HULL);

    // find upper hull points
    int upper_hull_size = QuickHull(leftmost, rightmost, upper_points, upper_count, upper_hull, UPPER_HULL);

    // add all points from upper hull to the convex hull
    int lower_hull_size = QuickHull(leftmost, rightmost, lower_points, lower_count, lower_hull, LOWER_HULL);

    int hull_size = upper_hull_size + lower_hull_size + 2;

    Point *ret = malloc(sizeof(Point) * hull_size);

    int ret_index = 0;
    // add the leftmost to the first index
    ret[ret_index] = leftmost;
    ret_index++;

    // add all points in upper hull
    for(int j = 0; j < upper_hull_size; j++)
    {
        ret[ret_index] = upper_hull[j];
        ret_index++;
    }

    // add rightmost point
    ret[ret_index] = rightmost;
    ret_index++;

    // add all points from lower hull
    for(int l = lower_hull_size - 1; l >= 0; l--)
    {
        ret[ret_index] = lower_hull[l];
        ret_index++;
    }

    // set the convex hull to the newly allocated array
    *size_hull = ret_index;
    return ret;
}

/**
 * @brief finds the points on one side of a line connecting p1 and p2
 * 
 * @param p1 
 * @param p2 
 * @param points 
 * @param hull 
 * @param len 
 * @param hull_type 
 * @return int the number of points retrieved - loads the array of points into the hull parameter
 */
int SplitHull(Point p1, Point p2, Point *points, Point *hull, int len, int hull_type)
{
    if(points == NULL)
    {
        return 0;
    }
    int hull_count = 0;

    // calculate values used to separate hull
    // float c = (p1.x * p2.y) - (p1.y * p2.x);
    // float a = p2.y - p1.y;
    // float b = p1.x - p2.x;
    for(int i = 0; i < len; i++)
    {
        Point p = points[i];
        // if point is same as point 1 or point 2 continue
        if(p.x == p1.x || p.x == p2.x)
        {
            continue;
        }
        // calculate c value
        float check = (p1.x * p2.y) + (p.x * p1.y) + (p2.x * p.y) - (p.x * p2.y) - (p2.x * p1.y) - (p1.x * p.y);

        if(hull_type == UPPER_HULL && check > 0)
        {
            hull[hull_count] = p;
            hull_count++;
            continue;
        }
        else if(hull_type == LOWER_HULL && check < 0)
        {
            hull[hull_count] = p;
            hull_count++; 
            continue;
        }
    }

    return hull_count;
}

/**
 * @brief This is a recursive function used to find points that lie on the specified hull
 * 
 * @param p1 
 * @param p2 
 * @param points 
 * @param len 
 * @param convex_hull 
 * @param hull_type 
 * @return int - the number of points located on the hull
 */
int QuickHull(Point p1, Point p2, Point *points, int len, Point *convex_hull, int hull_type)
{
    // check if length is greater than 0
    if(len <= 0)
    {
        return 0;
    }
    //check if points is null
    if(points == NULL)
    {
        return 0;
    }

    float max_area = 0;
    Point furthest_point = points[0];

    // find the furthest point and separate the upper and lower hulls
    for(int i = 0; i < len; i++)
    {
        Point p = points[i];

        // calculate the area
        float area = (p1.x * p2.y) + (p.x * p1.y) + (p2.x * p.y) - (p.x * p2.y) - (p2.x * p1.y) - (p1.x * p.y);

        if(area < 0 && hull_type == LOWER_HULL)
        {
            if(area < max_area)
            {
                max_area = area;
                furthest_point.x = p.x;
                furthest_point.y = p.y;
            }
        }
        if(area > 0 && hull_type == UPPER_HULL)
        {
            if(area > max_area)
            {
                max_area = area;
                furthest_point.x = p.x;
                furthest_point.y = p.y;              
            }
        }
    }


    // create list for hull
    Point hull_1[len];
    Point hull_2[len];

    // get the upper points and lower points
    Point hull_1_points[len]; 
    Point hull_2_lower_points[len];

    int hull_1_count = SplitHull(p1, furthest_point, points, hull_1_points, len, hull_type);
    int hull_2_count = SplitHull(furthest_point, p2, points, hull_2_lower_points, len, hull_type);

    // find upper hull points
    int hull_1_size = QuickHull(p1, furthest_point, hull_1_points, hull_1_count, hull_1, hull_type);

    // add all points from upper hull to the convex hull
    int hull_2_size = QuickHull(furthest_point, p2, hull_2_lower_points, hull_2_count, hull_2, hull_type);


    int ret_index = 0;

    // add all points in upper hull
    for(int j = 0; j < hull_1_size; j++)
    {
        convex_hull[ret_index] = hull_1[j];
        ret_index++;
    }

    // add rightmost point
    convex_hull[ret_index] = furthest_point;
    ret_index++;

    // add all points from lower hull
    for(int l = 0; l < hull_2_size; l++)
    {
        convex_hull[ret_index] = hull_2[l];
        ret_index++;
    }

    // set the convex hull to the newly allocated array
    return ret_index;
}

/**
 * @brief Finds the path between two points on a convex hull
 * 
 * @param p1 
 * @param p2 
 * @param points - a convex hull which is sorted
 * @param size 
 * @param path 
 * @param direction 
 * @return int 
 */
float FindDistance(int p1_index, int p2_index, Point *points, int size, Point *path, int *path_len)
{
    if(!points)
    {
        return ERROR;
    }

    float total_len = 0;
    int path_index = 0;

    // loop through the points
    for(int i = p1_index; i < size; i++)
    {
        int next_point = 0;
        if(i + 1 < size)
        {
            next_point = i + 1;
        }

        Point cur_p = points[i];
        Point n_p = points[next_point];
        // calculate distance between points
        total_len += sqrt(((n_p.x - cur_p.x) * (n_p.x - cur_p.x)) + (((n_p.y - cur_p.y)) * (n_p.y - cur_p.y)));
        
        // add point to the path list
        path[path_index] = cur_p;

        // if the next point is the final index - break
        if(next_point == p2_index)
        {
            path[path_index] = n_p;
            path_index++;
            break;
        }
        // if at the end of array, loop to beginning
        if(i + 1 == size)
        {
            i = 0;
        }
        path_index++;
    }
    *path_len = path_index;
    return total_len;
}

/**
 * @brief finds the index of a specified point in an array of points
 * 
 * @param points 
 * @param size 
 * @param p 
 * @return int 
 */
int FindPointIndex(Point *points, int size, Point p)
{
    // check that points is not null
    if(points == NULL)
    {
        return ERROR;
    }

    // loop through the array to find a match
    for(int i = 0; i < size; i++)
    {
        // calculate the difference between points
        // since they are floating points, there may be some variation after 
        //      the first decimal place
        int diff_x = roundf(fabs(points[i].x - p.x));
        int diff_y = roundf(fabs(points[i].y - p.y));

        if(diff_x == 0 && diff_y == 0)
        {
            return i;
        }
    }
    return NOT_MATCH;
}
