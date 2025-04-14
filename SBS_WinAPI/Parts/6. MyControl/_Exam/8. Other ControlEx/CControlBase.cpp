//===========================================================
#include "CControlBase.h"
#include <windows.h>
//===========================================================
CControlBase::CControlBase(HWND parentHwnd, TCHAR* pszClassName, TCHAR* pszName, HINSTANCE hInst, HMENU id, int posX, int posY, int width, int height, int winStyle)
{
	_hWndParent = parentHwnd;
	strcpy(_szClassName, pszClassName);
	_pszName = pszName;
	_hInst = hInst;
	_ID = id;
	_posX = posX;
	_posY = posY;
	_width = width;
	_height = height;
	_windowStyle = WS_CHILD | WS_VISIBLE | winStyle;

}//	CControlBase::CControlBase( HWND parentHwnd, TCHAR* pszName, ... )
//-------------------------------------------
bool CControlBase::Create()
{
	_hWnd = CreateWindow(
		_szClassName,
		_pszName,
		_windowStyle,
		_posX, _posY, _width, _height,
		_hWndParent,
		(HMENU)_ID,
		_hInst,
		NULL);

	if (_hWnd == NULL)
		return false;

	return true;

}//	bool CControlBase::Create()
//===========================================================