#include <stdio.h>
#include "Stack.h"

#pragma warning(disable:4996)

void main(void)
{
    struct STACK stack;
    int menu, data;

    InitOperation();
    Init( &stack );

    while( 1 )
    {
        printf( "[0] Á¾·á [1] ³Ö±â [2] »©±â - " );
        scanf( "%d", &menu );

        if( menu == 0 )
            break;

        switch( menu )
        {
        case 1 :
            printf( "Push : " );   
            scanf( "%d", &data );
            stack.op->Push( &stack, data );
            break;

        case 2 :
            if( stack.op->IsEmpty(&stack) == 0 )
                printf( "Pop  : %d\n", stack.op->Pop(&stack) );
            break;
        }
    }
}

/*
[Ãâ·Â°á°ú]
[0] Á¾·á [1] ³Ö±â [2] »©±â - 2
[0] Á¾·á [1] ³Ö±â [2] »©±â - 1
Push : 1
[0] Á¾·á [1] ³Ö±â [2] »©±â - 1
Push : 3
[0] Á¾·á [1] ³Ö±â [2] »©±â - 1
Push : 5
[0] Á¾·á [1] ³Ö±â [2] »©±â - 2
Pop  : 5
[0] Á¾·á [1] ³Ö±â [2] »©±â - 2
Pop  : 3
[0] Á¾·á [1] ³Ö±â [2] »©±â - 2
Pop  : 1
[0] Á¾·á [1] ³Ö±â [2] »©±â - 2
[0] Á¾·á [1] ³Ö±â [2] »©±â - 0
*/
