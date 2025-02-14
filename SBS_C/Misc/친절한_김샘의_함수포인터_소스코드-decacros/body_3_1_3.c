#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

void First(void);
void Second(void);
void Third(void);

void main(void)
{
    printf( "----> atexit() 이전 <----\n" );

    atexit( First  );
    atexit( Second );
    atexit( Third  );

    printf( "----> atexit() 이후 <----\n" );
}

void First(void)
{
    printf( "첫 번째 함수 : First()\n" );
}

void Second(void)
{
    printf( "두 번째 함수 : Second()\n" );
}

void Third(void)
{
    printf( "세 번째 함수 : Third()\n" );
}

/*
[출력 결과]
----> atexit() 이전 <----
----> atexit() 이후 <----
세 번째 함수 : Third()
두 번째 함수 : Second()
첫 번째 함수 : First()
*/
