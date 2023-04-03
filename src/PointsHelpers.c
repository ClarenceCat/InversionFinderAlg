/**
 * @file PointsHelpers.c
 * @author Daniel Grew
 * @brief Functions for dealing with Point struct
 * @version 0.1
 * @date 2022-02-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "assignment2.h"

int Compare(const void *p1, const void *p2)
{
    Point *point1 = (Point *)p1;
    Point *point2 = (Point *)p2;

    if(point1->x == point2->y && point1->y == point2->y)
    {
        return MATCH;
    }
    else{
        return NOT_MATCH;
    }
}

Point *NewPoint(float x, float y)
{
    Point *new_point = malloc(sizeof(Point));

    if(new_point == NULL)
    {
        return NULL;
    }
    new_point->x = x;
    new_point->y = y;

    return new_point;
}

void deletePoint(void *data)
{
    if(data == NULL)
    {
        return;
    }
    // free the data
    free(data);
}

int ComparePoints(Point *p1, Point *p2)
{
    if(p1->x == p2->x && p1->y == p2->y)
    {
        return MATCH;
    }
    else if(p1->x > p2->x)
    {
        return LESS;
    }
    else if (p1->x < p2->x)
    {
        return GREATER;
    }
    else 
    {
        return NOT_MATCH;
    }
}

