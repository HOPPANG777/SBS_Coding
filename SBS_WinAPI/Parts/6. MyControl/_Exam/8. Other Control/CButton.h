//===========================================================
#pragma once
//===========================================================
#include "CControlBase.h"
//===========================================================
class CButton :
	public CControlBase
{
public :
	CButton(HWND parentHwnd, TCHAR* pszName, HINSTANCE hInst, int id, int posX, int posY, int width, int height, int winStyle = BS_DEFPUSHBUTTON)
		: CControlBase(parentHwnd, TEXT("button"), pszName, hInst, id, posX, posY, width, height, winStyle) { }
};
//===========================================================