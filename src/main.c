/**
 * @file main.c
 * @author Daniel Grew - 0978547
 * @brief contains main function which runs algorithms
 * @version 0.1
 * @date 2022-02-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "assignment2.h"

int main(int argc, char *argv[])
{
    //Q1 
    printf("\n");

    // Q1. pt 1
    // extract lines of ints from file
    int size = 0;
    int *data1 = extractFromFile("./bin/data_A2_Q1.txt", &size);

    if(data1 == NULL)
    {
        return ERROR;
    }

    // calculate inversions using brute force algorithm
    long int q1p1_pre = CurTime();
    int numInversions = bruteForceInversions(data1, size);
    long int q1p1_post = CurTime();
    long int q1p1_dif = q1p1_post - q1p1_pre;

    printf("Brute force Number of inversions: %d \n", numInversions);
    printf("Execution Time: %ldms \n\n", q1p1_dif);

    // Q1. pt 2

    // calculate inversions using divide and conquer algorithm
    long int q1p2_pre = CurTime();
    int DCin = DCInversions(data1, size);
    long int q1p2_post = CurTime();
    long int q1p2_dif = q1p2_post - q1p2_pre;

    printf("Divide and Conquer Inversions: %d \n", DCin);
    printf("Execution Time: %ldms \n", q1p2_dif);

    if(data1 != NULL)
    {
        free(data1);
    }

    printf("\n");

    // =====================================================================
    // =====================================================================

    printf("Question 2 \n\n");
    // Q2.
    printf("Please enter the details of the first point\n");
    Point p1 = GetPointFromUser();

    printf("Please enter details of the second point\n");
    Point p2 = GetPointFromUser();

    printf("Brute Force: \n\n");

    // extract points from file
    int len = 0;
    Point *points = ExtractPointsFromFile("./bin/data_A2_Q2.txt", &len);

    int bf_len = 0;
    // Q2. pt 1
    long int q2p1_pre = CurTime();
    Point *bf_convex = BFGetConvexHull(points, len, &bf_len);
    long int q2p1_post = CurTime();

    long int q2p1_dif = q2p1_post - q2p1_pre;

    printf("Brute Force Convex Hull - Time for computing hull: %ldms \n", q2p1_dif);

    float bf_dist = 0;
    int bf_path_len = 0;
    Point *bf_shortest = findShortestPath(bf_convex, bf_len, &bf_path_len, &bf_dist, p1, p2);

    PrintDetails(bf_path_len, bf_dist, bf_shortest);

    // Q2. pt 2
    printf("QuickHull: \n\n");

    int c_hull = 0;
    long int q2p2_pre = CurTime();

    // call function to get convex hull
    Point *convex_hull = DCGetConvexHull(points, len, &c_hull);

    long int q2p2_post = CurTime();
    long int q2p2_dif = q2p2_post - q2p2_pre;

    printf("Quick Hull - Time for computing hull: %ldms \n", q2p2_dif);

    float qh_dist = 0;
    int qh_len = 0;
    Point *qh_shortest = findShortestPath(convex_hull, c_hull, &qh_len, &qh_dist, p1, p2);

    PrintDetails(qh_len, qh_dist, qh_shortest);


    free(points);
    if(convex_hull != NULL)
    {
        free(convex_hull);
    }
    if(bf_convex != NULL)
    {
        free(bf_convex);
    }

    if(bf_shortest != NULL)
    {
        free(bf_shortest);
    }
    if(qh_shortest != NULL)
    {
        free(qh_shortest);
    }

    return 0;
}

/**
 * @brief Asks the user for x and y values of a point
 * 
 * @return Point - point structure reflecting values that were entered
 */
Point GetPointFromUser()
{

    float x = 0;    
    float y = 0;

    int valid = 0;
    while(valid == 0)
    {
        char x_input[MAX_INPUT];
        char y_input[MAX_INPUT];

        printf("Enter x value: ");
        fgets(x_input, MAX_INPUT, stdin);

        printf("Enter y value: ");
        fgets(y_input, MAX_INPUT, stdin);

        int check_x = sscanf(x_input, "%f", &x);
        int check_y = sscanf(y_input, "%f", &y);

        printf("\n");

        if(check_x != 0 || check_y != 0)
        {
            valid = 1;
            break;
        }
        printf("please enter valid x and y coordinates - should be doubles \n");
    }

    Point new_p;
    new_p.x = x;
    new_p.y = y;

    return new_p;
}

void PrintDetails(int num_points, float dist, Point *path)
{
    printf("brute force shortest path\n");
    printf("number of points on the shortest path: %d\n", num_points);
    printf("The distance: %f\n", dist);
    printf("The points on path: \n");
    for(int m = 0; m < num_points; m++)
    {
        printf("(%f , %f)\n", path[m].x, path[m].y);
    }
    printf("=========================== \n");
}

/**
 * @brief Retrieves the current time in milliseconds
 * 
 * NOTE: This is from the example given by Professor Fangju Wang
 * 
 * @return long int 
 */
long int CurTime()
{
    struct timespec ts;
    long int cur = 0;

    // get the current utc time
    timespec_get(&ts, TIME_UTC);
    cur = ((long int)ts.tv_sec) * 1000 + ((long int)ts.tv_nsec)/1000000;

    return cur;
}
