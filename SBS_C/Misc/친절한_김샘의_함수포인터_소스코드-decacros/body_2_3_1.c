#include <stdio.h>
#pragma warning(disable:4996)

void Hello(void);
void ProxyHello( void (* func)(void) );

void main(void) 
{
    int i;
    for( i = 0; i < 5; i++ )
        ProxyHello( Hello );
}

void Hello(void)
{
    printf( "Hello() 호출\n" );
}

void ProxyHello( void (* func)(void) )
{
    func();
}

/*
[출력결과]
Hello() 호출
Hello() 호출
Hello() 호출
Hello() 호출
Hello() 호출
*/
