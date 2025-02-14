#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

enum { ARRAY_SIZE = 20 };

void FillRandom( int* array, int size );
void Print( int* array, int size );
void SelectionSort( int* array, int size );
void Selection( int* array, int size );

void main(void) 
{
    int array[ARRAY_SIZE];

    do
    {
        FillRandom( array, ARRAY_SIZE );
        SelectionSort( array, ARRAY_SIZE );
        Print( array, ARRAY_SIZE );

        printf( "종료[space]\n" );
    }
    while( getch() != ' ' );
}

void FillRandom( int* array, int size )
{
    int i;
    for( i = 0; i < size; i++ )
        array[i] = rand() % 100;
}

void Print( int* array, int size )
{
    int i;
    for( i = 0; i < size; i++ )
    {
        printf( "%3d ", array[i] );

        if( i%10 == 9 )
            printf( "\n" );
    }
}

void Selection( int* array, int size )
{
    int i, MaxPos = 0;
    for( i = 1; i < size; i++ )
    {
        if( array[i] > array[MaxPos] )
            MaxPos = i;
    }

    i = array[MaxPos];
    array[MaxPos] = array[size-1];
    array[size-1] = i;
}

void SelectionSort( int* array, int size )
{
    int i;
    for( i = size; i > 1; i-- )
        Selection( array, i );
}

/*
[출력결과]
  0   5  24  27  27  34  36  41  42  45
 58  61  62  64  67  69  78  81  91  95
종료[space]
  2   4  12  16  18  21  26  35  38  47
 53  67  69  71  82  91  92  94  95  99
종료[space]
  3  11  11  22  23  29  33  37  41  41
 44  47  53  57  59  62  64  68  73  78
종료[space]
*/
