#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>
#pragma warning(disable:4996)

void ThreadProc( void* pv );

void main(void) 
{
    printf( "Press Any Key...\n" );

    _beginthread( ThreadProc, 0, NULL );
    getch();
}

void ThreadProc( void* pv )
{
    while( 1 )
    {
        putchar( '.' );
        Sleep( 100 );
    }
}

/*
[출력결과]
Press Any Key...
................................
*/
