/*
 * 12-BONUS.c
 *
 * BONUS: checks whether graph H (the "second" graph) is a subgraph
 * of graph G (the "first" graph), and produces Output File #7:
 *   <FIRST>-<SECOND>-SUBGRAPH.TXT
 *
 * This is a standalone program with its own main() -- it is compiled
 * and run separately from main.c. It links against graph.c/graph.h,
 * which already provide ReadInputFile(), FindVertexIndex(), etc.
 *
 * Programmer: <your name here>
 * Tester:     <your name here>
 */

#include <stdio.h>
#include <string.h>
#include "graph.h"

static void GetBaseName(const char *strFileName, char *outBaseName)
{
    int i, lastDot;

    lastDot = -1;
    for (i = 0; strFileName[i] != '\0'; i++) {
        if (strFileName[i] == '.') {
            lastDot = i;
        }
    }

    if (lastDot == -1) {
        strcpy(outBaseName, strFileName);
    } else {
        strncpy(outBaseName, strFileName, lastDot);
        outBaseName[lastDot] = '\0';
    }
}

static void SortIndicesByLabel(const Graph *g, int idxOrder[])
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

static int EdgeExistsInGraph(const Graph *g, const char *labelA, const char *labelB)
{
    int idxA, idxB;
    AdjNode *cur;

    idxA = FindVertexIndex(g, labelA);
    idxB = FindVertexIndex(g, labelB);
    if (idxA == -1 || idxB == -1) {
        return 0;
    }

    cur = g->vertices[idxA].adjList;
    while (cur != NULL) {
        if (cur->vertexIndex == idxB) {
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

static int subgraphs(const char *outFile,
                               const Graph *first, const char *firstName,
                               const Graph *second, const char *secondName)
{
    FILE *fp;
    int idxOrder[MAX_VERTICES];
    EdgePair edges[MAX_VERTICES * MAX_VERTICES];
    int edgeCount, i;
    int allVerticesOk, allEdgesOk;
    int inFirst;

    fp = fopen(outFile, "w");
    if (fp == NULL) {
        return 0;
    }

    allVerticesOk = 1;
    allEdgesOk = 1;

    /* marks +/- */
    SortIndicesByLabel(second, idxOrder);
    for (i = 0; i < second->numVertices; i++) {
        const char *label = second->vertices[idxOrder[i]].label;
        inFirst = (FindVertexIndex(first, label) != -1);
        if (!inFirst) {
            allVerticesOk = 0;
        }
        fprintf(fp, "%s %s\n", label, inFirst ? "+" : "-");
    }

    /* marks +/- part 2 */
    edgeCount = BuildEdgeList(second, edges);
    for (i = 0; i < edgeCount; i++) {
        const char *labelA = second->vertices[edges[i].startIdx].label;
        const char *labelB = second->vertices[edges[i].endIdx].label;
        int inFirstEdge = EdgeExistsInGraph(first, labelA, labelB);
        if (!inFirstEdge) {
            allEdgesOk = 0;
        }
        fprintf(fp, "(%s,%s) %s\n", labelA, labelB, inFirstEdge ? "+" : "-");
    }

    /* verdict */
    if (allVerticesOk && allEdgesOk) {
        fprintf(fp, "%s is a subgraph of %s.\n", secondName, firstName);
    } else {
        fprintf(fp, "%s is a NOT subgraph of %s.\n", secondName, firstName);
    }

    fclose(fp);
    return (allVerticesOk && allEdgesOk);
}

int main(void)
{
    char fileOne[100], fileTwo[100];
    char firstBase[100], secondBase[100];
    char outName[220];
    Graph gFirst, gSecond;

    printf("Enter first graph filename: ");
    scanf("%99s", fileOne);
    if (!ReadInputFile(fileOne, &gFirst)) {
        printf("File %s not found.\n", fileOne);
        return 0;
    }

    printf("Enter second graph filename: ");
    scanf("%99s", fileTwo);
    if (!ReadInputFile(fileTwo, &gSecond)) {
        printf("File %s not found.\n", fileTwo);
        FreeGraph(&gFirst);
        return 0;
    }

    GetBaseName(fileOne, firstBase);
    GetBaseName(fileTwo, secondBase);

    sprintf(outName, "%s-%s-SUBGRAPH.TXT", firstBase, secondBase);
    subgraphs(outName, &gFirst, firstBase, &gSecond, secondBase);

    FreeGraph(&gFirst);
    FreeGraph(&gSecond);
    return 0;
}
