#include <stdio.h>

typedef void (* mfcfunc_t)(void);

#define BEGIN_MESSAGE_MAP(array) mfcfunc_t array[] = {
#define END_MESSAGE_MAP };
#define MESSAGE_HANDLER(func) ((mfcfunc_t) func),

void OnSize( int cx, int cy );
void OnPaint(void);
void OnLButtonDown( int x, int y, int flag );

void main(void)
{
    BEGIN_MESSAGE_MAP(FuncArray)
        MESSAGE_HANDLER(OnSize)
        MESSAGE_HANDLER(OnPaint)
        MESSAGE_HANDLER(OnLButtonDown)
    END_MESSAGE_MAP

    ((void (*)(int, int)) FuncArray[0])( 100, 200 );
    FuncArray[1]();
    ((void (*)(int, int, int)) FuncArray[2])( 30, 120, 0 );
}

void OnSize( int cx, int cy )
{
    printf( "OnSize - 윈도우 크기 변경[%d, %d]\n", cx, cy );
}

void OnPaint(void)
{
    printf( "OnPaint - 윈도우 다시 그리기\n" );
}

void OnLButtonDown( int x, int y, int flag )
{
    printf( "OnLButtonDown - 마우스 클릭[%d, %d]\n", x, y );
}

/*
[출력결과]
OnSize - 윈도우 크기 변경[100, 200]
OnPaint - 윈도우 다시 그리기
OnLButtonDown - 마우스 클릭[30, 120]
*/
