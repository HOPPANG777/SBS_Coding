#include <stdio.h>

void First(void);
int  Second( int n );

void main(void)
{
    void (* func1)(void);
    int  (* func2)(int);

    func1 = (void (*)(void)) Second;
    printf( "반환: %d\n", ((int (*)(int)) func1)(123) );

    func2 = (int (*)(int)) First;
    ((void (*)(void)) func2)();
}

void First(void)
{
    printf( "First() 호출\n" );
}

int Second( int n )
{
    printf( "Second() 호출\n" );

    return n*2;
}

/*
[출력결과]
Second() 호출
반환: 246
First() 호출
*/
