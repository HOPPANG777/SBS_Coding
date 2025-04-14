#pragma once
#include "CControlBase.h"
class CListBox :
	public CControlBase
{
public:
	CListBox(HWND parentHwnd, TCHAR* pszName, HINSTANCE hInst, HMENU id, int posX, int posY, int width, int height, int winStyle = WS_BORDER | LBS_NOTIFY)
		: CControlBase(parentHwnd, TEXT("listbox"), pszName, hInst, id, posX, posY, width, height, winStyle) { }
	
	void Add(TCHAR** ppszItems, int count);
	int GetCurSel() { return SendMessage(_hWnd, LB_GETCURSEL, 0, 0); }
	int SetCurSel(int idx) { return SendMessage(_hWnd, LB_SETCURSEL, idx, 0); }
};