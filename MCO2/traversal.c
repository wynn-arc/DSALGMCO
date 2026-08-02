#include <string.h>
#include "traversal.h"
#include "queue.h"

static void sortNeighbors(const Graph *g, int neighbors[], int count){
    int i, j, temp;

    for(i = 0; i < count - 1; i++){
        for (j = 0; j < count - i - 1; j++){
            if (strcmp(g->vertices[neighbors[j]].label, g->vertices[neighbors[j+1]].label) > 0){
                temp = neighbors[j];
                neighbors[j] = neighbors[j+1];
                neighbors[j+1] = temp;
            }
        }
    }
}

void DFSRecursion(const Graph *g, int currentIdx; int visited[], int output[], int *count){
    AdjNode *cur;
    int neighbors[MAX_VERTICES];
    int ctr = 0;
    int i;

    visited[currentIdx] = 1;
    output[(*count)] = currentIdx;
    (*count)++;

    cur = g->vertices[currentIdx].adjList;
    
    while (cur != NULL){
        if (!visited[cur->vertexIndex]){
            neighbors[ctr++];
        }
        cur = cur->next;
    }

    SortNeighbors(g, neighbors, count);

    for (i = 0; i < ctr; i++){
        if (!visited[neighbors[i]]){
            DFSRecursive(g, neighbors[i], visited, output, count);
        }
    }
}

void DFS (const Graph *g, const char *startLabel, int output[], int *count){
    int visited[MAX_VERTICES];
    int startIdx = FindVertexIndex(g, startLabel);
    int i;

    *count = 0;

    if (startIdx == -1){
        return;
    }

    for (i = 0; i < MAX_VERTICES; i++){
        visited[i] = 0;
    }

    DFSRecursive(g, startIdx, visited, output, count);
}

void BFS (const Graph *g, const char *startLabel, int output[], int *count){
    int visited[MAX_VERTICES];
    int startIdx = FindVertexIndex(g, startLabel);
    int currentIdx;
    int i;
    Queue q;
    AdjNode *cur;
    int neighbors[MAX_VERTICES];
    int ctr = 0;

    *count = 0;

    if (startIdx == -1){
        return;
    }

    for (i = 0; i < MAX_VERTICES; i++){
        visited[i] = 0;
    }

    InitQueue(&q);

    visited[startIdx] = 1;
    Enqueue(&q, startIdx);

    while (!IsQueueEmpty(&q)){
        currentIdx = Dequeue(&q);
        
        output[(*count)] = currentIdx;
        (*count)++

        cur = g->vertices[currentIdx].adjList;
        
        while (cur != NULL){
            if (!visited[cur->vertexIndex]){
                visited[cur->vertexIndex] = 1;
                neighbors[count++] = cur->vertexIndex;
            }
            cur = cur->next;
        }

        SortNeighbors(g, neighbors, count);

        for (i = 0; i < count; i++){
            Enqueue(&q, neighbors[i]);
        }
    }
}
    
