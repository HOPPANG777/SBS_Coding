#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

void Print( char words[][32], int size );
void Selection( void* array, int count, int typesize, int (* cmp)(const void*, const void*) );
void SelectionSort( void* array, int count, int typesize, int (* cmp)(const void*, const void*) );
int CompareStringAsc( const void* p1, const void* p2 );
int CompareStringDsc( const void* p1, const void* p2 );

void main(void) 
{
    char words[][32] = 
    {
        "swing", "book", "dance", "white", "chocolate", "paper", "sea", "buffet", "sports", "bed",
    };

    printf( "[원본]\n" );
    Print( words, sizeof(words)/sizeof(words[0]) );

    SelectionSort( words, sizeof(words)/sizeof(words[0]), sizeof(words[0]), CompareStringAsc );

    printf( "[오름차순]\n" );
    Print( words, sizeof(words)/sizeof(words[0]) );

    SelectionSort( words, sizeof(words)/sizeof(words[0]), sizeof(words[0]), CompareStringDsc );

    printf( "[내림차순]\n" );
    Print( words, sizeof(words)/sizeof(words[0]) );
}

void Print( char words[][32], int size )
{
    int i;
    for( i = 0; i < size; i++ )
    {
        printf( "%10s ", words[i] );

        if( i%5 == 4 )
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

int CompareStringAsc( const void* p1, const void* p2 )
{
    return strcmp(p1, p2);
}

int CompareStringDsc( const void* p1, const void* p2 )
{
    return strcmp(p2, p1);
}

/*
[출력결과]
[원본]
     swing       book      dance      white  chocolate
     paper        sea     buffet     sports        bed
[오름차순]
       bed       book     buffet  chocolate      dance
     paper        sea     sports      swing      white
[내림차순]
     white      swing     sports        sea      paper
     dance  chocolate     buffet       book        bed
*/
