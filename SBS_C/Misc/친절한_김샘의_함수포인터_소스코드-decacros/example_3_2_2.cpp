#include <stdio.h>
#include <ctype.h>
#include <string.h>
#pragma warning(disable:4996)

struct Base
{
    virtual bool operator()( const char* str )
    {
        return true;
    }
};

struct Alphabet : public Base
{
    int (* CheckFunc)(int);

    Alphabet( int (* _CheckFunc)(int) ) : CheckFunc(_CheckFunc) {}

    bool operator()( const char* str )
    {
        while( *str )
        {
            if( CheckFunc(*str++) == 0 )
                return false;
        }

        return true;
    }
};

struct Length : public Base
{
    int g_length;

    Length( int _length ) : g_length(_length) {}

    bool operator()( const char* str )
    {
        return strlen(str) == g_length;
    }
};

struct Find : public Base
{
    char g_letter;

    Find( char _letter ) : g_letter(_letter) {}

    bool operator()( const char* str )
    {
        char letter = toupper( g_letter );

        while( *str )
        {
            if( toupper(*str++) == letter )
                return true;
        }

        return false;
    }
};

void PrintMatch( char words[][32], int size, Base& base );

void main(void)
{
    char words[][32] = { "Hello", "TEST", "Newyork21", "1492", "memory", "MiNoR", "AccesS" };

    printf( "[전체  ] " );    PrintMatch( words, sizeof(words)/sizeof(words[0]), Base() );

    printf( "[대문자] " );    PrintMatch( words, sizeof(words)/sizeof(words[0]), Alphabet(isupper) );
    printf( "[소문자] " );    PrintMatch( words, sizeof(words)/sizeof(words[0]), Alphabet(islower) );
    
    int length;
    printf( "정수 - " );
    scanf( "%d", &length );   
    fflush( stdin );
    printf( "[길이  ] " );    PrintMatch( words, sizeof(words)/sizeof(words[0]), Length(length) );
    
    char letter;
    printf( "문자 - " );
    scanf( "%c", &letter );
    printf( "[검색  ] " );    PrintMatch( words, sizeof(words)/sizeof(words[0]), Find(letter) );
}

void PrintMatch( char words[][32], int size, Base& base )
{
    for( int i = 0; i < size; i++ )
    {
        if( base(words[i]) == true )
            printf( "%s ", words[i] );
    }
    printf( "\n" );
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
