/**

    >> Encode your group number (2 digits) and last names, first names and sections of group members.  Encode the purpose of this file.

    Group #: 00  (2 digits)

    MANGAHAS, EOWYN SABRINA S13
    LUMBANG, VAUGHN  S14
    LASTNAME3, FIRSTNAME3  SECTION 

    PURPOSE OF THIS FILE: to show an example of a C source file that follows the coding guidelines/instructions.

    >> GENERAL INSTRUCTIONS: NON-COMPLIANCE WILL RESULT INTO AT LEAST A 10 POINT DEDUCTION!
    1. Adhere with good programming style and practice (learned from CCPROG1 and CCPROG2).
    2. Do NOT use global variables!  
    3. Do NOT use goto statement!
    4. Do NOT use return in a void function!

*/

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

void PUSH(Stack *S, Point elem)
{
    if (ISFULL(S)) {
        fprintf(stderr, "STACK OVERFLOW!\n");
        exit(EXIT_FAILURE);
    }

    (*S).top++;
    (*S).data[(*S).top] = elem;
}

Point POP(Stack *S)
{
    Point elem;

    if (ISEMPTY(S)) {
        fprintf(stderr, "STACK EMPTY!\n");
        exit(EXIT_FAILURE);
    }

    elem = (*S).data[(*S).top];
    (*S).top--;

    return elem;
}

Point TOP(Stack *S)
{
    if (ISEMPTY(S)) {
        fprintf(stderr, "STACK EMPTY!\n");
        exit(EXIT_FAILURE);
    }

    return (*S).data[(*S).top];
}
Point NEXT_TO_TOP(Stack *S)
{
    if ((*S).top < 1) {   
        fprintf(stderr, "NOT ENOUGH ELEMENTS\n");
        exit(EXIT_FAILURE);
    }

    return (*S).data[(*S).top - 1];
}
