//================================================================
#pragma once
//================================================================
#include "CControlBase.h"
//================================================================
class CEdit :
	public CControlBase
{
public:
	CEdit(HWND parentHwnd, TCHAR* pszName, HINSTANCE hInst, HMENU id, int posX, int posY, int width, int height, int winStyle = WS_BORDER | ES_RIGHT )
		: CControlBase(parentHwnd, TEXT("edit"), pszName, hInst, id, posX, posY, width, height, winStyle) { }

	void GetText(TCHAR* pszTmp, int length) { GetWindowText(_hWnd, pszTmp, length); }
	void SetText(TCHAR *pszText)			{ SetWindowText(_hWnd, pszText); }
};
//================================================================