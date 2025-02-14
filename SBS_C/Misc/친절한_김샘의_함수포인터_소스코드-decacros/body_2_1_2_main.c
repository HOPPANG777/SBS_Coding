#include "body_2_1_2_Chair.h" 

void main(void)
{
    CHAIR chair;
    InitChair( &chair );

    chair.Input( &chair );
    chair.Output( &chair );
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
