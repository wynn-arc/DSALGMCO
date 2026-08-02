#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
void CREATE(Stack *S)
{
    (*S).top = -1;
}
int ISFULL(Stack *S)
{
    return ((*S).top == MAX - 1);
}
int ISEMPTY(Stack *S)
{
    return ((*S).top == -1);
}

void Push(Stack *s, int value)
{
    s->top++;
    s->data[s->top] = value;
}

int POP(Stack *S)
{
    int elem;
    if (ISEMPTY(S)) {
        fprintf(stderr, "STACK EMPTY!\n");
        exit(EXIT_FAILURE);
    }
    elem = (*S).data[(*S).top];
    (*S).top--;
    return elem;
}
int TOP(Stack *S)
{
    if (ISEMPTY(S)) {
        fprintf(stderr, "STACK EMPTY!\n");
        exit(EXIT_FAILURE);
    }
    return (*S).data[(*S).top];
}
int NEXT_TO_TOP(Stack *S)
{
    if ((*S).top < 1) {   
        fprintf(stderr, "NOT ENOUGH ELEMENTS\n");
        exit(EXIT_FAILURE);
    }
    return (*S).data[(*S).top - 1];
}