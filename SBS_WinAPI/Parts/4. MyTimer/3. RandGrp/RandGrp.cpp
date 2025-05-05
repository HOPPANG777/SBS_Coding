//=========================================================================
#include <windows.h>
//=========================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("RandGrp");
//=========================================================================
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
//=========================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	int i;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
		/*	케이스 - 1..
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			for (;;) {
				SetPixel(hdc, rand() % 500, rand() % 400,
					RGB(rand() % 256, rand() % 256, rand() % 256));
			}
			EndPaint(hWnd, &ps);
			return 0;
			//*/



		/*	케이스 - 2..
		case WM_CREATE:
			SetTimer(hWnd,1,1,NULL);
			return 0;
		
		case WM_TIMER:
			hdc=GetDC(hWnd);
			for (i=0;i<10000;i++)
			{
				SetPixel(hdc,rand()%500, rand()%400,
					RGB(rand()%256,rand()%256,rand()%256));
			}
			ReleaseDC(hWnd, hdc);
			return 0;
			//*/



		case WM_LBUTTONDOWN:
			hdc=GetDC(hWnd);
			Ellipse(hdc,LOWORD(lParam)-10,HIWORD(lParam)-10,
				LOWORD(lParam)+10,HIWORD(lParam)+10);
			ReleaseDC(hWnd, hdc);
			return 0;

		case WM_DESTROY:
			KillTimer(hWnd, 1);
			PostQuitMessage(0);
			return 0;

	}//	switch (iMessage)

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//=============================================================
/*
    Q > 위 프로그램을 WM_PAINT에서도
		정상 작동되도록 수정합니다.
        
		WM_TIMER - 데이터 세팅..
		WM_PAINT - 데이터 출력..

        팁)  [ 픽셀에 대한 정보( 위치, 색 ) ]를 [ 구조체 ]로 만듬..
			 [ 구조체 ]를 [ 배열 ]로 관리..

             WM_TIMER - [ 구조체 배열 ] 데이터 설정..
			 WM_PAINT - [ 구조체 배열 ] 출력..
*/
//=============================================================