#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>
#pragma warning(disable:4996)

enum { ARRAY_SIZE = 20 };

void FillRandom( int* array, int size );
void Print( int* array, int size );
void SelectionSort( int* array, int size, int (* CmpFunc)(int, int) );
void Selection( int* array, int size, int (* CmpFunc)(int, int) );

int CompareAsc( int n1, int n2 );
int CompareDsc( int n1, int n2 );

void main(void) 
{
    int ch;
    int array[ARRAY_SIZE];

    while( 1 )
    {
        printf( "종료[space] 오름차순[A] 내림차순[D]\n" );

        ch = toupper( getch() );

        if( ch == ' ' )
            break;

        if( ch != 'A' && ch != 'D' )
            continue;

        FillRandom( array, ARRAY_SIZE );

        if( ch == 'A' )     SelectionSort( array, ARRAY_SIZE, CompareAsc );
        else                SelectionSort( array, ARRAY_SIZE, CompareDsc );

        Print( array, ARRAY_SIZE );
    }
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

void Selection( int* array, int size, int (* CmpFunc)(int, int) )
{
    int i, MaxPos = 0;
    for( i = 1; i < size; i++ )
    {
        if( CmpFunc(array[i], array[MaxPos]) == 1 )
            MaxPos = i;
    }

    i = array[MaxPos];
    array[MaxPos] = array[size-1];
    array[size-1] = i;
}

void SelectionSort( int* array, int size, int (* CmpFunc)(int, int) )
{
    int i;
    for( i = size; i > 1; i-- )
        Selection( array, i, CmpFunc );
}

int CompareAsc( int n1, int n2 )
{
    return n1 > n2;
}

int CompareDsc( int n1, int n2 )
{
    return n1 < n2;
}

/*
[출력결과]
종료[space] 오름차순[A] 내림차순[D]
  0   5  24  27  27  34  36  41  42  45
 58  61  62  64  67  69  78  81  91  95
종료[space] 오름차순[A] 내림차순[D]
 99  95  94  92  91  82  71  69  67  53
 47  38  35  26  21  18  16  12   4   2
종료[space] 오름차순[A] 내림차순[D]
  3  11  11  22  23  29  33  37  41  41
 44  47  53  57  59  62  64  68  73  78
종료[space] 오름차순[A] 내림차순[D]
 93  90  90  88  70  64  50  48  48  46
 42  42  40  35  29  16   6   6   5   1
종료[space] 오름차순[A] 내림차순[D]
*/
