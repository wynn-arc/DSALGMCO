

#ifndef GRAPH_H
#define GRAPH_H

#define MAX_VERTICES   20   /* max number of vertices allowed in a graph      */
#define MAX_LABEL_LEN  8    /* max length of a vertex ID/label (excl. \0)     */


typedef struct AdjNode {
    int vertexIndex;          /* index into Graph.vertices[] of the neighbor */
    struct AdjNode *next;     /* next neighbor in the list, NULL if none     */
} AdjNode;


typedef struct {
    char label[MAX_LABEL_LEN + 1];  /* +1 for null terminator */
    AdjNode *adjList;                /* head of this vertex's adjacency list */
} VertexEntry;


typedef struct {
    VertexEntry vertices[MAX_VERTICES];
    int numVertices;
} Graph;


void InitGraph(Graph *g);

/* Reads the input text file (e.g. "G.TXT") and builds the
   adjacency-list representation inside *g.
   Returns 1 on success, 0 if the file could not be opened. */
int ReadInputFile(const char *strInputFileName, Graph *g);

/* Returns the array index of the vertex with the given label,
   or -1 if the label does not exist in the graph. */
int FindVertexIndex(const Graph *g, const char *label);

/* Allocates and returns a new AdjNode pointing to vertexIndex. */
AdjNode *CreateAdjNode(int vertexIndex);

/* Frees all dynamically allocated adjacency-list nodes and
   resets the graph. Call this before program exit to avoid
   memory leaks. */
void FreeGraph(Graph *g);

#endif /* GRAPH_H */
