#include <windows.h>
#include "resource.h"
#include "CBitMap.h"
#include "CDrawManager.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("FieldScroll");

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
		CW_USEDEFAULT,CW_USEDEFAULT,1000,480,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	
	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
//------------------------------
int scrX = 0;
int bx=100,by=100,tx=-1,ty;
//------------------------------
CBitMap *g_pBGBitmap;
CBitMap *g_pBabyBitmap;
CBitMap *g_pToiletBitmap;
CDrawManager *g_pDrawManager;
//------------------------------
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	int destWidth;
	HDC hMemDC;	
	
	switch (iMessage) {
	case WM_CREATE:
		g_pBGBitmap = new CBitMap(hWnd, g_hInst);
		g_pBGBitmap->Load(IDB_FIELD);

		g_pBabyBitmap = new CBitMap(hWnd, g_hInst);
		g_pBabyBitmap->Load(IDB_BABY);

		g_pToiletBitmap = new CBitMap(hWnd, g_hInst);
		g_pToiletBitmap->Load(IDB_TOILET);

		g_pDrawManager = new CDrawManager(1000, 480);
		hWndMain=hWnd;
		SetTimer(hWnd,1,50,NULL);
		return 0;
		
	case WM_TIMER:
		scrX += 30;
		if (scrX >2048) scrX =0;

		if (tx!= -1) {
			tx+=10;
			if (tx > 1000) {
				tx=-1;
			}
		}
		InvalidateRect(hWnd,NULL,FALSE);
		return 0;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			bx-=5;
			break;
		case VK_RIGHT:
			bx+=5;
			break;
		case VK_UP:
			by-=5;
			break;
		case VK_DOWN:
			by+=5;
			break;
		case VK_SPACE:
			if (tx == -1) {
				tx=bx+100;
				ty=by;
			}
			break;
		}
		return 0;
	case WM_PAINT:
		hMemDC = g_pDrawManager->BeginDraw(hWnd);

		//	배경 애니 적용.
		destWidth = min(2048 - scrX, 1000);
		g_pBGBitmap->DrawForDBuff(hMemDC, 0, 0, destWidth, 480, scrX, 0);
		if (destWidth < 1000)
			g_pBGBitmap->DrawForDBuff(hMemDC, destWidth, 0, 1000 - destWidth, 480, 0, 0);

		// 아기 그림
		g_pBabyBitmap->TransDrawForDBuff(hMemDC, bx, by, RGB(255, 0, 255));
		
		// 총알 그림
		if (tx != -1)
			g_pToiletBitmap->TransDrawForDBuff(hMemDC, tx, ty, RGB(255, 0, 255));

		g_pDrawManager->EndDraw(hWnd);
		return 0;

	case WM_DESTROY:

		delete g_pBGBitmap;
		delete g_pBabyBitmap;
		delete g_pToiletBitmap;
		delete g_pDrawManager;

		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
