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

public:
	CBitMap( HWND hWnd );
	~CBitMap();
	bool Load( HINSTANCE hInst, int id );
	void Draw( HDC hdc, int posX, int posY );
	BOOL DeleteBitmap();
};
//==========================================================