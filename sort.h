#ifndef SORT_H
#define SORT_H

#include "stack.h"  
double cross_product(Point O, Point A, Point B);
double dist_sq(Point a, Point b);
void slow_sort(Point *pts, int n, Point anchor);
void fast_sort(Point *pts, int n, Point anchor);

#endif  
