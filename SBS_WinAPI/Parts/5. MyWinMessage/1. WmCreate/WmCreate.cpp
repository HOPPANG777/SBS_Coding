/*=============================================================================

	------------------------
	-	윈도우 관리 메시지..
	------------------------
	
		------------------
		1.	생성 및 파괴..
		------------------

			---------------
			-	WM_CREATE..
			---------------

				-	윈도우가 생성될 때
					호출되는 메시지..

				-	[ CreateWindow ]가
					성공하면 바로 보내짐..

				-	각종 초기화를 하기에 적합..


			----------------
			-	WM_DESTROY..
			----------------

				-	윈도우가 파괴되기전에
					호출되는 메시지..

				-	[ Alt + F4 ], 
					[ 시스템 버튼( X버튼 ) ]을
					누르면 호출됨..

				-	종료 처리에 적합..




		-------------------------
		2.	초기화 및 종료 처리의
			또 다른 방법..
		-------------------------

				-	[ CreateWindow ] 함수 이후에
					초기화..


				-	메시지 루프를 빠져 나온 후
					종료처리..
					( GetMessage(), TranslateMessage(),
					  DispatchMessage() )

					-	return 처리 바로 직전..

					-	권장하는 방법은 아님..

						-	[ CreateWindow ]이
							꼭 성공한다는 보장이 없음..

						-	실패 시에도 별도의
							종료처리를 해줘야함..

=============================================================================*/
#include <windows.h>
//============================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("WmCreate");
TCHAR *mem;
//============================================================================
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
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

	hWnd = CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		  CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,
		  NULL,(HMENU)NULL,hInstance,NULL);

	//	WM_CREATE 호출 시점.
	//	-	CreateWindow 성공 바로 직후!!
	/*
	if (hWnd != NULL)
		mem = (TCHAR*)malloc(1000);
	//*/

	ShowWindow(hWnd,nCmdShow);

	
	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	
	//	WM_DESTROY 호출 시점..
	//	-	메시지 루프 빠져나온 직후!!
	//free(mem);

	return (int)Message.wParam;

}//	int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
//============================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch (iMessage) {

		case WM_CREATE: 
			mem=(TCHAR *)malloc(1000);
			return 0;

		case WM_DESTROY:
			free(mem);
			PostQuitMessage(0);
			return 0;

	}//	switch (iMessage)
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//============================================================================//