/*
 * main.c
 *
 * Driver program for the Undirected Graph SNS project.
 * Reads a graph description file, builds the adjacency-list
 * representation (graph.c/.h), then produces:
 *   Output File #1  <NAME>-SET.TXT      (V(G) and E(G))
 *   Output File #2  <NAME>-DEGREE.TXT   (vertex degrees)
 *   Output File #3  <NAME>-LIST.TXT     (adjacency list view)
 *   Output File #4  <NAME>-MATRIX.TXT   (adjacency matrix view)
 * then asks for a start vertex and, if it exists, produces:
 *   Output File #5  <NAME>-BFS.TXT
 *   Output File #6  <NAME>-DFS.TXT
 *
 * Programmer: <your name here>
 * Tester:     <your name here>
 */

#include <stdio.h>
#include <string.h>
#include "graph.h"
#include "traversal.h"

/* Copies strInputFileName into outBaseName, dropping the
   trailing ".XXX" extension (if any). Example: "G.TXT" -> "G" 
   got helo with gemini...*/
static void GetBaseName(const char *strInputFileName, char *outBaseName)
{
    int i, lastDot;

    lastDot = -1;
    for (i = 0; strInputFileName[i] != '\0'; i++) {
        if (strInputFileName[i] == '.') {
            lastDot = i;
        }
    }

    if (lastDot == -1) {
        strcpy(outBaseName, strInputFileName);
    } else {
        strncpy(outBaseName, strInputFileName, lastDot);
        outBaseName[lastDot] = '\0';
    }
}

static void SortIndices(const Graph *g, int idxOrder[])
{
    int i, j, temp, n;

    n = g->numVertices;
    for (i = 0; i < n; i++) {
        idxOrder[i] = i;
    }
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(g->vertices[idxOrder[j]].label,
                       g->vertices[idxOrder[j + 1]].label) > 0) {
                temp = idxOrder[j];
                idxOrder[j] = idxOrder[j + 1];
                idxOrder[j + 1] = temp;
            }
        }
    }
}

typedef struct {
    int startIdx;
    int endIdx;
} EdgePair;

static int BuildEdgeList(const Graph *g, EdgePair edges[])
{
    int i, edgeCount;
    AdjNode *cur;

    edgeCount = 0;
    for (i = 0; i < g->numVertices; i++) {
        cur = g->vertices[i].adjList;
        while (cur != NULL) {
            if (strcmp(g->vertices[i].label,
                       g->vertices[cur->vertexIndex].label) < 0) {
                edges[edgeCount].startIdx = i;
                edges[edgeCount].endIdx = cur->vertexIndex;
                edgeCount++;
            }
            cur = cur->next;
        }
    }

    {
        int a, b;
        EdgePair tmp;
        for (a = 0; a < edgeCount - 1; a++) {
            for (b = 0; b < edgeCount - a - 1; b++) {
                int cmp = strcmp(g->vertices[edges[b].startIdx].label,
                                  g->vertices[edges[b + 1].startIdx].label);
                if (cmp == 0) {
                    cmp = strcmp(g->vertices[edges[b].endIdx].label,
                                 g->vertices[edges[b + 1].endIdx].label);
                }
                if (cmp > 0) {
                    tmp = edges[b];
                    edges[b] = edges[b + 1];
                    edges[b + 1] = tmp;
                }
            }
        }
    }

    return edgeCount;
}

static int VertexDegree(const Graph *g, int idx)
{
    int deg = 0;
    AdjNode *cur = g->vertices[idx].adjList;
    while (cur != NULL) {
        deg++;
        cur = cur->next;
    }
    return deg;
}

