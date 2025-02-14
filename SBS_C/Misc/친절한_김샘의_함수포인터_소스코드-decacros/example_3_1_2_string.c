#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

void PrintWords( char** words, int size );
int CompareString( const void* p1, const void* p2 );
void* LinearSearch( void* value, void* array, int count, int typesize, int (*cmp)(const void*, const void*) );

void main(void) 
{
    char* words[] = 
    { 
        "lemon", "tooth", "cup", "pencil", "book", "cable", "coke", "speaker", "white", "traffic"
    };
    char buf[32], * input = buf, ** find;

    printf( "[원본] " );
    PrintWords( words, sizeof(words)/sizeof(words[0]) );

    while( 1 )
    {
        printf( "입력 - " );
        scanf( "%s", input );

        find = LinearSearch( &input, words, sizeof(words)/sizeof(words[0]), sizeof(words[0]), CompareString );

        if( find == NULL )
            break;

        printf( "성공 - %s\n\n", *find );
    }
}

void PrintWords( char** words, int size )
{
    int i;
    for( i = 0; i < size; i++ )
        printf( "%s ", *words++ );

    printf( "\n\n" );
}

int CompareString( const void* p1, const void* p2 )
{
    return strcmp(*(char**) p1, *(char**) p2) > 0;
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
[원본] lemon tooth cup pencil book cable coke speaker white traffic

입력 - lemon
성공 - lemon

입력 - traffic
성공 - traffic

입력 - book
성공 - book

입력 - cake
*/
