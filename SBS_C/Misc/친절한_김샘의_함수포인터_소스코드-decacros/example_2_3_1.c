#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

enum { ARRAY_SIZE = 20 };

void FillRandom( int* array, int size );
void Print( int* array, int size );
int Find( int* array, int size, int value, int(* comp)(int, int) );
int IsBigger( int n1, int n2 );

void main(void) 
{
    int array[ARRAY_SIZE];
    int value, result;

    FillRandom( array, ARRAY_SIZE );
    Print( array, ARRAY_SIZE );
    printf( "종료 - 음수 입력\n\n" );

    while( 1 )
    {
        printf( "검색 : " );
        scanf( "%d", &value );

        if( value < 0 )
            break;

        result = Find( array, ARRAY_SIZE, value, IsBigger );

        if( result != -1 )
            printf( "결과 : %d번째[%d]\n", result, array[result] );
        else
            printf( "결과 : 없음\n" );
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

int Find( int* array, int size, int value, int(* comp)(int, int) )
{
    int i;
    for( i = 0; i < size; i++ )
    {
//        if( comp(array[i], value) == comp(value, array[i]) )
        if( comp(array[i], value) == 0 && comp(value, array[i]) == 0 )
            return i;
    }

    return -1;
}

int IsBigger( int n1, int n2 )
{
    return n1 > n2;
}

/*
[출력결과]
 41  67  34   0  69  24  78  58  62  64
  5  45  81  27  61  91  95  42  27  36
종료 - 음수입력

검색 : 27
결과 : 13번째[27]
검색 : 78
결과 : 6번째[78]
검색 : 99
결과 : 없음
검색 : -1
*/
