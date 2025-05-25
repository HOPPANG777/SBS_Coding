//==================================================================
#include <windows.h>
//==================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MemBit");
//==================================================================
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
//==================================================================
//* 1 - 화면에 직접 그리기..
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int i;
	HBRUSH MyBrush, OldBrush;
	int x,y;
	
	switch (iMessage)
	{
		case WM_ERASEBKGND:
			break;//	return 0;	break;

			//	[ return 0 ] 으로 처리..
			// 
			//	ㄴ	[ DefWindowProc ]에서
			//		[ WM_ERASEBKGND ]에 대한 기본 처리인
			//		화면 지우기를 하지 않음..
			// 
			//		ㄴ	이전 이미지가 남아있게 됨..

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			for ( i = 0; i < 5000; i++ )
			{
				MyBrush = CreateSolidBrush(
							RGB( 
								rand()%256,
								rand()%256,
								rand()%256 )
							);

				OldBrush = ( HBRUSH )SelectObject( hdc, MyBrush );

				x = rand()%720;
				y = rand()%520;

				Ellipse(
					hdc,
					x, y,
					x + rand() % 50 + 30,
					y + rand() % 50 + 30
				);

				SelectObject(hdc,OldBrush);
				DeleteObject(MyBrush);

			}//	for ( i = 0; i < 5000; i++ )

			EndPaint(hWnd, &ps);
			return 0;
	
		case WM_LBUTTONDOWN:
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;
	
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//*/
//==================================================================
/* 2 - 더블 버퍼링 적용..

// 가상 메모리 비트맵..
HBITMAP g_hMemBit;			

void DrawBitmap(HDC hdc,int x,int y,HBITMAP hBit)
{
	if (hBit == NULL)
		return;

	HDC MemDC;
	HBITMAP OldBitmap;
	int bx,by;
	BITMAP bit;

	//	화면 DC와 호환되는 DC 생성..
	MemDC = CreateCompatibleDC( hdc );
	OldBitmap = ( HBITMAP )SelectObject( MemDC, hBit );

	GetObject( hBit, sizeof( BITMAP ), &bit );
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(
		hdc,
		x, y, bx, by,
		MemDC, 0, 0,
		SRCCOPY
	);

	SelectObject( MemDC, OldBitmap );
	DeleteDC( MemDC );
}

// 가상 메모리 비트맵에 그림을 미리 그림..
void Ready(HWND hWnd)
{
	HBRUSH MyBrush, OldBrush;
	int x, y;

	//	0.	DC 얻기..
	HDC hdc = GetDC( hWnd );
		
	//	1.	화면 DC와 호환되는 DC 생성..
	HDC MemDC = CreateCompatibleDC( hdc );

	// 이미 비트맵이 만들어져 있으면 제거..
	if (g_hMemBit)
		DeleteObject(g_hMemBit);

	//	2.	오프 스크린 비트맵 생성..
	g_hMemBit = CreateCompatibleBitmap( hdc, 800, 600 );

	//	3.	메모리 DC에 오프 스크린 비트맵을 선택..
	//		-	메모리 DC가 가상 화면이 됨..
	HBITMAP hOldBmp = ( HBITMAP )SelectObject( MemDC, g_hMemBit );

	//	메모리 비트맵을 흰색으로 채운 후
	//	무작위로 타원 5000개를 그림..
	PatBlt(MemDC,0,0,800,600,WHITENESS);
	
	for ( int i = 0; i < 5000; i++ )
	{
		//	랜덤 색으로 브러시 선택..
		MyBrush = CreateSolidBrush(
						RGB( rand() % 256,
							 rand() % 256,
							 rand() % 256 )
				);
		OldBrush = ( HBRUSH )SelectObject( MemDC, MyBrush );

		//	랜덤 위치와 색으로
		//	원 그리기..
		x = rand() % 720;
		y = rand() % 520;
		Ellipse(
			MemDC,
			x, y,
			x + rand() % 50 + 30,
			y + rand() % 50 + 30
		);
		SelectObject(MemDC,OldBrush);
		DeleteObject(MyBrush);

	}//	for ( int i = 0; i < 5000; i++ )

	//	마무리..
	SelectObject(MemDC, hOldBmp);
	DeleteDC(MemDC);
	ReleaseDC(hWnd, hdc);
}
//==================================================================
// 가상 화면에 그리기..
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	switch ( iMessage )
	{
		case WM_PAINT:
			hdc=BeginPaint(hWnd, &ps);
			DrawBitmap(hdc,0,0, g_hMemBit);
			EndPaint(hWnd, &ps);
			return 0;


		case WM_LBUTTONDOWN:
			Ready(hWnd);
			InvalidateRect(hWnd, NULL, FALSE);
			return 0;


		case WM_DESTROY:
			if (g_hMemBit)
				DeleteObject(g_hMemBit);
			PostQuitMessage(0);
			return 0;

	}//	switch ( iMessage )

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//*/
//==================================================================