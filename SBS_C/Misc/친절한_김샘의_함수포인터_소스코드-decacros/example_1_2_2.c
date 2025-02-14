#include <stdio.h>
#include <string.h>
#pragma warning(disable:4996)

void main(void)
{
    char buf1[512] = "", buf2[128] = "";
    char menu[32];
    char* (* func)(char*, const char*) = NULL;

    while( 1 )
    {
        printf( "Quit strcpy strcat - " );
        scanf( "%s", menu );

        if( strcmp(menu, "Quit") == 0 )
            break;

        if( strcmp(menu, "strcpy") == 0 )
        {
            func = strcpy;
        }
        else if( strcmp(menu, "strcat") == 0 )
        {
            func = strcat;
        }

        printf( "buf1 : %s\n", buf1 );
        printf( "buf2 : " );
        scanf( "%s", buf2 );

        func( buf1, buf2 );
        printf( "결과 : %s\n\n", buf1 );
    }
}

/*
[출력결과]
Quit strcpy strcat - strcpy
buf1 :
buf2 : Hello
결과: Hello

Quit strcpy strcat - strcat
buf1 : Hello
buf2 : 여러분
결과: Hello여러분

Quit strcpy strcat - Quit
*/