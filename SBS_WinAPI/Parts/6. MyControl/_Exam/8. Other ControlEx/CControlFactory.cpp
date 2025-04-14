//===========================================================
#include "CControlFactory.h"
#include "CScrollBar.h"
#include "CEdit.h"
#include "CButton.h"
#include "CListBox.h"
#include "CComboBox.h"
#include "CControlBase.h"
#include "CStatic.h"
//===========================================================
CControlBase* CControlFactory::Create(
	int ControlType, HMENU id, TCHAR* pszName,
	int posX, int posY, int width, int height)
{
	CControlBase* pControl = NULL;

	switch (ControlType)
	{
	case SCROLLBAR:
		pControl = new CScrollBar(_hWnd, pszName, _hInst, id, posX, posY, width, height);
		break;

	case EDIT:
		pControl = new CEdit(_hWnd, pszName, _hInst, id, posX, posY, width, height);
		break;

	case BUTTON:
		pControl = new CButton(_hWnd, pszName, _hInst, id, posX, posY, width, height);
		break;

	case LISTBOX:
		pControl = new CListBox(_hWnd, pszName, _hInst, id, posX, posY, width, height);
		break;

	case COMBOBOX:
		pControl = new CComboBox(_hWnd, pszName, _hInst, id, posX, posY, width, height);
		break;

	case STATIC:
		pControl = new CStatic(_hWnd, pszName, _hInst, id, posX, posY, width, height);
		break;
	}

	_ControlList.push_back(pControl);
	return pControl;
}

CControlFactory::~CControlFactory()
{
	CONTROLLISTITER iterBegin = _ControlList.begin();
	CONTROLLISTITER iterEnd = _ControlList.end();
	CONTROLLISTITER iterCur;

	for(iterCur = iterBegin; iterCur != iterEnd; ++iterCur )
	{
		CControlBase* pTmp = (*iterCur);
		delete pTmp;
		pTmp = NULL;
	}
}
//===========================================================