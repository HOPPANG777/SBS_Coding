#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void Change( int* pn );
void ToDouble( int* pn );
void PrintElement( int* pn );

void ProxyFunction( void (* func)(int*), int* array, int size );

void main(void) 
{
    void (* FuncArray[3])(int*) = { Change, ToDouble, PrintElement };
    int array[10] = { 0 };
    int menu;

    while( 1 )
    {
        printf( "[0] 종료 [1] 생성 [2] 두배 [3] 출력 - " );
        scanf( "%d", &menu );

        if( menu < 0 || menu > 3 )
            continue;

        if( menu == 0 )
            break;

        ProxyFunction( FuncArray[menu-1], array, 10 );

        if( menu == 3 )
            printf( "\n" );
    }
}

void Change( int* pn )
{
    *pn = rand() % 100;
}

void ToDouble( int* pn )
{
    *pn *= 2;
}

void PrintElement( int* pn )
{
    printf( "%3d ", *pn );
}

void ProxyFunction( void (* func)(int*), int* array, int size )
{
    int i;
    for( i = 0; i < size; i++ )
        func( array+i );
}

/*
[출력결과]
[0] 종료 [1] 생성 [2] 두배 [3] 출력 - 1
[0] 종료 [1] 생성 [2] 두배 [3] 출력 - 3
 41  67  34   0  69  24  78  58  62  64
[0] 종료 [1] 생성 [2] 두배 [3] 출력 - 2
[0] 종료 [1] 생성 [2] 두배 [3] 출력 - 3
 82 134  68   0 138  48 156 116 124 128
[0] 종료 [1] 생성 [2] 두배 [3] 출력 - 0
*/
