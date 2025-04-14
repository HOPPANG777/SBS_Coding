//==============================================================
#include <windows.h>
#include <stdlib.h>
#include <time.h>
//==============================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("KeyDown");
//==============================================================
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
//==============================================================
void SetRandomPosition( int *pX, int *pY )
{
	srand(time(0));
	*pX = rand();
	*pY = rand();
}
//==============================================================
const int WIDTH = 10;
const int HEIGHT = 10;
//==============================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int x=100;
	static int y=100;

	static int targetX = 0;
	static int targetY = 0;

	switch ( iMessage )
	{
		case WM_CREATE:
		{
			SetRandomPosition(&targetX, &targetY);
			targetX = targetX % 500 + 50;
			targetY = targetY % 500 + 50;

			SetRandomPosition(&x, &y);
			x = x % 1200 + 50;
			y = y % 600 + 50;

			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;

		case WM_KEYDOWN:
		{
			switch (wParam) {
			case VK_LEFT:
				x -= 8;
				if (x < 0)
					x = 0;
				break;
			case VK_RIGHT:
				x += 8;
				if (x > 1400)
					x = 1400;
				break;
			case VK_UP:
				y -= 8;
				if (y < 0)
					y = 0;
				break;
			case VK_DOWN:
				y += 8;
				if (y > 700)
					y = 700;
				break;
			}

			//	참고	:	https://gameculture.tistory.com/33
			//				https://hoidu.tistory.com/entry/%EC%B6%A9%EB%8F%8C%EC%B2%98%EB%A6%AC-AABB%EC%99%80-AABB-%EC%B6%A9%EB%8F%8C-%EC%B2%98%EB%A6%AC
			//	충돌 체크..
			//	-	AABB..
			//		( Axis Aligned Bounding Box.. )
			bool isCollision = false;
			if ((targetX - WIDTH < x && x < targetX + WIDTH) &&
				(targetY - HEIGHT < y && y < targetY + HEIGHT))
				isCollision = true;

			if (isCollision)
			{
				SetRandomPosition( &targetX, &targetY);
				targetX = targetX % 500 + 50;
				targetY = targetY % 500 + 50;
			}

			InvalidateRect(hWnd, NULL, TRUE);
			//InvalidateRect(hWnd,NULL,FALSE);

		}//	case WM_KEYDOWN:
		return 0;
		

		case WM_PAINT:
			hdc=BeginPaint(hWnd,&ps);
			SetTextAlign(hdc, TA_CENTER);
			TextOut(hdc, x, y, TEXT("A"),1);
			TextOut(hdc, targetX, targetY, TEXT("Bad"), 3);
			EndPaint(hWnd,&ps);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

	}//	switch ( iMessage )
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//==============================================================