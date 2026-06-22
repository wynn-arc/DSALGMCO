#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static Point anchor_g; 

static double cross_product(Point O, Point A, Point B)
{
    return (double)(A.x - O.x) * (B.y - O.y)
         - (double)(A.y - O.y) * (B.x - O.x);
}

static double dist_sq(Point a, Point b)
{
    return (double)(a.x - b.x) * (a.x - b.x)
         + (double)(a.y - b.y) * (a.y - b.y);
}


void bubbleSwap(Point *arr, int i, int j)
{
    Point tempArr = arr[i];
    arr[i]        = arr[j];
    arr[j]        = tempArr;
}

void bubbleSort(Point arr[], int n)
{
    int    i, j;
    double cp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            cp = cross_product(anchor_g, arr[j], arr[j + 1]);
            if (cp < 0 ||
               (cp == 0 && dist_sq(anchor_g, arr[j]) >
                           dist_sq(anchor_g, arr[j + 1])))
                bubbleSwap(arr, j, j + 1);
        }
    }
}


static void slow_sort(Point *pts, int n, Point anchor)
{
    anchor_g = anchor;
    bubbleSort(pts, n);
}

static int find_anchor_idx(Point *pts, int n)
{
    int i, idx;

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
    Point   anchor;      
    int     m;          
    int     i;

    start_time = clock();   

    anchor_idx      = find_anchor_idx(pts, n);
    tmp             = pts[0];
    pts[0]          = pts[anchor_idx];
    pts[anchor_idx] = tmp;
    anchor          = pts[0];

    slow_sort(pts + 1, n - 1, anchor);   */
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

        end_time = clock();
        printf("[SLOW] Elapsed time: %lf ms\n",
               (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000.0);
        return;
    }

    PUSH(hull, pts[0]);
    PUSH(hull, pts[1]);
    PUSH(hull, pts[2]);

    for (i = 3; i <= m; i++) {
        while ((*hull).top >= 1 &&
               cross_product(NEXT_TO_TOP(hull), TOP(hull), pts[i]) <= 0.0)
            POP(hull);

        PUSH(hull, pts[i]);
    }

    end_time = clock();
    printf("[SLOW] Elapsed time: %lf ms\n",
           (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000.0);
}
