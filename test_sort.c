#include <stdio.h>
#include <stdlib.h>
#include "stack.c"  
#include "sort.c"   

#define TEST_N 9    /* number of test points (matches sample-input.txt) */


void print_points(Point *pts, int n, const char *label)
{
    int i; 
  
    printf("%s (%d points):\n", label, n);

    for (i = 0; i < n; i++)
        printf("  [%d]  (%9.6f, %9.6f)\n", i, pts[i].x, pts[i].y);

    printf("\n");
}

int verify_sorted(Point *pts, int n, Point anchor)
{
    int i;      
    int passed;  /* 1 if all pairs are in order */

    passed = 1;

    for (i = 0; i < n - 1; i++) {
        double cp = cross_product(anchor, pts[i], pts[i + 1]);

        if (cp < 0.0) {  
            printf("  FAIL at index %d: pts[%d] should come after pts[%d]\n",
                   i, i, i + 1);
            passed = 0;
        }
    }

    return passed;
}

int main()
{
    Point raw[TEST_N];   
    Point slow_pts[TEST_N]; 
    Point fast_pts[TEST_N]; 
    Point anchor;        
    int   anchor_idx;   
    int   i;           
    int   match;  
  
    raw[0].x =  5.0;  raw[0].y =  5.0;
    raw[1].x = 10.0;  raw[1].y =  2.5;
    raw[2].x =  5.0;  raw[2].y = 10.0;
    raw[3].x = 10.0;  raw[3].y =  0.0;
    raw[4].x =  7.5;  raw[4].y =  0.0;
    raw[5].x =  5.0;  raw[5].y =  0.0;
    raw[6].x =  0.0;  raw[6].y =  0.0;
    raw[7].x =  1.0;  raw[7].y =  8.0;
    raw[8].x =  0.0;  raw[8].y = 10.0;

    anchor_idx = 0;
    for (i = 1; i < TEST_N; i++) {
        if (raw[i].y < raw[anchor_idx].y ||
           (raw[i].y == raw[anchor_idx].y && raw[i].x < raw[anchor_idx].x))
            anchor_idx = i;
    }
    anchor = raw[anchor_idx];

    printf("Anchor point: (%9.6f, %9.6f)\n\n", anchor.x, anchor.y);

    for (i = 0; i < TEST_N; i++) {
        slow_pts[i] = raw[i];
        fast_pts[i] = raw[i];
    }

    printf("=============================================\n");
    printf("  SLOW SORT TEST\n");
    printf("=============================================\n");
    print_points(slow_pts, TEST_N, "Before slow_sort");
    slow_sort(slow_pts, TEST_N, anchor);
    print_points(slow_pts, TEST_N, "After  slow_sort");
    if (verify_sorted(slow_pts, TEST_N, anchor))
        printf("  slow_sort: PASS\n\n");
    else
        printf("  slow_sort: FAIL\n\n");

    printf("=============================================\n");
    printf("  FAST SORT TEST\n");
    printf("=============================================\n");
    print_points(fast_pts, TEST_N, "Before fast_sort");
    fast_sort(fast_pts, TEST_N, anchor);
    print_points(fast_pts, TEST_N, "After  fast_sort");
    if (verify_sorted(fast_pts, TEST_N, anchor))
        printf("  fast_sort: PASS\n\n");
    else
        printf("  fast_sort: FAIL\n\n");

    match = 1;
    for (i = 0; i < TEST_N; i++) {
        if (slow_pts[i].x != fast_pts[i].x || slow_pts[i].y != fast_pts[i].y)
            match = 0;
    }
    printf("Both sorts produce identical ordering: %s\n\n",
           match ? "YES (PASS)" : "NO (FAIL - check sort implementations)");

    return 0;
}
