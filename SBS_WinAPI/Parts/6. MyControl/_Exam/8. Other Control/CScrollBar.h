//===========================================================
#pragma once
//===========================================================
#include "CControlBase.h"
//===========================================================
class CScrollBar : public CControlBase
{
	int _nCurValue;
public :
	CScrollBar(HWND parentHwnd, TCHAR* pszName, HINSTANCE hInst, int id, int posX, int posY, int width, int height, int winStyle = SBS_HORZ)
		: CControlBase(parentHwnd, TEXT("scrollbar"), pszName, hInst, id, posX, posY, width, height, winStyle)	{ }
	virtual bool Create() { return CControlBase::Create(); }
	bool Create(int nPos, int nMinPos, int nMaxPos);
	BOOL SetValueRange(int nMinPos, int nMaxPos)	{ return SetScrollRange(_hWnd, SB_CTL, nMinPos, nMaxPos, TRUE); }
	BOOL SetValue(int nPos)							{ _nCurValue = nPos;  return SetScrollPos(_hWnd, SB_CTL, nPos, TRUE); }	
	int GetValue()									{ return _nCurValue; }
	void GetValueString(TCHAR* pszTmp);
	int OnHScroll(WPARAM wParam);
};
//===========================================================