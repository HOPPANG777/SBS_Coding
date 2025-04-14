/*============================================================================================
	그외 ...

		컨트롤 리소스 생성..
		( 메뉴, 아이콘, 커서, 단축키.. )

			-	리소스 생성..
				-	[ 솔루션 탐색기 ]
					> [ 프로젝트 명 ]
					> [ 마우스 우클릭 ]
					> [ 팝업 메뉴 ] 노출..
					->	[ 추가 ]
						> [ 리소스 ] 선택..
					->	[ 리소스 추가 팝업 ] 노출..
					->	선택..

			-	LoadCursor, LoadIcon,
				LoadAccelerators,
				MAKEINTRESOURCE 등을
				활용하여 생성..

			-	이하 소스 참고..

============================================================================================*/
#include <windows.h>
#include "resource.h"
//============================================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("Menu");
//============================================================================================
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
	//	커서 추가..
	WndClass.hCursor=LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1));
	//	아이콘 추가..
	WndClass.hIcon=LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	
	//	메뉴 추가..
	WndClass.lpszMenuName=MAKEINTRESOURCE(IDR_MENU1);

	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		  CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		  NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);

	//	액셀러레이터 추가..(단축키)
	HACCEL hAccel;	
	hAccel=LoadAccelerators(hInstance,MAKEINTRESOURCE(IDR_ACCELERATOR1));	

	while (GetMessage(&Message,NULL,0,0))
	{
		//	엑셀러레이터 번역기.
		if (!TranslateAccelerator(hWnd,hAccel,&Message))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}
	return (int)Message.wParam;

}//	int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
//============================================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch (iMessage)
	{
		case WM_COMMAND:

			switch (LOWORD(wParam))
			{
				case ID_FILE_MENU1:
					MessageBox(hWnd,TEXT("첫 번째 메뉴를 선택했습니다."),TEXT("Menu Demo"),MB_OK);
					break;
				case ID_FILE_MENU2:
					MessageBox(hWnd,TEXT("두 번째 메뉴를 선택했습니다."),TEXT("Menu Demo"),MB_OK);
					break;
				case ID_FILE_EXIT:
					DestroyWindow(hWnd);
					break;
			}
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

	}//	switch (iMessage)

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//============================================================================================