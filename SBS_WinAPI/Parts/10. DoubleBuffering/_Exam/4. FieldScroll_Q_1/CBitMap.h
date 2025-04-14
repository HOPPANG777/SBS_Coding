//==========================================================
#pragma once
//==========================================================
#include <windows.h>
//==========================================================
class CBitMap
{
	HWND _hWnd;
	HINSTANCE _hInst;
	HBITMAP _hBitMap;
	BITMAP _bm;

public:
	CBitMap(HWND hWnd, HINSTANCE hInst);
	~CBitMap();
	bool Load( int id );
	void Draw( HDC hdc, int posX, int posY );

	void DrawForDBuff(HDC hMemDC, int posX, int posY, int width, int height, int srcX, int srcY);
	void TransDrawForDBuff(HDC hMemDC, int posX, int posY, COLORREF transColor );
	
	BOOL DeleteBitmap();
	HBITMAP GetHBitMap() { return _hBitMap; }
};
//==========================================================