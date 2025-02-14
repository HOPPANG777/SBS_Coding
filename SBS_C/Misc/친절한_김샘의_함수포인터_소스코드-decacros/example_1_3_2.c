#include <stdio.h> 
#include <string.h> 
#pragma warning(disable:4996)

int SelectMenu(void);

void main(void) 
{
    char str[512] = "Hello";
    char* (* FuncArray[])(char*) = { NULL , gets, (char* (*)(char*)) puts, strupr, strrev };
    int select;

    while( 1 )
    {
        select = SelectMenu();

        if( select == 0 )
            break;

        FuncArray[select]( str );
    }
}

int SelectMenu(void)
{
    static char* menu[] = { "Quit", "Input", "Print", "Uppercase", "Reverse" };
    char input[32];
    int  i = -1;

    while( 1 )
    {
        printf( "[메뉴] Quit Input Print Uppercase Reverse - " );
        scanf( "%s", input );
        fflush( stdin );

        for( i = 0; i < sizeof(menu)/sizeof(menu[0]); i++ )
        {
            if( strcmp(input, menu[i]) == 0 )
                return i;
        }
    }

    return -1;
}

/*
[출력결과]
[메뉴] Quit Input Print Uppercase Reverse - Print
Hello
[메뉴] Quit Input Print Uppercase Reverse - Input
Black
[메뉴] Quit Input Print Uppercase Reverse - Print
Black
[메뉴] Quit Input Print Uppercase Reverse - Uppercase
[메뉴] Quit Input Print Uppercase Reverse - Print
BLACK
[메뉴] Quit Input Print Uppercase Reverse - Reverse
[메뉴] Quit Input Print Uppercase Reverse - Print
KCALB
[메뉴] Quit Input Print Uppercase Reverse - Quit
*/
