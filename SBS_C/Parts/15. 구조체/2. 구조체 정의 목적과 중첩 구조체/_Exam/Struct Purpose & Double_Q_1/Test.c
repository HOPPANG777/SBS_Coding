//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
typedef struct
{
	int _nPosX;
	int _nPosY;

}sPoint;

typedef struct
{
	sPoint _lt;
	sPoint _rb;

}sRectangle;

void ShowArea(sRectangle* pRect)
{
	int width = pRect->_rb._nPosX - pRect->_lt._nPosX;
	int height = pRect->_rb._nPosY - pRect->_lt._nPosY;

	printf("Area : %d\n", width * height);
}

void ShowPtInfo(sRectangle* pRect)
{
	printf("[L, T] : [ %d, %d ]\n", pRect->_lt._nPosX, pRect->_lt._nPosY);
	printf("[L, B] : [ %d, %d ]\n", pRect->_lt._nPosX, pRect->_rb._nPosY);
	printf("[R, B] : [ %d, %d ]\n", pRect->_rb._nPosX, pRect->_rb._nPosY);
	printf("[R, T] : [ %d, %d ]\n", pRect->_rb._nPosX, pRect->_lt._nPosY);
}
void main()
{
	//	초기화 1)
	sRectangle tmpRect = { 0,0, 100,100 };
	//	초기화 2)
	//sRectangle tmpRect = { {0,0}, {100,100} };
	
	/*	정의.
	sRectangle tmpRect;
	tmpRect._lt._nPosX = 0;
	tmpRect._lt._nPosY = 0;
	tmpRect._rb._nPosX = 100;
	tmpRect._rb._nPosY = 100;
	//*/
		
	ShowPtInfo( &tmpRect );
	ShowArea( &tmpRect );
}
//======================================================//