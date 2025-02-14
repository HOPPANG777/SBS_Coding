#include <stdio.h>
#include <string.h>
#include "body_2_1_2_Chair.h" 
#pragma warning(disable:4996)

void InputChair( CHAIR* pChair );
void OutputChair( const CHAIR* pChair );

void InitChair( CHAIR* pChair )
{
    memset( pChair, 0, sizeof(CHAIR) );

    pChair->Input  = InputChair;
    pChair->Output = OutputChair;
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
