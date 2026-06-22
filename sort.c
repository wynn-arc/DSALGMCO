#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stack.h"
#include "sort.h"

double cross_product(Point O, Point A, Point B)
{
    return (A.x - O.x) * (B.y - O.y)
         - (A.y - O.y) * (B.x - O.x);
}
double dist_sq(Point a, Point b)
{
    double dx;
    double dy; 

    dx = a.x - b.x;
    dy = a.y - b.y;

    return dx * dx + dy * dy;
}

static int cmp_by_angle(Point anchor, Point pa, Point pb)
{
    double cp;   
    double da;   
    double db;  

    cp = cross_product(anchor, pa, pb);

    if (cp > 0.0)
        return -1;  

    if (cp < 0.0)
        return 1;    

    da = dist_sq(anchor, pa);
    db = dist_sq(anchor, pb);

    if (da < db)  return -1;
    if (da > db)  return  1;
    return 0;
}

static void swap_points(Point *a, Point *b)
{
    Point temp;  

    temp = *a;
    *a   = *b;
    *b   = temp;
}

void slow_sort(Point *pts, int n, Point anchor)
{
    int i; 
    int j;  

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (cmp_by_angle(anchor, pts[j], pts[j + 1]) > 0) {
                swap_points(&pts[j], &pts[j + 1]);
            }
        }
    }
}
static int divide(Point *pts, int lb, int ub, Point anchor)
{
    Point pivot;  
    int   i;     
    int   j;      

    pivot = pts[ub];
    i = lb - 1;

    for (j = lb; j < ub; j++) {
        if (cmp_by_angle(anchor, pts[j], pivot) <= 0) {
            i++;
            swap_points(&pts[i], &pts[j]);
        }
    }

    /* place pivot in its correct sorted position (moved outside the loop) */
    swap_points(&pts[i + 1], &pts[ub]);

    return i + 1;
}

static void quick_sort_helper(Point *pts, int lb, int ub, Point anchor)
{
    int pi;  

    if (lb < ub) {
        pi = divide(pts, lb, ub, anchor);
        quick_sort_helper(pts, lb, pi - 1, anchor);
        quick_sort_helper(pts, pi + 1, ub, anchor);
    }
}

void fast_sort(Point *pts, int n, Point anchor)
{
    if (n <= 1)
        return;

    quick_sort_helper(pts, 0, n - 1, anchor);
}
