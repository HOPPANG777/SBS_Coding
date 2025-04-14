//======================================================================================
#include <windows.h>
//======================================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("GraphOut");
//======================================================================================
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
//======================================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	//	선의 데이터를 관리할 핸들..
	HPEN curPen;

	//	도형 색을 관리할 핸들..
	HBRUSH curBrush;

	switch (iMessage)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:

			//	DC 핸들 얻기..
			hdc = BeginPaint(hWnd,&ps);

			//	점 출력..
			//	-	RGB( Red, Green, Blue )..
			//	-	각각 0 ~ 255..
			SetPixel(hdc, 10, 10, RGB(255, 0, 0));
		
			//	선 색상 설정..
			
			//	펜 생성..
			curPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

			//	생성된 펜을 dc에 전달..
			//	-	기존의 펜 리소스 
			//		데이터가 반환 됨..
			HGDIOBJ oldPen = SelectObject(hdc, curPen);

			//	선 긋기..
			//	선의 시작점 설정..
			MoveToEx(hdc,50,50,NULL);
			//	선의 종료점 설정..
			LineTo(hdc,300,90);


			//	면의 색상 설정..
			//	브러시 생성..
			curBrush = CreateSolidBrush(RGB(0, 255, 255));

			//	생성된 브러시를
			//	dc에 전달..
			//	-	기존의 브러시 리소스
			//		데이터가 반환됨..
			HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, curBrush);

			//	직사각형..
			Rectangle(hdc,50,100,200,180);
		
			//	타원..
			Ellipse(hdc,220,100,400,200);
				
			//	기존 펜 리소스를 dc에 반환..
			SelectObject(hdc, oldPen);
			//	생성한 펜 리소스 제거..
			DeleteObject(curPen);		

			//	기존 브러시 리소스를 dc에 반환..
			SelectObject(hdc, oldBrush);
			//	생성한 브러시 리소스 제거..
			DeleteObject(curBrush);

			//	DC 핸들 반환..
			EndPaint(hWnd,&ps);

			return 0;

	}//	switch (iMessage)

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//======================================================================================
/*
    Q >
		다음 도형을 그리세요..

        파란색 점선,
		녹색 테두리의 노란색 브러시 사각형,
        파란색 굵은 테두리의 분홍색 타원..
*/
//======================================================================================