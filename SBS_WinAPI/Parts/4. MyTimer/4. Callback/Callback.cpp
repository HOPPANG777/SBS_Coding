/*=====================================================================================

	--------------
	-	콜백함수..
	--------------

	-	정의..
		-	특정 시스템에
			함수를 등록하기만 하고,
			어떤 이벤트가 발생했거나
			특정 시점에 도달했을 때
			해당 시스템에서
			호출해주는 함수..
			예) WndProc

		-	원형이
			미리 정해져 있음..
			
							
	-	타이머 처리 방식..

		-	방법 1)	WM_TIMER 메시지 처리..
			방법 2)	콜백함수..

		-	실행 결과는 거의 동일..
			-	단, WM_TIMER 메시지는
				다른 메시지가
				비슷한 시기에
				발생할 경우
				실행순서에 밀려
				늦게 호출될 수 있음..
			-	콜백함수는
				정확한 시간에 호출..


	-----------------------------------------------------------------------------
	void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)..
	-----------------------------------------------------------------------------
	-	hWnd
		-	타이머를 소유한
			윈도우 핸들..
	-	uMsg
		-	WM_TIMER..
	-	idEvent
		-	타이머 ID..
	-	dwTime
		-	윈도우즈가 실행된후
			경과시간..



*/
//=====================================================================================
#include <windows.h>
//=====================================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("Callback");
//=====================================================================================
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
//=====================================================================================
void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	HDC hdc;
	int i;
	hdc=GetDC(hWnd);
	for (i=0;i<1000;i++) {
		SetPixel(hdc,rand()%500, rand()%400,
			RGB(rand()%256,rand()%256,rand()%256));
	}
	ReleaseDC(hWnd, hdc);
}
//=====================================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;

	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd,1,100,TimerProc);
		return 0;
	case WM_LBUTTONDOWN:
		hdc=GetDC(hWnd);
		Ellipse(hdc,LOWORD(lParam)-10,HIWORD(lParam)-10,
			LOWORD(lParam)+10,HIWORD(lParam)+10);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//=====================================================================
/*
    Q > 타이머 메시지를 이용하여
		간단한 경마 시뮬레이션
		프로그램을 만듭니다..

        참고 )
            말 클래스를 만듭니다..
                -   주요 기능
                    -   속도, 이동 좌표, 랜덤시간 등의
						정보를 관리합니다..

            레이싱 매니져를 만듭니다.
                -   주요 기능.
                    -   말 5마리가 경주하게 합니다.
                    -   말은 각자의 랜덤 시간 마다
						속도가 변하게 합니다..

			타이머 프로시저 함수에서
			경과시간을 체크할땐
			GetTickCount 함수를 참고합니다..
*/
//=====================================================================