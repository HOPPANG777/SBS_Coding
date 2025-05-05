//===========================================================================
#include <windows.h>
//===========================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("MyTimer");
//===========================================================================
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
		  ,LPSTR lpszCmdParam,int nCmdShow)
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
//===========================================================================
int g_countTime = 5;
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR sTime[128];
	static RECT rt={100,100,400,120};

    switch (iMessage)
	{
		case WM_CREATE:
			SetTimer(hWnd, 1, 1000, NULL);
			SendMessage(hWnd, WM_TIMER, 1, 0);
			return 0;


		case WM_TIMER:
			if (g_countTime >= 0)
			{
				wsprintf(sTime, TEXT("남은시간 %d초."), g_countTime--);
				//	클라이언트 영역 전체 갱신..
				InvalidateRect(hWnd, NULL, TRUE);
			}
			else
			{
				KillTimer(hWnd, 1);
				MessageBox(hWnd, TEXT("뻥!!!!!!!!!!!!"), TEXT("폭탄"), MB_OK);
				SendMessage(hWnd, WM_DESTROY, 0, 0);
			}
			return 0;


		case WM_PAINT:
			hdc=BeginPaint(hWnd,&ps);
			TextOut(hdc,100,100,sTime,lstrlen(sTime));
			EndPaint(hWnd,&ps);
			return 0;


		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

	}//	switch (iMessage)

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//===========================================================================