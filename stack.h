

/*

    >> Encode your group number (2 digits) and last names, first names and sections of group members.  Encode the purpose of this file.

    Group #: 12 (2 digits)

    MANGAHAS, EOWYN SABRINA  S13
    LUMBANG, VAUGHN S14
    TAN, JEAN EMMANOEL S13

    PURPOSE OF THIS FILE: to show an example of a C header file that follows the coding guidelines/instructions.

    >> GENERAL INSTRUCTIONS:
    1. Adhere with good programming style and practice (learned from CCPROG1 and CCPROG2).
    3. Do NOT use global variables!  NON-COMPLIANCE WILL RESULT INTO A 10 POINT DEDUCTION!
*/

/*
    You may encode any of the following below this comment the following:   
    1. #define directives
    2. typedef alias(es) 
    3. declaration of your user-defined struct data type(s)
    4. typedef alias(es) for your struct data type(s) -- you have to put an inline comment 
       for each struct member as part of the documentation. 

    The header should NOT include the codes for any function definitions.  

    Function definitions should be encoded in your C source file only!
*/
#ifndef STACK_H
#define STACK_H
#include <stdio.h>
#include <stdlib.h>
#define MAX 32768

// stack struct
typedef struct {
    double x;
    double y;
} Point;

//ensure that the data has MAX
typedef struct {
    Point data[MAX];
    int top; //top element index
} Stack;

//function headers
void CREATE (Stack *S);
void  PUSH (Stack *S, Point elem);
Point POP (Stack *S);
Point TOP (Stack *S);
int ISFULL (Stack *S);
int ISEMPTY (Stack *S);
Point NEXT_TO_TOP (Stack *S);

#endif
  
