#include "CComboBox.h"

void CComboBox::Add(TCHAR** ppszItems, int count)
{
	for (int i = 0; i < count; i++)
		SendMessage(_hWnd, CB_ADDSTRING, 0, (LPARAM)ppszItems[i]);
}