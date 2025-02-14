#include <stdio.h>
#pragma warning(disable:4996)

struct Add
{
    int operator()( int n1, int n2 )
    {
        return n1+n2;
    }
};

int TestAdd( Add& func, int n1, int n2 );

void main(void)
{
    int n1 = 3, n2 = 5;
    printf( "%d + %d = %d\n", n1, n2, TestAdd(Add(), n1, n2) );
}

int TestAdd( Add& func, int n1, int n2 )
{
    return func(n1, n2);
}

/*
[출력결과]
3 + 5 = 8
*/
