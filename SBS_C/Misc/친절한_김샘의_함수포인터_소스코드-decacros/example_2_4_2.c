#include <stdio.h>
#include <ctype.h>
#include <string.h>
#pragma warning(disable:4996)

void PrintMatch( char words[][32], int size, int (* check)(const char*) );
int CheckOk( const char* str );
int CheckUppercase( const char* str );
int CheckLowercase( const char* str );
int CheckLength( const char* str );
int CheckFind( const char* str );

int  g_length = -1;
char g_letter = '\0';

void main(void) 
{
    char words[][32] = { "Hello", "TEST", "Newyork21", "1492", "memory", "MiNoR", "AccesS" };

    printf( "[전체  ] " );    PrintMatch( words, sizeof(words)/sizeof(words[0]), CheckOk );

    printf( "[대문자] " );    PrintMatch( words, sizeof(words)/sizeof(words[0]), CheckUppercase );
    printf( "[소문자] " );    PrintMatch( words, sizeof(words)/sizeof(words[0]), CheckLowercase );
    
    printf( "정수 - " );
    scanf( "%d", &g_length );   
    fflush( stdin );
    printf( "[길이  ] " );    PrintMatch( words, sizeof(words)/sizeof(words[0]), CheckLength );
    
    printf( "문자 - " );
    scanf( "%c", &g_letter );
    printf( "[검색  ] " );    PrintMatch( words, sizeof(words)/sizeof(words[0]), CheckFind );
}

void PrintMatch( char words[][32], int size, int (* check)(const char*) )
{
    int i;
    for( i = 0; i < size; i++ )
    {
        if( check(words[i]) != 0 )
            printf( "%s ", words[i] );
    }
    printf( "\n" );
}

int CheckOk( const char* str )
{
    return 1;
}

int CheckUppercase( const char* str )
{
    while( *str )
    {
        if( isupper(*str++) == 0 )
            return 0;
    }

    return 1;
}

int CheckLowercase( const char* str )
{
    while( *str )
    {
        if( islower(*str++) == 0 )
            return 0;
    }

    return 1;
}

int CheckLength( const char* str )
{
    return strlen(str) == g_length;
}

int CheckFind( const char* str )
{
    char letter = toupper( g_letter );

    while( *str )
    {
        if( toupper(*str++) == letter )
            return 1;
    }

    return 0;
}

/*
[출력결과]
[전체  ] Hello TEST Newyork21 1492 memory MiNoR AccesS
[대문자] TEST
[소문자] memory
정수 - 5
[길이  ] Hello MiNoR
문자 - E
[검색  ] Hello TEST Newyork21 memory AccesS
*/
