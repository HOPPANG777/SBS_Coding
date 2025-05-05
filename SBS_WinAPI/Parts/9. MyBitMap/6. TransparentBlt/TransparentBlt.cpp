//===============================================================================
#include <windows.h>
//===============================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("TransparentBlt");
//===============================================================================
int APIENTRY WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdParam,
	int nCmdShow )
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
//===============================================================================
#include "resource.h"
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HDC MemDC;
	HBITMAP MyBitmap, OldBitmap;
	int i;
	BITMAP bit;
	int bx,by;

	switch (iMessage) {
	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		for (i=0;i<500;i+=10) {
			MoveToEx(hdc,0,i,NULL);
			LineTo(hdc,800,i);
		}
		MemDC=CreateCompatibleDC(hdc);
		MyBitmap=LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		OldBitmap=(HBITMAP)SelectObject(MemDC, MyBitmap);

		GetObject(MyBitmap, sizeof(BITMAP), &bit);
		bx=bit.bmWidth;
		by=bit.bmHeight;

		/*
			TransparentBlt( hdc,0,0,bx,by,MemDC,0,0,bx,by,RGB(255,0,0) );
			-	[ StretchBlt ]와 유사하나
				마지막 인자는 ROP모드가 아닌
				투명색으로 사용할 마스크 색상..

			-	분홍색을 많이 사용함..

			-	확대 축소는 가능하나
				미러링은 불가..
		*/
		//	일반적인 사용.
		TransparentBlt(hdc,0,0,bx,by,MemDC,0,0,bx,by,RGB(255,0,0));

		//	축소..
		//TransparentBlt(hdc, 0, 0, bx*0.5f, by*0.5f, MemDC, 0, 0, bx, by, RGB(255, 0, 0));

		//	확대..
		//	TransparentBlt(hdc, 0, 0, bx*2.f, by*2.f, MemDC, 0, 0, bx, by, RGB(255, 0, 0));

		//	미러링..
		//	TransparentBlt(hdc, 0, 0, -bx, -by, MemDC, 0, 0, bx, by, RGB(255, 0, 0));

		SelectObject(MemDC,OldBitmap);
		DeleteObject(MyBitmap);
		DeleteDC(MemDC);
		EndPaint(hWnd, &ps);
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
/*
	---------------------------------------
	참고..
	
		예전에는 복잡한 그래픽 처리까지
		CPU가 전담..

		[ Direct X ]나 [ OPENGL ]등의
		그래픽 랜더러 프로그램이 등장하여
		그래픽 관련 업무를 [ GPU ]에 넘김으로써
		[ CPU ]의 부담이 많이 줄었음..

	---------------------------------------
*/
//===============================================================================