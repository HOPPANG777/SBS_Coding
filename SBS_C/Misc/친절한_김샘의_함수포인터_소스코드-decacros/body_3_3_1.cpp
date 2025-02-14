#include <stdio.h>
#pragma warning(disable:4996)

struct PlusFunction
{
    void operator()(void)
    {
        printf( "operator() 호출\n" );
    }
};

void TestPlusFunction( PlusFunction& func );

void main(void)
{
    TestPlusFunction( PlusFunction() );
}

void TestPlusFunction( PlusFunction& func )
{
    func();
}

/*
[출력결과]
operator() 호출
*/
