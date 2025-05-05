//====================================================================
#include <windows.h>
//====================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("Key");
//====================================================================
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
		//	1-3-2. TranslateMessage 확인..
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
//====================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	/*
		WM_CHAR에서 wParam / lParam 용도..

		-	wParam..

			-	어떤 문자키를 눌렀는지 확인..


		-	lParam..

			-	Alt 키 등 특수키가
				눌려졌는지 체크..

			-	비트 연산으로 체크..

			-	메시지 별로 다름..

	*/
	HDC hdc;
	PAINTSTRUCT ps;
	static TCHAR str[256];
	int len;

	switch (iMessage) {
		//	1-3-1. TranslateMessage 확인..
		//*
	case WM_KEYDOWN:

		//	디버깅 모드로 실행하는 경우
		//	출력창에 로그 출력.
		OutputDebugString("--- keydown\n");
		return 0;


	case WM_KEYUP:
		OutputDebugString("+++ keyup\n");
		return 0;
		//*/


	case WM_CHAR:
		OutputDebugString("*** char\n");
//*
		len = lstrlen(str);
		str[len] = (TCHAR)wParam;
		str[len+1] = 0;
		InvalidateRect(hWnd,NULL,TRUE);
//*/
/*		2. 무효 영역..
		if ((TCHAR)wParam == ' ')	//	스페이스 버튼..
			str[0] = 0;	//	0 다음 char은 무시..
		else {
			len = lstrlen(str);
			str[len] = (TCHAR)wParam;
			str[len+1] = 0;
		}
		//InvalidateRect(hWnd,NULL, TRUE);	//	출력 버퍼 지우고 갱신..
	    InvalidateRect(hWnd,NULL, FALSE);	//	출력 버퍼 안지우고 갱신..
//*/
		return 0;


	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		TextOut(hdc,100,100,str,lstrlen(str));
		EndPaint(hWnd,&ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//====================================================================