// Output File 1, sets
static int sets(const char *strOutputFileName, const Graph *g,
                               const char *graphName)
{
    FILE *fp;
    int idxOrder[MAX_VERTICES];
    EdgePair edges[MAX_VERTICES * MAX_VERTICES];
    int edgeCount, i;

    fp = fopen(strOutputFileName, "w");
    if (fp == NULL) {
        return 0;
    }

    SortIndices(g, idxOrder);

    fprintf(fp, "V(%s)={", graphName);
    for (i = 0; i < g->numVertices; i++) {
        fprintf(fp, "%s", g->vertices[idxOrder[i]].label);
        if (i != g->numVertices - 1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "}\n");

    edgeCount = BuildEdgeList(g, edges);

    fprintf(fp, "E(%s)={", graphName);
    for (i = 0; i < edgeCount; i++) {
        fprintf(fp, "(%s,%s)",
                g->vertices[edges[i].startIdx].label,
                g->vertices[edges[i].endIdx].label);
        if (i != edgeCount - 1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "}\n");

    fclose(fp);
    return 1;
}

//Output File 2, degree
static int funcDegree(const char *strOutputFileName, const Graph *g)
{
    FILE *fp;
    int idxOrder[MAX_VERTICES];
    int i;

    fp = fopen(strOutputFileName, "w");
    if (fp == NULL) {
        return 0;
    }

    SortIndices(g, idxOrder);

    for (i = 0; i < g->numVertices; i++) {
        fprintf(fp, "%s %d\n", g->vertices[idxOrder[i]].label,
                VertexDegree(g, idxOrder[i]));
    }

    fclose(fp);
    return 1;
}

// Output File 3, list
static int lists(const char *strOutputFileName, const Graph *g)
{
    FILE *fp;
    int i;
    AdjNode *cur;

    fp = fopen(strOutputFileName, "w");
    if (fp == NULL) {
        return 0;
    }

    for (i = 0; i < g->numVertices; i++) {
        fprintf(fp, "%s->", g->vertices[i].label);
        cur = g->vertices[i].adjList;
        while (cur != NULL) {
            fprintf(fp, "%s->", g->vertices[cur->vertexIndex].label);
            cur = cur->next;
        }
        fprintf(fp, "\\\n");
    }

    fclose(fp);
    return 1;
}

// Output File 4, matrix
static int matrix(const char *strOutputFileName, const Graph *g)
{
    FILE *fp;
    int i, j;
    int matrix[MAX_VERTICES][MAX_VERTICES];
    AdjNode *cur;

    fp = fopen(strOutputFileName, "w");
    if (fp == NULL) {
        return 0;
    }

    for (i = 0; i < g->numVertices; i++) {
        for (j = 0; j < g->numVertices; j++) {
            matrix[i][j] = 0;
        }
    }
    for (i = 0; i < g->numVertices; i++) {
        cur = g->vertices[i].adjList;
        while (cur != NULL) {
            matrix[i][cur->vertexIndex] = 1;
            cur = cur->next;
        }
    }

    for (j = 0; j < g->numVertices; j++) {
        fprintf(fp, " %s", g->vertices[j].label);
    }
    fprintf(fp, "\n");

    for (i = 0; i < g->numVertices; i++) {
        fprintf(fp, "%s", g->vertices[i].label);
        for (j = 0; j < g->numVertices; j++) {
            fprintf(fp, " %d", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    return 1;
}

// Output File 5, bfs sort using queuess
static int BFSout(const char *strOutputFileName, const Graph *g,
                               const char *strStartLabel)
{
    FILE *fp;
    int output[MAX_VERTICES];
    int count, i;

    BFS(g, strStartLabel, output, &count);

    fp = fopen(strOutputFileName, "w");
    if (fp == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        fprintf(fp, "%s", g->vertices[output[i]].label);
        if (i != count - 1) {
            fprintf(fp, " ");
        }
    }
    fprintf(fp, "\n");

    fclose(fp);
    return 1;
}

// Output File 6, dfs sort using stacks
static int DFSout(const char *strOutputFileName, const Graph *g,
                               const char *strStartLabel)
{
    FILE *fp;
    int output[MAX_VERTICES];
    int count, i;

    DFS(g, strStartLabel, output, &count);

    fp = fopen(strOutputFileName, "w");
    if (fp == NULL) {
        return 0;
    }

    for (i = 0; i < count; i++) {
        fprintf(fp, "%s", g->vertices[output[i]].label);
        if (i != count - 1) {
            fprintf(fp, " ");
        }
    }
    fprintf(fp, "\n");

    fclose(fp);
    return 1;
}

int main(void)
{
    char strInputFileName[100];
    char baseName[100];
    char outName[120];
    char startLabel[MAX_LABEL_LEN + 1];
    Graph g;
    int ok;

    printf("Enter input filename: ");
    scanf("%99s", strInputFileName);

    ok = ReadInputFile(strInputFileName, &g);
    if (!ok) {
        printf("File %s not found.\n", strInputFileName);
        return 0;
    }

    GetBaseName(strInputFileName, baseName);

    sprintf(outName, "%s-SET.TXT", baseName);
    sets(outName, &g, baseName);

    sprintf(outName, "%s-DEGREE.TXT", baseName);
    funcDegree(outName, &g);

    sprintf(outName, "%s-LIST.TXT", baseName);
    lists(outName, &g);

    sprintf(outName, "%s-MATRIX.TXT", baseName);
    matrix(outName, &g);

    printf("Enter start vertex: ");
    scanf("%8s", startLabel);

    if (FindVertexIndex(&g, startLabel) == -1) {
        printf("Vertex %s not found.\n", startLabel);
        FreeGraph(&g);
        return 0;
    }

    sprintf(outName, "%s-BFS.TXT", baseName);
    BFSout(outName, &g, startLabel);

    sprintf(outName, "%s-DFS.TXT", baseName);
    DFSout(outName, &g, startLabel);

    FreeGraph(&g);
    return 0;
}
