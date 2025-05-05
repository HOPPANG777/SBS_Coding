//=====================================================================
#include <windows.h>
//=====================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("KeyDown");
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
//=====================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x=100;
	static int y=100;

	switch (iMessage) {
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_LEFT:
			x-=8;
			break;
		case VK_RIGHT:
			x+=8;
			break;
		case VK_UP:
			y-=8;
			break;
		case VK_DOWN:
			y+=8;
			break;
		}
		InvalidateRect(hWnd,NULL,TRUE);
		//InvalidateRect(hWnd,NULL,FALSE);
		return 0;

	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		TextOut(hdc,x,y,TEXT("A"),1);
		EndPaint(hWnd,&ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//=====================================================================
/*
    Q > 프로그램 시작시 "Bad"라는 글자와
		"A"라는 글자가 임의의 위치에 등장..

        키보드 방향 키로 "A"를 움직이게 하다가
		"Bad"와 충돌하면 "Bad"의 위치가
		임의의 위치로 변경되도록 합니다..

        팁) 
            1.  임의의 위치 설정기능..
				( 랜덤 기능 )
                
				-   srand, rand 함수를 검색..



            2.  충돌체크 알고리즘..

                -   aabb 충돌 방식 검색..
*/
//=====================================================================