#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef void (* func_t)(int*, int);

void FillRandom( int* array, int size );
void DoubleUp( int* array, int size );
void Print( int* array, int size );

void ProxyFunction( func_t func, int* array, int size );

void main(void) 
{
    int array[10];
    int menu;

    while( 1 )
    {
        printf( "[0] 종료 [1] 생성 [2] 두배 [3] 출력 - " );
        scanf( "%d", &menu );

        if( menu == 0 )
            break;

        switch( menu )
        {
        case 1 : ProxyFunction( FillRandom, array, 10 );   break;
        case 2 : ProxyFunction( DoubleUp, array, 10 );     break;
        case 3 : ProxyFunction( Print, array, 10 );        break;
        }
    }
}

void FillRandom( int* array, int size )
{
    int i;
    for( i = 0; i < size; i++ )
        array[i] = rand() % 100;
}

void DoubleUp( int* array, int size )
{
    int i;
    for( i = 0; i < size; i++ )
        array[i] *= 2;
}

void Print( int* array, int size )
{
    int i;
    for( i = 0; i < size; i++ )
        printf( "%3d ", array[i] );

    printf( "\n" );
}

void ProxyFunction( func_t func, int* array, int size )
{
    func( array, size );
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
