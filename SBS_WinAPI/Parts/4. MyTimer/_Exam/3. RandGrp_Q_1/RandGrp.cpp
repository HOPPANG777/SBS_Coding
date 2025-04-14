//==============================================================================
#include <windows.h>
//==============================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("RandGrp");
//==============================================================================
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
//==============================================================================
typedef struct SPixelInfo
{
    float _pos[2];
    float _color[3];
};
//==============================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
    static SPixelInfo pixelInfos[10000];

	switch (iMessage) {
	case WM_CREATE:
        memset(pixelInfos, 0, sizeof(pixelInfos));
		SetTimer(hWnd,1,1,NULL);
		return 0;
		
	case WM_TIMER:
        for( int cur = 0; cur < 10000; cur++)
        {
            pixelInfos[cur]._pos[0] = rand() % 500;
            pixelInfos[cur]._pos[1] = rand() % 400;

            pixelInfos[cur]._color[0] = rand() % 256;
            pixelInfos[cur]._color[1] = rand() % 256;
            pixelInfos[cur]._color[2] = rand() % 256;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		return 0;

	case WM_LBUTTONDOWN:
		hdc=GetDC(hWnd);
		Ellipse(hdc,LOWORD(lParam)-10,HIWORD(lParam)-10,
			LOWORD(lParam)+10,HIWORD(lParam)+10);
		ReleaseDC(hWnd, hdc);
		return 0;

	case WM_PAINT:
		hdc=BeginPaint(hWnd, &ps);
		for (int cur = 0; cur < 10000; cur++) {
			SetPixel( 
				hdc,
				pixelInfos[cur]._pos[0],
				pixelInfos[cur]._pos[1],
				RGB(pixelInfos[cur]._color[0],
					pixelInfos[cur]._color[1],
					pixelInfos[cur]._color[2]));
		}
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//==============================================================================