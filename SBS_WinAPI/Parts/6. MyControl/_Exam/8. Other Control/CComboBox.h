//===========================================================
#pragma once
//===========================================================
#include "CControlBase.h"
//===========================================================
class CComboBox :
	public CControlBase
{
	public:
		CComboBox(HWND parentHwnd, TCHAR* pszName, HINSTANCE hInst, int id, int posX, int posY, int width, int height, int winStyle = CBS_DROPDOWN)
			: CControlBase(parentHwnd, TEXT("combobox"), pszName, hInst, id, posX, posY, width, height, winStyle) { }

		void Add(TCHAR** ppszItems, int count);
		int GetCurSel()			{ return SendMsg( CB_GETCURSEL, 0, 0); }
		int SetCurSel(int idx)	{ return SendMsg( CB_SETCURSEL, idx, 0); }
};
//===========================================================