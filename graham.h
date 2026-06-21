#ifndef GRAHAM_H
#define GRAHAM_H

#include "stack.h"

#define MAX_POINTS 32768  

void graham_scan_slow(Point *pts, int n, Stack *hull);
void graham_scan_fast(Point *pts, int n, Stack *hull); /*will edit depending on code!*/

#endif 
