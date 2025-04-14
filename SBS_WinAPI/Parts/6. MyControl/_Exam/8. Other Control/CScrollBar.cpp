//===========================================================
#include "CScrollBar.h"
//===========================================================
bool CScrollBar::Create(int nPos, int nMinPos, int nMaxPos)
{
	bool bRes = CControlBase::Create();

	if (bRes)
	{
		SetValueRange(nMinPos, nMaxPos);
		SetValue(nPos);
	}

	return bRes;
}
//---------------------------------------
void CScrollBar::GetValueString( TCHAR* pszTmp ) { wsprintf(pszTmp, "%d", GetValue()); }
//---------------------------------------
int CScrollBar::OnHScroll(WPARAM wParam)
{
	int tmpPos = _nCurValue ;

	switch (LOWORD(wParam))
	{
	case SB_LINELEFT:
		tmpPos = max(0, tmpPos - 1);
		break;
	case SB_LINERIGHT:
		tmpPos = min(255, tmpPos + 1);
		break;
	case SB_PAGELEFT:
		tmpPos = max(0, tmpPos - 10);
		break;
	case SB_PAGERIGHT:
		tmpPos = min(255, tmpPos + 10);
		break;
	case SB_THUMBTRACK:
		tmpPos = HIWORD(wParam);
		break;
	}

	_nCurValue = tmpPos;

	SetScrollPos(_hWnd, SB_CTL, _nCurValue, TRUE);

	return _nCurValue;

}//	int CScrollBar::OnHScroll(WPARAM wParam)
//===========================================================