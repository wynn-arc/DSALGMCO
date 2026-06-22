#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "stack.h"
#include "sort.h"
#include "graham.h"

static int find_anchor_idx(Point *pts, int n)
{
    int i;    
    int idx;  
    idx = 0;

    for (i = 1; i < n; i++) {
        if (pts[i].y < pts[idx].y ||
           (pts[i].y == pts[idx].y && pts[i].x < pts[idx].x))
            idx = i;
    }

    return idx;
}

void graham_scan_slow(Point *pts, int n, Stack *hull)
{
    clock_t start_time; 
    clock_t end_time;    
    int     anchor_idx; 
    Point   anchor;     
    Point   tmp;         
    int     m;           
    int     i;          
    start_time = clock();
    
    anchor_idx      = find_anchor_idx(pts, n);
    tmp             = pts[0];
    pts[0]          = pts[anchor_idx];
    pts[anchor_idx] = tmp;
    anchor          = pts[0];

    slow_sort(pts + 1, n - 1, anchor);

    m = 1;

    for (i = 1; i < n; i++) {
        while (m > 0 && cross_product(anchor, pts[m], pts[i]) == 0.0)
            m--;

        m++;
        pts[m] = pts[i];
    }

    CREATE(hull);

    if (m < 2) {
        for (i = 0; i <= m; i++)
            PUSH(hull, pts[i]);
    } else {
        PUSH(hull, pts[0]);
        PUSH(hull, pts[1]);
        PUSH(hull, pts[2]);

        for (i = 3; i <= m; i++) {
            while ((*hull).top >= 1 &&
                   cross_product(NEXT_TO_TOP(hull), TOP(hull), pts[i]) <= 0.0)
                POP(hull);

            PUSH(hull, pts[i]);
        }
    }

    end_time = clock();
    printf("[SLOW] Elapsed time: %lf ms\n",
           (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000.0);
}
