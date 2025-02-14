#include <stdio.h>

void First(void);
int Second( int n );

void main(void)
{
    void (* func1)(void);
    int  (* func2)(int);

    func1 = First;
    func1();

    func1 = (void (*)(void)) Second;
    func1();

    func2 = (int (*)(int)) First;
    func2( 123 );

    func2 = Second;
    func2( 456 );
}

void First(void)
{
    printf( "First() 호출\n" );
}

int Second( int n )
{
    printf( "Second 호출\n" );

    return n*2;
}

/*
[출력결과]
First() 호출
Second 호출
First() 호출
Second 호출
*/
