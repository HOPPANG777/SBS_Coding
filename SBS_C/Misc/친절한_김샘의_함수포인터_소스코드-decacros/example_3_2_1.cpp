#include <stdio.h>


struct Base
{
    virtual void operator()(void) = 0;
};

struct Hello : public Base
{
    void operator()(void)
    {
        printf( "%-13s\n", "Hello()" );
    }
};

struct PrintNumber : public Base
{
    int n;

    PrintNumber( int _n ) : n(_n) {}

    void operator()(void)
    {
        printf( "%-13s [%d]\n", "PrintNumber()", n );
    }
};

struct PrintArray : public Base
{
    int* array;
    int size;

    PrintArray( int* _array, int _size ) : array(_array), size(_size) {}

    void operator()(void)
    {
        printf( "%-13s [", "PrintArray()" );

        for( int i = 0; i < size; i++ )
            printf( "%d ", array[i] );
        printf( "\b]\n" );
    }
};

void ProxyFunction( Base& base );

void main(void)
{
    int array[10] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 };

    printf( "[매개 변수1]\n");
    ProxyFunction( Hello() );
    ProxyFunction( PrintNumber(99) );
    ProxyFunction( PrintArray(array, 10) );

    // **************************** //

    printf( "\n[배열]\n" );
    Base* FuncArray[] = { new Hello, new PrintNumber(99), new PrintArray(array, 10) };
    
    FuncArray[0]->operator()();
    FuncArray[1]->operator()();
    FuncArray[2]->operator()();

    // **************************** //

    printf( "\n[매개 변수2]\n");
    for( int i = 0; i < 3; i++ )
    {
        ProxyFunction( *FuncArray[i] );
        delete FuncArray[i];
    }
}

void ProxyFunction( Base& base )
{
    base();
}

/*
[출력결과]
[매개 변수1]
Hello()
PrintNumber() [99]
PrintArray()  [1 3 5 7 9 2 4 6 8 0]

[배열]
Hello()
PrintNumber() [99]
PrintArray()  [1 3 5 7 9 2 4 6 8 0]

[매개 변수2]
Hello()
PrintNumber() [99]
PrintArray()  [1 3 5 7 9 2 4 6 8 0]
*/
