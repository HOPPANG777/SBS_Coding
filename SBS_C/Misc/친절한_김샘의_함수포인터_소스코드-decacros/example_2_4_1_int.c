#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

enum { ARRAY_SIZE = 20 };

void FillRandom( int* array, int size );
void Print( int* array, int size );

void Selection( void* array, int count, int typesize, int (* cmp)(const void*, const void*) );
void SelectionSort( void* array, int count, int typesize, int (* cmp)(const void*, const void*) );
int CompareInt( const void* p1, const void* p2 );

void main(void) 
{
    int array[ARRAY_SIZE];

    do
    {
        FillRandom( array, ARRAY_SIZE );
        SelectionSort( array, ARRAY_SIZE, sizeof(array[0]), CompareInt );
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

void Selection( void* array, int count, int typesize, int (* cmp)(const void*, const void*) )
{
    char* base = array, * buf = malloc( typesize );
    int i, MaxPos = 0;
    for( i = 1; i < count; i++ )
    {
        if( cmp(base+i*typesize, base+MaxPos*typesize) > 0 )
            MaxPos = i;
    }

    memcpy( buf, base+(count-1)*typesize, typesize );
    memcpy( base+(count-1)*typesize, base+MaxPos*typesize, typesize );
    memcpy( base+MaxPos*typesize, buf, typesize );

    free( buf );
}

void SelectionSort( void* array, int count, int typesize, int (* cmp)(const void*, const void*) )
{
    int i;
    for( i = count; i > 1; i-- )
        Selection( array, i, typesize, cmp );
}

int CompareInt( const void* p1, const void* p2 )
{
    return *(int*) p2 - *(int*) p1;
}

/*
[출력 결과]
 95  91  81  78  69  67  64  62  61  58
 45  42  41  36  34  27  27  24   5   0
종료[space]
 99  95  94  92  91  82  71  69  67  53
 47  38  35  26  21  18  16  12   4   2
종료[space]
 78  73  68  64  62  59  57  53  47  44
 41  41  37  33  29  23  22  11  11   3
종료[space]
*/
