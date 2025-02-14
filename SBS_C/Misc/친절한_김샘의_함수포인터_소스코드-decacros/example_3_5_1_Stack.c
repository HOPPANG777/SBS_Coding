#include "Stack.h"

static struct STACK_OP g_op;

void Push( struct STACK* ps, int data )
{
    ps->array[ps->top++] = data;
}

int Pop( struct STACK* ps )
{
    return ps->array[--ps->top];
}

int IsEmpty( struct STACK* ps )
{
    return ps->top == 0;
}

void Init( struct STACK* ps )
{
    ps->top = 0;
    ps->op  = &g_op;
}

void InitOperation(void)
{
    g_op.Push    = Push;
    g_op.Pop     = Pop;
    g_op.IsEmpty = IsEmpty;
}
