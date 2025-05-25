//==========================================================
#include <windows.h>
#include "CBitMap.h"
//==========================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("DrawBitmap");
//==========================================================
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
	  ,LPSTR lpszCmdParam,int nCmdShow)
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
	
	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
//---------------------------------------------------------------------------
#include "resource.h"
//---------------------------------------------------------------------------
CBitMap* g_pBitMap1;
CBitMap* g_pBitMap2;
//---------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
		//-------------------------------------
		case WM_CREATE:

			//	비트맵 로딩..
			g_pBitMap1 = new CBitMap(hWnd);
			g_pBitMap2 = new CBitMap(hWnd);

			if (!g_pBitMap1->Load(g_hInst, IDB_BITMAP_AVG3))
			{
				MessageBox(hWnd, "비트맵 로딩 실패", "에러", MB_OK);
				return 0;
			}

			if (!g_pBitMap2->Load(g_hInst, IDB_BITMAP_AVG3_2))
			{
				MessageBox(hWnd, "비트맵 로딩 실패", "에러", MB_OK);
				return 0;
			}
			return 0;


		//-------------------------------------
		case WM_PAINT:

			hdc = BeginPaint(hWnd, &ps);
		
			//	비트맵 그리기..
			g_pBitMap1->Draw(hdc, 10, 10);

			//	비트맵 그리기..
			g_pBitMap2->Draw(hdc, 30, 10);

			EndPaint(hWnd, &ps);
			return 0;


		//-------------------------------------
		case WM_DESTROY:
		
			//	메모리 제거..
			delete g_pBitMap1;
			g_pBitMap1 = NULL;

			delete g_pBitMap2;
			g_pBitMap2 = NULL;

			PostQuitMessage(0);
			return 0;


	}//	switch (iMessage)


	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//==========================================================