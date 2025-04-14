#pragma once
#include "CControlBase.h"
class CStatic :
	public CControlBase
{
public:
	CStatic(HWND parentHwnd, TCHAR* pszName, HINSTANCE hInst, HMENU id, int posX, int posY, int width, int height, int winStyle = 0)
		: CControlBase(parentHwnd, TEXT("static"), pszName, hInst, id, posX, posY, width, height, winStyle) { }
};