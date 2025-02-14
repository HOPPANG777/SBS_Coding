#include <stdio.h>
#pragma warning(disable:4996)

typedef struct _CHAIR
{
    char model[32];
    int  price;
    char size;      // Small, Medium, Big
}
CHAIR;

void InputChair( CHAIR* pChair );
void OutputChair( const CHAIR* pChair );

void main(void) 
{
    CHAIR chair;

    InputChair( &chair );
    OutputChair( &chair );
}

void InputChair( CHAIR* pChair )
{
    printf( "[입력]\n" );

    printf( "모델 : " );
    scanf( "%s", pChair->model );

    printf( "가격 : " );
    scanf( "%d", &pChair->price );    fflush( stdin );

    printf( "크기 : " );
    scanf( "%c", &pChair->size );
}

void OutputChair( const CHAIR* pChair )
{
    printf( "[출력]\n" );

    printf( "모델 : %s\n", pChair->model );
    printf( "가격 : %d\n", pChair->price );
    printf( "크기 : %c\n", pChair->size  );
}

/*
[출력결과]
[입력]
모델 : 듀오백
가격 : 120000
크기 : M
[출력]
모델 : 듀오백
가격 : 120000
크기 : M
*/