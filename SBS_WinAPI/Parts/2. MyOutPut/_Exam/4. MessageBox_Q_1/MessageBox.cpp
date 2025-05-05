#include <windows.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("Jackie MessageBox");

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
//====================================================================
int g_appleCount = 100;
//====================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	TCHAR str[128];
	switch (iMessage) {
		
	case WM_CREATE:

		//	윈도우 타이틀 문자열 읽기.		
		GetWindowText(hWnd, str, strlen(str));
		MessageBox(hWnd, str, TEXT("WM_CREATE"), MB_OK);

		return 0;


	case WM_LBUTTONDOWN:
		
		//	윈도우 타이틀 문자열 설정.
		wsprintf(str, TEXT("사과 갯수 = %d"), g_appleCount);
		SetWindowText(hWnd, str);

		//	메시지 박스 리턴값 확인.
		if (MessageBox(hWnd, TEXT("사과를 좋아하시나요?"), TEXT("좋아하는 과일은 뭔가요??"), MB_YESNO) == IDYES)
		{
			MessageBox(hWnd, TEXT("네 그렇습니다!!"), TEXT("^^"), MB_OK);
			if (MessageBox(hWnd, TEXT("사과 하나줄까요???"), TEXT("내 사과를 받아주세요~"), MB_YESNO) == IDYES)
			{
				wsprintf(str, TEXT("사과 갯수 = %d"), ++g_appleCount);
				SetWindowText(hWnd, str);
			}			
		}
		else
			MessageBox(hWnd, TEXT("아닌데요!!"), TEXT("T.T"), MB_OK);
		return 0;


	case WM_RBUTTONDOWN:
		if (MessageBox(hWnd, TEXT("사과 하나만 주세요~~"), TEXT("깁 미 앺플~~~"), MB_YESNO) == IDYES)
		{
			wsprintf(str, TEXT("사과 갯수 = %d"), --g_appleCount);
			SetWindowText(hWnd, str);
		}
		return 0;


	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	}
	return( DefWindowProc( hWnd,iMessage,wParam,lParam ) );
}
//====================================================================