//===================================================
#include "CObject.h"
//===================================================
CObject* g_pObject;
//===================================================
//===================================================
bool CObject::InitInstance(const TCHAR *pszName, HINSTANCE hInstance, PSTR szCmdLine, int iCmdShow)
{
	WNDCLASS	wndClass;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = pszName;

	RegisterClass(&wndClass);

	_hWnd = CreateWindow(pszName,
		pszName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (_hWnd != NULL)
	{
		ShowWindow(_hWnd, iCmdShow);
		return true;
	}

	return false;

}//	bool CObject::InitInstance(HINSTANCE hInstance, PSTR szCmdLine,	int iCmdShow)
//===================================================
void CObject::Run()
{
	while (GetMessage(&_msg, NULL, 0, 0))
	{
		TranslateMessage(&_msg);
		DispatchMessage(&_msg);

	}//	while (GetMessage(&msg, NULL, 0, 0))

}//	void CObject::Run()
//===================================================
WPARAM CObject::ExitInstance() { return _msg.wParam; }
//===================================================