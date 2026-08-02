#ifndef TRAVERSALS_H
#define TRAVERSALS_H
#include "graph.h"

void BFS(const Graph *g, const char *startLabel, int Output[], int *Count);
void DFS(const Graph *g, const char *startLabel, int Output[], int *Count);

#endif