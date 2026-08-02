#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>

#define MAX 32768   


typedef struct {
    double x;   
    double y; 
} Point;


typedef struct {
    int data[MAX]; 
    int   top;   
} Stack;


void  CREATE      (Stack *S);
void  PUSH        (Stack *S, Point elem);
int POP         (Stack *S);
int TOP         (Stack *S);
int   ISFULL      (Stack *S);
int   ISEMPTY     (Stack *S);
int NEXT_TO_TOP (Stack *S);

#endif 
