#include <stdio.h>

void Hello(void);
void PrintNumber( int n );
void PrintArray( int* array, int size );

typedef void (* func_t)(void);

void main(void)
{
    int array[10] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 };
    void (* FuncArray[])(void) = { Hello, (func_t) PrintNumber, (func_t) PrintArray };

    FuncArray[0]();
    ((void (*)(int)) FuncArray[1])( 99 );
    ((void (*)(int*, int)) FuncArray[2])( array, 10 );
}

void Hello(void)
{
    printf( "%-13s\n", "Hello()" );
}

void PrintNumber( int n )
{
    printf( "%-13s [%d]\n", "PrintNumber()", n );
}

void PrintArray( int* array, int size )
{
    int i;
    printf( "%-13s [", "PrintArray()" );

    for( i = 0; i < size; i++ )
        printf( "%d ", array[i] );
    printf( "\b]\n" );
}

/*
[출력결과]
Hello()
PrintNumber() [99]
PrintArray()  [1 3 5 7 9 2 4 6 8 0]
*/
