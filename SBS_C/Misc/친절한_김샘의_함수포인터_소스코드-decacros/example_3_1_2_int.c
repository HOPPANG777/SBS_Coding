#include <stdio.h>
#pragma warning(disable:4996)

int CompareInt( const void* p1, const void* p2 );
void* LinearSearch( void* value, void* array, int count, int typesize, int (*cmp)(const void*, const void*) );

void main(void) 
{
    int array[] = { 99, 77, 55, 33, 11, 0, 88, 66, 44, 22 };
    int i, number, * find;

    printf( "[원본] " );
    for( i = 0; i < 10; i++ )
        printf( "%d ", array[i] );

    printf( "\n\n" );

    /////////////////////////////////////

    while( 1 )
    {
        printf( "입력 - " );
        scanf( "%d", &number );

        find = LinearSearch( &number, array, 10, sizeof(int), CompareInt );

        if( find == NULL )
            break;

        printf( "성공 - %d\n\n", *find );
    }
}

int CompareInt( const void* p1, const void* p2 )
{
    return *(int*) p1 > *(int*) p2;
}

void* LinearSearch( void* value, void* array, int count, int typesize, int (*cmp)(const void*, const void*) )
{
    int i;
    char* cur;

    for( i = 0; i < count; i++ )
    {
        cur = (char*) array + i*typesize;

        if( !cmp(value, cur) && !cmp(cur, value) )
            return cur;
    }

    return NULL;
}

/*
[출력결과]
[원본] 99 77 55 33 11 0 88 66 44 22

입력 - 99
성공 - 99

입력 - 22
성공 - 22

입력 - 33
성공 - 33

입력 - 19
*/
