#ifndef STACK_H
#define STACK_H
#include "maze.h"
 
#define MAX_STACK (ROWS * COLS)
 
typedef struct {
    Position data[MAX_STACK];
    int top;
} Stack;
 
void stackInit(Stack *s);
int  stackIsEmpty(Stack *s);
int  stackIsFull(Stack *s);
void stackPush(Stack *s, Position pos);
Position stackPop(Stack *s);
Position stackPeek(Stack *s);
#endif

