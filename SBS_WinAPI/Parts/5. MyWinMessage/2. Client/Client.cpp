/*===========================================================================

	---------------
	2.	작업 영역..
	---------------
	
		-------------------
		-	작업 영역..
			( Client Area )
		-------------------

			-	일반적으로 윈도우 중앙
				흰 부분..


			-	프로그래밍의 대상이
				되는 영역..


			-	모든 출력의 기준..

				예)	좌표 10, 10..

					-	작업 영역의 좌상단을
						기준으로 10, 10..


		---------------------------
		-	BOOL GetClientRect(
					HWND hWnd,
					LPRECT lpRect )
		---------------------------

			-	작업 영역의 정보 구하기..
				( 클라이언트 영역 )


			---------------
			-	매개 변수..
			---------------
			
				-	hWnd..
					-	윈도우 핸들..
			
				-	lpRect..
					-	hWnd의 클라이언트
							( 작업 영역 )
						영역 크기..
						
							

		-----------------------
		-	비작업 영역..
			( Non Client Area )
		-----------------------

			-	그 외 영역..

			-	타이틀 바, 경계선,
				메뉴 등..

			-	운영체제가 알아서 관리..



	-------------
	3.	WM_SIZE..
	-------------

		-	윈도우 크기 변경시
			호출되는 메시지..

			-	lParam..

				-	하위 워드	:	윈도우 폭..
					상위 워드	:	윈도우 높이..


			-	wParam..

				-	메시지가 발생한 이유..

					SIZE_MAXIMIZED	:	최대화..
					SIZE_MINIMIZED	:	최소화..



	-------------
	4.	WM_MOVE..
	-------------

		-	윈도우 위치 변경시
			호출되는 메시지..

			-	lParam

				-	하위 워드	:	x 좌표
					상위 워드	:	y 좌표



		-	잘 사용되지 않음..

			-	윈도우의 위치가 응용프로그램에
				큰 영향을 주지 않음..

				ㄴ	실제 작업 영역은
					클라이언트 영역..

===========================================================================*/
#include <windows.h>
//=========================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("Client");
//=========================================================================
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)GetStockObject(LTGRAY_BRUSH);
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
//-----------------------------------------------------------
/*	WM_CREATE에서 작업영역 크기 조사..
//-----------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rt;

	switch (iMessage)
	{
		case WM_CREATE:
			GetClientRect(hWnd,&rt);
			return 0;


		case WM_PAINT:
			hdc=BeginPaint(hWnd, &ps);
			SetTextAlign(hdc,TA_CENTER);
			//TextOut(hdc, rt.right / 2, rt.bottom / 2, TEXT("Center String"),13);
			TextOut(hdc, rt.right * 0.5f, rt.bottom * 0.5f, TEXT("Center String"), 13);
			EndPaint(hWnd, &ps);
			return 0;


		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//*/
//-----------------------------------------------------------
/* WM_SIZE에서 작업영역 크기 조사..
//-----------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rt;

	switch (iMessage)
	{
		case WM_SIZE:
			//  방법 1)
			GetClientRect(hWnd, &rt);

			//  방법 2)
			//rt.right = LOWORD(lParam);
			//rt.bottom = HIWORD(lParam);
		
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;


		case WM_PAINT:
			hdc=BeginPaint(hWnd, &ps);
			SetTextAlign(hdc,TA_CENTER);
			TextOut(hdc,rt.right/2, rt.bottom/2, TEXT("Center String"),13);
			EndPaint(hWnd, &ps);
			return 0;


		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//*/
//-----------------------------------------------------------
/*	[ WM_PAINT ]에서 작업영역 크기 조사
//	
//	-	결과는 같으나
//		최적화 관점에서 비추..
// 
//		-	[ WM_PAINT ]는 작업영역 사이즈 변경시에도
//			호출되지만 그 외의 경우에도 호출됨..
// 
//			-	사이즈 변경시가 아닌 경우에도
//				클라이언트 영역 크기를
//				조사하는건 비효율적..
// 
// 
//	-	[ WM_PAINT ]는 출력처리만
//		담당 할 것..
// 
//		-	그 외 데이터 가공 처리는 
//			관련된 메시지에서 담당 할 것..

LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;

	switch (iMessage) {

		case WM_PAINT:
			hdc=BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rt);
			SetTextAlign(hdc,TA_CENTER);
			TextOut(hdc,rt.right/2, rt.bottom/2, TEXT("Center String"),13);
			EndPaint(hWnd, &ps);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

	}//	switch (iMessage)
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//*/
//-----------------------------------------------------------
//* WM_MOVE
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rt;
	static TCHAR tmp[100];

	switch (iMessage)
	{
		case WM_MOVE:
			{
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);
				wsprintf(tmp, "x = %d, y = %d", x, y);

				InvalidateRect(hWnd, NULL, TRUE);
			}
			return 0;


		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			GetClientRect(hWnd, &rt);
			SetTextAlign(hdc, TA_CENTER);
			TextOut(hdc, rt.right / 2, rt.bottom / 2, tmp, strlen(tmp));
			EndPaint(hWnd, &ps);
			return 0;


		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//*/
//-----------------------------------------------------------