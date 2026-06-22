#include <stdio.h>
#include <stdlib.h>
#include "stack.c"
#include "sort.c"
#include "graham_slow.c"

int main()
{
    char   in_file[256];       
    char   out_file[256];      
    FILE  *fp_in  = NULL;     
    FILE  *fp_out = NULL;      
    Point *pts    = NULL;      
    Stack  hull;              
    int    n;                 
    int    m;                 
    int    i;               

    printf("Enter input  filename (e.g. sample-input.txt) : ");
    scanf("%255s", in_file);

    printf("Enter output filename (e.g. sample-output.txt): ");
    scanf("%255s", out_file);

    fp_in = fopen(in_file, "r");

    if (fp_in == NULL) {
        fprintf(stderr, "ERROR: Cannot open input file '%s'.\n", in_file);
        return EXIT_FAILURE;
    }

    fscanf(fp_in, "%d", &n);

    if (n < 1 || n > MAX_POINTS) {
        fprintf(stderr, "ERROR: n = %d is out of valid range [1, %d].\n",
                n, MAX_POINTS);
        fclose(fp_in);
        return EXIT_FAILURE;
    }

    pts = (Point *)malloc(n * sizeof(Point));

    if (pts == NULL) {
        fprintf(stderr, "ERROR: Memory allocation failed.\n");
        fclose(fp_in);
        return EXIT_FAILURE;
    }

    for (i = 0; i < n; i++)
        fscanf(fp_in, "%lf %lf", &pts[i].x, &pts[i].y);

    graham_scan_slow(pts, n, &hull);

    fp_out = fopen(out_file, "w");

    if (fp_out == NULL) {
        fprintf(stderr, "ERROR: Cannot open output file '%s'.\n", out_file);
        free(pts);
        fclose(fp_in);
        return EXIT_FAILURE;
    }

    m = hull.top + 1;   
    fprintf(fp_out, "%d\n", m);

    for (i = 0; i < m; i++)
        fprintf(fp_out, "%9.6f  %9.6f\n", hull.data[i].x, hull.data[i].y);

    fclose(fp_in);
    fclose(fp_out);
    free(pts);

    printf("Convex hull (%d points) written to '%s'.\n", m, out_file);

    return 0;
}
