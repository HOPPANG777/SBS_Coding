#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

void PrintWords( char** words );
int CompareString( const void* p1, const void* p2 );

void main(void) 
{
    char* words[] = 
    { 
        "lemon", "tooth", "cup", "pencil", "book", "cable", "coke", "speaker", "white", "traffic", NULL,
    };

    printf( "[원본] " );    PrintWords( words );

    qsort( words, sizeof(words)/sizeof(words[0])-1, sizeof(words[0]), CompareString );
    printf( "[정렬] " );    PrintWords( words );
}

void PrintWords( char** words )
{
    while( *words )
        printf( "%s ", *words++ );

    printf( "\n" );
}

int CompareString( const void* p1, const void* p2 )
{
    return strcmp( *(char**) p1, *(char**) p2 );
}

/*
[출력결과]
[원본] lemon tooth cup pencil book cable coke speaker white traffic
[정렬] book cable coke cup lemon pencil speaker tooth traffic white
*/
