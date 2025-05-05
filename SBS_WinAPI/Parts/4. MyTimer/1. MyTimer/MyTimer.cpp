/*================================================================================
 
	--------------
	1.	WM_TIMER..
	--------------
	
		-	한 번 시간을 설정해 놓으면
			일정한 시간 간격을 두고
			연속적으로 계속 발생..


		----------
		-	용도..
		----------

			-	주기적으로 같은 동작..
				
				예) 시계, 애니메이션..


			-	시간대 별로 여러번 나누어
				해야할 일..

				예) 팝업 정보..

================================================================================*/
#include <windows.h>
//===========================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("MyTimer");
//===========================================================================
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
//===========================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st;
	static TCHAR sTime[128];
	static RECT rt={100,100,400,120};

	switch (iMessage) {
	case WM_CREATE:
		/*
			-------------------------------
			UINT SetTimer(
					HWND hWnd,
					UINT nIDEvent,
					UINT uElapse,
					TIMERPROC lpTimerFunc )
			-------------------------------

			-	타이머 생성..


				----------
				-	hWnd..
				----------

					-	타이머 메시지를 받을
						윈도우..

					-	일반적으로 WndProc의 hWnd를
						그대로 사용..



				--------------
				-	nIDEvent..
				--------------

					-	타이머의 ID..



				-------------
				-	uElapse..
				-------------

					-	타이머의 주기..
						단위는 1/1000초..

					-	이 값이 1이라고 해서
						타이머 메시지가
						초당 1000번 발생하진 않음..

						-	1초에 100회 이상
							발생하지 않음..

				
				
				-----------------
				-	lpTimerFunc..
				-----------------

					-	타이머 메시지가 발생할
						때마다 호출될 함수..

		*/
		SetTimer( hWnd, 1, 1000, NULL );
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;


	case WM_TIMER:
		/*
			-	wParam
				-	타이머 ID..

			-	lParam
				-	타이머 메시지 발생 시
					호출될 함수의 주소..
		*/

		//	현재 PC에 세팅되어 있는
		//	시간 정보 가져오기..
		GetLocalTime(&st);
		wsprintf(sTime,TEXT("지금은 %d시 %d분 %d초 입니다."),
			st.wHour,st.wMinute,st.wSecond);

		//	클라이언트 영역 전체 갱신..
		InvalidateRect(hWnd,NULL,TRUE);

		//	rt 로 설정된 영역만 갱신..
		//InvalidateRect(hWnd,&rt,TRUE);
		return 0;


	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		TextOut(hdc,100,100,sTime,lstrlen(sTime));
		EndPaint(hWnd,&ps);
		return 0;


	case WM_DESTROY:
		/*
			------------------
			KillTimer(
				HWND hWnd,
				UINT nIDEvent)
			------------------

				-	SetTimer에 의해 생성된
					타이머 리소스 반환..
		*/
		KillTimer(hWnd,1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//=========================================================================
/*
    Q > 5초 카운트 다운후
		종료되는 프로그램을 만듭니다..
        
        팁 ) SendMessage를 활용하여
			강제 종료되는 기능 적용..
*/
//=========================================================================
/*
	[ 참고 ]

		[C++] 시스템 시간 날짜 얻어오기, SYSTEMTIME, GetLocalTime, GetSystemTime byte 모호한 기호입니다. 에러 windows.h to_string
		https://blog.naver.com/dorergiverny/223036013271

*/
//=========================================================================