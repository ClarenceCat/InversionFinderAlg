/**
 * @file assignment2.h
 * @author Daniel Grew - 0978547
 * @brief Contains function declarations for all functions in assignment 2 as well as includes for all libraries used
 * @version 0.1
 * @date 2022-02-01
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <inttypes.h>
#include <time.h>

#define ERROR -1
#define FILE_ERROR -2
#define READ "r"
#define NEW_LINE '\n'
#define MAX_LINE_LEN 100
#define EMPTY_STR ""
#define EMPTY_LINE "\n"
#define INTS_PER_LINE 5
#define POINTS_PER_LINE 2
#define MATCH 0
#define NOT_MATCH -1
#define GREATER 1
#define LESS -2

#define GT 1
#define LT -1

#define UPPER_HULL 1
#define LOWER_HULL -1

#define MAX_INPUT 10

typedef struct {
    float x;
    float y;
} Point;


// used to extract information from files
int bruteForceInversions(int numbers[], int numElements);
int DCInversions(int numbers[], int numElements);
int *extractFromFile(char *filename, int* dest);
char **readFromFile(char *filename, int file_size);
int linesInFile(char *filename);
int *stringsToInts(char **strings, int lines);
void freeStringList(char **strings, int lines);

// Used in Q1.Pt2
int DCInversions(int numbers[], int numElements);
int InversionsMerge(int *lower, int lower_num, int *upper, int upper_num, int *numbers, int num_numbers);
void copyArray(int *dest, int *src, int src_size, int elements_to_copy, int target_start_index);

// Used to parse the points from file in Q2
Point *ExtractPointsFromFile(char *filename, int *lines);
Point *extractPoints(char **lines, int num_lines);

// List *ExtractPointsFromFileList(char *filename);
// List *extractPointsList(char **lines, int num_lines);

// Used in Q2.Pt1
Point *BFGetConvexHull(Point *points, int len, int *ret_len);
void SortConvexHull(Point * points, int size);
void SortHull(Point *points, int size);
void MergeSortHull(Point *lower, int lower_size, Point *upper, int upper_size, Point *arr, int arr_size);
void CopyPointArr(Point *dest, Point *src, int src_size, int to_copy, int start);

// used in Q2.Pt2
Point *DCGetConvexHull(Point *points, int len, int *size_hull);
int QuickHull(Point p1, Point p2, Point *points, int len, Point *convex_hull, int hull_type);
int SplitHull(Point p1, Point p2, Point *points, Point *hull, int len, int hull_type);

// used in both pt 1 and pt 2
Point *findShortestPath(Point *convex_hull, int c_hull_len, int *ret_len, float *ret_distance, Point p1, Point p2);
float FindDistance(int p1_index, int p2_index, Point *points, int size, Point *path, int *path_len);
int FindPointIndex(Point *points, int size, Point p);
Point GetPointFromUser();
void PrintDetails(int num_points, float dist, Point *path);
long int CurTime();

// Helper functions
int ComparePoints(Point *p1, Point *p2);
int Compare(const void *p1, const void *p2);
Point *NewPoint(float x, float y);
void deletePoint(void *data);
