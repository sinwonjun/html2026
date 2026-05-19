#include "stack.h"
 
void stackInit(Stack *s) { s->top = -1; }
int stackIsEmpty(Stack *s) { return s->top == -1; }
int stackIsFull(Stack *s) { return s->top == MAX_STACK - 1; }
 
void stackPush(Stack *s, Position pos) {
    if (!stackIsFull(s))
        s->data[++(s->top)] = pos;
}
 
Position stackPop(Stack *s) {
    return s->data[(s->top)--];
}
 
Position stackPeek(Stack *s) {
    return s->data[s->top];
}

