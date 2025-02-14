enum { STACK_SIZE = 1024 };

struct STACK
{
    int stack[STACK_SIZE];
    int top;

    void (* Push)(struct STACK*, int);
    int (* Pop)(struct STACK*);
    int (* IsEmpty)(struct STACK*);
};

void InitStack( struct STACK* pStack );
