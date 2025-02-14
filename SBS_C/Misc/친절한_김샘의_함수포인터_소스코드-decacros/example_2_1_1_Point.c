#include <stdio.h>
#include <string.h>
#include "example_2_1_1_Point.h"
#pragma warning(disable:4996)

void InputPoint( struct POINT* ppt );
void OutputPoint( const struct POINT* ppt );

void InitPoint( struct POINT* ppt )
{
    memset( ppt, 0, sizeof(struct POINT) );

    ppt->Input  = InputPoint;
    ppt->Output = OutputPoint;
}

void InputPoint( struct POINT* ppt )
{
    printf( "x : " );    scanf( "%d", &ppt->x );
    printf( "y : " );    scanf( "%d", &ppt->y );
}

void OutputPoint( const struct POINT* ppt )
{
    printf( "x : %d\n", ppt->x );
    printf( "y : %d\n", ppt->y );
}
