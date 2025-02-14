#include <stdio.h>

struct Test
{
    void (Test::* func)(void);

    Test(void) : func(&Test::Print) {}

    void Print(void)
    {
        printf( "멤버 함수 호출 성공\n" );
    }

    void Proxy(void)
    {
        (this->*func)();
    }
};

void main(void)
{
    Test test;

    test.Proxy();
    (test.*test.func)();
}

/*
[출력결과]
멤버 함수 호출 성공
멤버 함수 호출 성공
*/
