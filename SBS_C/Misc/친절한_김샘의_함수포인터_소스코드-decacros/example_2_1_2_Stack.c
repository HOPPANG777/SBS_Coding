#include "example_2_1_2_Stack.h"

void Push( struct STACK* pStack, int data )
{
    pStack->stack[pStack->top++] = data;
}

int Pop( struct STACK* pStack )
{
    return pStack->stack[--pStack->top];
}

int IsEmpty(struct STACK* pStack )
{
    return pStack->top == 0;
}

void InitStack( struct STACK* pStack )
{
    pStack->top = 0;

    pStack->Push    = Push;
    pStack->Pop     = Pop;
    pStack->IsEmpty = IsEmpty;
}
