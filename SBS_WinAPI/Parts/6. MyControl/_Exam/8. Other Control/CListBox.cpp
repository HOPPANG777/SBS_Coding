//==================================================================
#include "CListBox.h"
//==================================================================
void CListBox::Add(TCHAR** ppszItems, int count)
{
	for (int i = 0; i < count; i++)
		SendMessage(_hWnd, LB_ADDSTRING, 0, (LPARAM)ppszItems[i]);
}
//==================================================================