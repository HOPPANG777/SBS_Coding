#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("GraphOut");

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

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	//	선의 색상 핸들.
	HPEN curPen;
	HPEN curPen2;
	HPEN curPen3;

	//	도형 색상.
	HBRUSH curBrush;
	HBRUSH curBrush2;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);

		//	점 출력.
		//	RGB(Red, Green, Blue)
		//	각각 0 ~ 255		
		SetPixel(hdc, 10, 10, RGB(255, 0, 0));
		
		// 선 색상 변경..
		curPen = CreatePen(PS_DOT, 1, RGB(0, 0, 255));	//	펜 생성.
		HGDIOBJ oldPen = SelectObject(hdc, curPen);		//	생성된 펜을 dc에 전달하면 기존 펜 리소스 데이터가 반환됨.
		//	선 긋기.
		MoveToEx(hdc,50,50,NULL);
		LineTo(hdc,300,90);


		//	브러시 색 변경..
		curBrush = CreateSolidBrush(RGB(255, 255, 0));
		HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, curBrush);
		//	펜 변경..
		curPen2 = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
		SelectObject(hdc, curPen2);
		//	직사각형
		Rectangle(hdc,50,100,200,180);
		
		//	브러시 변경..
		curBrush2 = CreateSolidBrush(RGB(255, 0, 255));
		SelectObject(hdc, curBrush2);
		//	펜 변경..
		curPen3 = CreatePen(PS_SOLID, 3, RGB(0, 0, 255));
		SelectObject(hdc, curPen3);

		//	타원.
		Ellipse(hdc,220,100,400,200);
				
		SelectObject(hdc, oldPen);	//	기존 펜 리소스를 dc에 반환.
		DeleteObject(curPen);		//	생성한 펜 리소스 제거.
		DeleteObject(curPen2);		//	생성한 펜 리소스 제거.
		DeleteObject(curPen3);		//	생성한 펜 리소스 제거.

		SelectObject(hdc, oldBrush);	//	기존 브러시 리소스를 dc에 반환.
		DeleteObject(curBrush);			//	생성한 브러시 리소스 제거.
		DeleteObject(curBrush2);		//	생성한 브러시 리소스 제거.

		EndPaint(hWnd,&ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
