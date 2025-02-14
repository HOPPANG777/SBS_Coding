#include <stdio.h>
#include "example_2_1_1_Rect.h"
#pragma warning(disable:4996)

void main(void)
{
    struct RECT rect;
    InitRect( &rect );

    rect.Input( &rect );
    rect.Output( &rect );
}

/*
[출력결과]
[영역 입력]
x : 11
y : 33
x : 22
y : 77
[영역 출력]
x : 11
y : 33
x : 22
y : 77
*/
