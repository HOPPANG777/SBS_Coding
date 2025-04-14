//===========================================================
#pragma once
//===========================================================
#include <windows.h>
//===========================================================
class CControlBase
{
protected:
	HWND _hWnd;
	HWND _hWndParent;
	TCHAR _szClassName[128];
	TCHAR* _pszName;
	HINSTANCE _hInst;
	HMENU _ID;
	int _posX, _posY;
	int _width, _height;
	int _windowStyle;

public :
	CControlBase(HWND parentHwnd, TCHAR* pszClassName, TCHAR* pszName, HINSTANCE hInst, HMENU id, int posX, int posY, int width, int height, int winStyle);
	virtual bool Create();
	virtual int SendMsg(int Msg, WPARAM wParam, LPARAM lParam) { return SendMessage(_hWnd, Msg, wParam, lParam); }
	HWND GetHwnd()	{ return _hWnd; }
	int GetID()		{ return (int)_ID; }
};
//===========================================================