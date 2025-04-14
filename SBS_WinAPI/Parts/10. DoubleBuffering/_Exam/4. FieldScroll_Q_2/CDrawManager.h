//===============================================================
//	비트맵을 출력하기 위한 오프스크린 비트맵 생성 및 그리기 처리..
//===============================================================
#pragma once
//===============================================================
#include <windows.h>
//===============================================================
class CDrawManager
{
	HDC _hdc;
	HDC _hMemDC;
	PAINTSTRUCT _ps;
	HBITMAP _hOffScrBitmap, _hOldBitmap;
	int _offScrWidth, _offScrHeight;

public:
	CDrawManager(int offScrWidth, int offScrHeight);
	HDC BeginDraw( HWND hWnd );
	void EndDraw( HWND hWnd);
};
//===============================================================