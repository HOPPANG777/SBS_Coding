#include <stdio.h> 
#pragma warning(disable:4996)

void PrintBinary( unsigned char lights );
unsigned char SwitchOn( unsigned char lights, int pos );
unsigned char SwitchOff( unsigned char lights, int pos );
unsigned char SwitchReverse( unsigned char lights, int pos );

unsigned char (* GetFuncPointer(int menu))(unsigned char, int);

void main(void) 
{
    unsigned char lights = 0x3C;        // 0011 1100
    int menu, pos;

    while( 1 )
    {
        printf( "[0] 종료 [1] 출력 [2] 켜기 [3] 끄기 [4] 반전 - " );
        scanf( "%d", &menu );

        if( menu < 0 || menu > 4 )
            continue;

        if( menu == 0 )
            break;

        if( menu != 1 )
        {
            printf( "위치 : " );
            scanf( "%d", &pos );

            lights = GetFuncPointer(menu)(lights, pos);
        }

        printf( "결과 : " );
        PrintBinary( lights );
    }
}

unsigned char (* GetFuncPointer(int menu))(unsigned char, int)
{
    static unsigned char (* FuncArray[])(unsigned char, int) = { SwitchOn, SwitchOff, SwitchReverse };

    return FuncArray[menu-2];
}

void PrintBinary( unsigned char lights )
{
    unsigned char mask = 0x80;

    while( mask > 0 )
    {
        printf( "%d", (lights&mask) == mask );
        mask >>= 1;
    }
    printf( "\n" );
}

unsigned char SwitchOn( unsigned char lights, int pos )
{
    return lights | (1<<pos);
}

unsigned char SwitchOff( unsigned char lights, int pos )
{
    return lights & ~(1<<pos);
}

unsigned char SwitchReverse( unsigned char lights, int pos )
{
    return lights ^ (1<<pos);
}

/*
[출력결과]
[0] 종료 [1] 출력 [2] 켜기 [3] 끄기 [4] 반전 - 1
결과 : 00111100
[0] 종료 [1] 출력 [2] 켜기 [3] 끄기 [4] 반전 - 2
위치 : 7
결과 : 10111100
[0] 종료 [1] 출력 [2] 켜기 [3] 끄기 [4] 반전 - 2
위치 : 6
결과 : 11111100
[0] 종료 [1] 출력 [2] 켜기 [3] 끄기 [4] 반전 - 3
위치 : 7
결과 : 01111100
[0] 종료 [1] 출력 [2] 켜기 [3] 끄기 [4] 반전 - 3
위치 : 6
결과 : 00111100
[0] 종료 [1] 출력 [2] 켜기 [3] 끄기 [4] 반전 - 4
위치 : 7
결과 : 10111100
[0] 종료 [1] 출력 [2] 켜기 [3] 끄기 [4] 반전 - 4
위치 : 7
결과 : 00111100
[0] 종료 [1] 출력 [2] 켜기 [3] 끄기 [4] 반전 - 0
*/
