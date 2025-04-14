//===========================================================
#pragma once
//===========================================================
#include "CControlBase.h"
#include <list>
using namespace std;
//===========================================================
enum { SCROLLBAR, EDIT, BUTTON,	LISTBOX, COMBOBOX, STATIC };
//---------------------------------
typedef list<CControlBase*>		CONTROLLIST;
typedef CONTROLLIST::iterator	CONTROLLISTITER;
//---------------------------------
class CControlFactory
{
	HWND _hWnd;
	HINSTANCE _hInst;
	CONTROLLIST _ControlList;

public:
	CControlFactory(HWND hWnd, HINSTANCE hInst)
	{
		_hWnd = hWnd;
		_hInst = hInst;
	}
	~CControlFactory();
	CControlBase* Create(int ControlType, int id, TCHAR* pszName, int posX, int posY, int width, int height);

};
//===========================================================