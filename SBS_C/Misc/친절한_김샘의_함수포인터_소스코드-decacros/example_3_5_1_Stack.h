#pragma once

struct STACK_OP;	// 전방 선언

struct STACK
{
    int array[256];
    int top;

    struct STACK_OP* op;
};

struct STACK_OP
{
    void (* Push)( struct STACK* ps, int data );
    int (* Pop)( struct STACK* ps );
    int (* IsEmpty)( struct STACK* ps );
};

void Init( struct STACK* ps );
void InitOperation(void);
