
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"


void InitGraph(Graph *g) {
    int i;
    g->numVertices = 0;
    for (i = 0; i < MAX_VERTICES; i++) {
        g->vertices[i].label[0] = '\0';
        g->vertices[i].adjList = NULL;
    }
}


int FindVertexIndex(const Graph *g, const char *label) {
    int i;
    for (i = 0; i < g->numVertices; i++) {
        if (strcmp(g->vertices[i].label, label) == 0) {
            return i;
        }
    }
    return -1;
}


AdjNode *CreateAdjNode(int vertexIndex) {
    AdjNode *node = (AdjNode *)malloc(sizeof(AdjNode));
    if (node != NULL) {
        node->vertexIndex = vertexIndex;
        node->next = NULL;
    }
    return node;
}


static void AppendAdjNode(Graph *g, int srcIndex, int destIndex) {
    AdjNode *newNode = CreateAdjNode(destIndex);
    AdjNode *cur;

    if (newNode == NULL) {
        return; /* malloc failed; silently skip (could log an error here) */
    }

    if (g->vertices[srcIndex].adjList == NULL) {
        g->vertices[srcIndex].adjList = newNode;
    } else {
        cur = g->vertices[srcIndex].adjList;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = newNode;
    }
}


int ReadInputFile(const char *strInputFileName, Graph *g) {
    FILE *fp;
    int n, i, j;
    char label[MAX_LABEL_LEN + 1];
    char token[MAX_LABEL_LEN + 1];

    /* temporary storage for raw neighbor labels per vertex,
       collected during the single read of the file */
    char rawNeighbors[MAX_VERTICES][MAX_VERTICES][MAX_LABEL_LEN + 1];
    int neighborCount[MAX_VERTICES];

    fp = fopen(strInputFileName, "r");
    if (fp == NULL) {
        return 0; /* caller is responsible for printing the
                     "File <FILENAME.TXT> not found." message */
    }

    InitGraph(g);

    fscanf(fp, "%d", &n);
    g->numVertices = n;

    for (i = 0; i < n; i++) {
        fscanf(fp, "%s", label);
        strcpy(g->vertices[i].label, label);
        neighborCount[i] = 0;

        fscanf(fp, "%s", token);
        while (strcmp(token, "-1") != 0) {
            strcpy(rawNeighbors[i][neighborCount[i]], token);
            neighborCount[i]++;
            fscanf(fp, "%s", token);
        }
    }

    fclose(fp); /* file has now been read exactly once */

    /* Pass 2: resolve labels -> indices, build adjacency lists */
    for (i = 0; i < n; i++) {
        for (j = 0; j < neighborCount[i]; j++) {
            int idx = FindVertexIndex(g, rawNeighbors[i][j]);
            if (idx != -1) {
                AppendAdjNode(g, i, idx);
            }
            /* per spec, input is assumed correct/valid, so we
               don't need to handle idx == -1 as an error case */
        }
    }

    return 1;
}


void FreeGraph(Graph *g) {
    int i;
    for (i = 0; i < g->numVertices; i++) {
        AdjNode *cur = g->vertices[i].adjList;
        while (cur != NULL) {
            AdjNode *temp = cur;
            cur = cur->next;
            free(temp);
        }
        g->vertices[i].adjList = NULL;
    }
    g->numVertices = 0;
}
