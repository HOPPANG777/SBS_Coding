//=====================================================================
#include <windows.h>
#include "CRCPManager.h"
//=====================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MyButton");
//=====================================================================
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	
	while (GetMessage(&Message,NULL,0,0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;

}//	int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
//=====================================================================
CRCPManager g_RCPManager;
//=====================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static HWND _replayBttn;

	switch (iMessage)
	{
		case WM_CREATE:
			CreateWindow(	TEXT("button"),
							TEXT("가위"),
							WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
							100,200,100,25,
							hWnd, (HMENU)0, g_hInst, NULL);

			CreateWindow(	TEXT("button"),
							TEXT("바위"),
							WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
							220, 200,100,25,
							hWnd, (HMENU)1, g_hInst, NULL);

			CreateWindow(	TEXT("button"),
							TEXT("보"),
							WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
							340, 200, 100, 25,
							hWnd, (HMENU)2, g_hInst, NULL);

			_replayBttn = CreateWindow(TEXT("button"),
				TEXT("리플레이"),
				WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
				220, 250, 100, 25,
				hWnd, (HMENU)3, g_hInst, NULL);
			
			ShowWindow(_replayBttn, SW_HIDE);

			return 0;

		case WM_COMMAND://	컨트롤의 통지 메시지 전달시 호출되는 메시지.
			switch (LOWORD(wParam))//	컨트롤의 ID
			{
			case 3:
				g_RCPManager.Reset();
				ShowWindow(_replayBttn, SW_HIDE);
				InvalidateRect(hWnd, NULL, TRUE);
				break;
			
			default :
				g_RCPManager.ProcessRCP(hWnd, LOWORD(wParam));
				break;
			}
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			g_RCPManager.ShowTitle(hdc);
			if (g_RCPManager.IsFinish())
			{
				g_RCPManager.ShowResult(hdc);
				ShowWindow(_replayBttn, SW_SHOW);
			}
			EndPaint(hWnd, &ps);
		}
		return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

	}//	switch (iMessage)
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//=====================================================================