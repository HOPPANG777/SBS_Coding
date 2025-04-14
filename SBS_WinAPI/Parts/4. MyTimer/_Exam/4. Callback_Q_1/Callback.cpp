//=====================================================================================
#include <windows.h>
#include "CRaceManager.h"
//=====================================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("Callback");
//=====================================================================================
int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
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
	
	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
//=====================================================================================
CRaceManager g_RaceManager(1000);
//=====================================================================================
void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	//	현재 경과된 시간 계산.
	//	GetTickCount()
	//	-	시스템이 시작한 시점부터
	//		이 함수를 호출한 시점까지
	//		흘러간 시간을 1/1000초 단위의
	//		시간으로 반환..
	static DWORD time = GetTickCount();
	DWORD elapsedTime = dwTime - time;
	time = GetTickCount();

	/*	경과시간을 디버깅용으로 알기위해 출력.
	TCHAR szTmp[100] = "";
	wsprintf(szTmp, "%d\n", elapsedTime);
	OutputDebugString(szTmp);
	//*/

	HDC hdc = GetDC(hWnd);	

	//	실제 레이싱을 관리..
	g_RaceManager.DoRace(hdc, elapsedTime);

	ReleaseDC(hWnd, hdc);
}
//=====================================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;

	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd,1,100,TimerProc);
		return 0;
		
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//=====================================================================================