#include <stdio.h>
#pragma warning(disable:4996)

struct AddPlus
{
    int n1, n2;

    AddPlus( int _n1, int _n2 ) : n1(_n1), n2(_n2) {}

    int operator()(void)
    {
        return n1+n2;
    }
};

int TestAddPlus( AddPlus& func );

void main(void)
{
    int n1 = 3, n2 = 5;
    AddPlus add( n1, n2 );

    printf( "%d + %d = %d\n", n1, n2, TestAddPlus(add) );
}

int TestAddPlus( AddPlus& func )
{
    return func();
}

/*
[출력결과]
3 + 5 = 8
*/
