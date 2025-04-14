/*===============================================================================================
	------------
	10.	스태틱..
	------------

		-	용도..
			-	문자열 보여주기..
			-	컨트롤의 용도를
				설명해주는 역할..


		-	생성하기
				-	윈도우 클래스
					-	"static"

				-	============================================
					스타일				|	기능..
					============================================
					SS_LEFT				|	왼쪽 정렬..
										|	자동 개행..
					--------------------------------------------
					SS_LEFTNOWORDWRAP	|	왼쪽 정렬..
										|	자동 개행 안됨..
					--------------------------------------------
					SS_CENTER			|	중앙 정렬..
										|	자동 개행..
					--------------------------------------------
					SS_RIGHT			|	오른쪽 정렬..
										|	자동 개행..
					--------------------------------------------
					SS_SIMPLE			|	단순 문자열..
										|	자동개행 안됨..
					--------------------------------------------
					SS_WHITEFRAME		|	윈도우의 배경색으로
										|	그려지는 사각형..
					--------------------------------------------
					SS_WHITERECT		|	윈도우의 배경색으로
										|	그려지는 속이 채워진 사각형..
					--------------------------------------------
					SS_BLACKFRAME		|	화면 배경색으로
										|	그려지는 사각형..
					--------------------------------------------
					SS_BLACKRECT		|	화면 배경색으로
										|	그려지는
										|	속이 채워진 사각형..
					--------------------------------------------
					SS_GRAYFRAME		|	윈도우 프레임 색상으로
										|	그려지는 사각형..
					--------------------------------------------
					SS_GRAYRECT			|	윈도우 프레임 색상으로
										|	그려지는 속이 채워진 사각형..
					--------------------------------------------
					SS_ICON				|	대화상자내에서
										|	아이콘 출력..
					--------------------------------------------
					SS_NOPREFIX			|	[ & ]문자를
										|	단축키 지정에
										|	사용하지 않고
										|	그대로 출력..
					============================================


		-	TextOut와 차이점..
		
			TextOut..
			-	단순 문자열..
			-	언제든지 지워질수 있음..
			-	WM_PAINT에서
				계속 복구해야함..

			스태틱..
			-	스스로 메시지를
				처리할 수 있는 윈도우..
				( WM_PAINT등 기본 메시지 자체 처리.. )
			-	색상, 글꼴 등
				운영체제의
				세팅이 바뀔 경우
				스스로 대처..


===============================================================================================*/
#include <windows.h>
//===============================================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MyStatic");
//===============================================================================================
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
	WndClass.hbrBackground=(HBRUSH)(WHITE_BRUSH);//(COLOR_BTNFACE+1);
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

}//	int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
//===============================================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	static HWND hStatic;

	switch (iMessage)
	{
		case WM_CREATE:
			hStatic = CreateWindow(	TEXT("static"),
							TEXT("Only Text"),
							WS_CHILD | WS_VISIBLE,
							20,20,100,25,
							hWnd,
							(HMENU)-1,	//	일반적으로 부모 윈도우와 통신할 일이 없기 때문에 ID를 부여할 의미가 없음.
							g_hInst,
							NULL);
			return 0;

		case WM_LBUTTONDOWN:
			SetWindowText(hStatic, "aaa"); return 0;

		case WM_DESTROY:
			PostQuitMessage(0); return 0;

	}//	switch (iMessage)
	
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//===============================================================================================