//=====================================================================
#include <windows.h>
//=====================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("Mouse");
//=====================================================================
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
	//WndClass.style = CS_HREDRAW | CS_VREDRAW;
	//	3. 더블 클릭..
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
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

}//	int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ..
//=====================================================================
//	5.	wParam, lParam 참고..
//=====================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	static int x;
	static int y;
	static BOOL bNowDraw = FALSE;

	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		bNowDraw = TRUE;
		return 0;


	case WM_MOUSEMOVE:
		if (bNowDraw == TRUE)
		{
			hdc = GetDC(hWnd);

			MoveToEx(hdc, x, y, NULL);

			x = LOWORD(lParam);
			y = HIWORD(lParam);

			LineTo(hdc, x, y);

			ReleaseDC(hWnd, hdc);
		}
		return 0;


	case WM_LBUTTONUP:
		bNowDraw = FALSE;
		return 0;


	case WM_LBUTTONDBLCLK:
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}//	switch (iMessage)

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)}
//==============================================================
/*
    Q > 간단한 그림판을 만듭니다..
        
        -   1,2,3 버튼..
            -   선, 사각형, 원..

        -   shift + 1,2,3 버튼..
            -   펜 색( Red, Green, Blue )

        -   Ctrl + 1,2,3 버튼..
            -   브러시 색( Red, Green, Blue )


        팁 )    shift, ctrl 키가 동시에 눌렸는지 확인하기 위해
                [ GetAsyncKeyState ] 함수를 활용..
*/
//==============================================================