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