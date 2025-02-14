#include <stdio.h> 
#pragma warning(disable:4996)

void Hello(void);
void GoodNight(void);
void WhatsUp(void);

typedef void (* func_t)(void);

void main(void) 
{
    func_t FuncArray[3] = { Hello, GoodNight, WhatsUp };
    int menu;

    while( 1 )
    {
        printf( "[0] Quit [1] Hello [2] GoodNight [3] WhatsUp - " );
        scanf( "%d", &menu );

        if( menu < 0 || menu > 3 )
            continue;

        if( menu == 0 )
            break;

        FuncArray[menu-1]();
    }
}

void Hello(void)
{
    printf( "Hello?\n" );
}

void GoodNight(void)
{
    printf( "Good night!\n" );
}

void WhatsUp(void)
{
    printf( "What's up?\n" );
}

/*
[출력결과]
[0] Quit [1] Hello [2] GoodNight [3] WhatsUp - 1
Hello?
[0] Quit [1] Hello [2] GoodNight [3] WhatsUp - 2
Good night!
[0] Quit [1] Hello [2] GoodNight [3] WhatsUp - 3
What's up?
[0] Quit [1] Hello [2] GoodNight [3] WhatsUp - 0
*/