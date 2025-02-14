#include <stdio.h>
#include <string.h>
#include "example_2_1_1_Rect.h"
#pragma warning(disable:4996)

void InputRect( struct RECT* pRect );
void OutputRect( const struct RECT* pRect );

void InitRect( struct RECT* pRect )
{
    memset( pRect, 0, sizeof(struct RECT) );

    InitPoint( &pRect->pt1 );
    InitPoint( &pRect->pt2 );

    pRect->Input  = InputRect;
    pRect->Output = OutputRect;
}

void InputRect( struct RECT* pRect )
{
    printf( "[영역 입력]\n" );
    pRect->pt1.Input( &pRect->pt1 );
    pRect->pt2.Input( &pRect->pt2 );
}

void OutputRect( const struct RECT* pRect )
{
    printf( "[영역 출력]\n" );
    pRect->pt1.Output( &pRect->pt1 );
    pRect->pt2.Output( &pRect->pt2 );
}
