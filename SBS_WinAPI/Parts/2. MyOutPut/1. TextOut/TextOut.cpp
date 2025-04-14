//======================================================
#include <windows.h>
//======================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("TextOut");
//======================================================
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
//======================================================
/*
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_LBUTTONDOWN:
			hdc = GetDC(hWnd);
			//hdc = BeginPaint(hWnd, &ps);

			TextOut(
				hdc,
				100,100,
				TEXT("Beautiful Korea"),
				15);

			ReleaseDC(hWnd, hdc);
			//EndPaint(hWnd, &ps);
			return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/
//======================================================
/*
	-----------------
	1.	[ GetDC ] /
		[ ReleaseDC ]
	-----------------

		-	DC 핸들을 사용하고 반환하는
			일반적인 방식 제공..

	--------------
	2.	문제 발생..
	--------------
	
		-	응용 프로그램이
			화면 밖으로 이동하거나
			크기를 변경..

			-	문자열이 일부 또는
				전부 사라짐..

				-	운영 체제가 개별 윈도우의
					화면을 보관 및 복구 해주지
					않기 때문..


		-	해결책..

			-	화면이 지워질때 마다
				문자열을 다시 출력해야 함..
*/
//======================================================
/*
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
		case WM_CREATE:
				
				MessageBox(
					hWnd,
					TEXT("WM_Create"),
					"Title",
					MB_OK);

				return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

			//	어떤 상황에서 호출되는지
			//	디버깅을 통해 확인할 것..
		case WM_PAINT:
			hdc = BeginPaint(hWnd,&ps);
			//hdc = GetDC(hWnd);
			TextOut(
				hdc,
				100,100,
				TEXT("Beautiful Korea"),
				15);
			//ReleaseDC(hWnd, hdc);
			EndPaint(hWnd,&ps);
			return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/
//======================================================
/*
//	[ 참고 : https://blog.naver.com/tipsware/221119932350 ]

	3.	운영 체제는 윈도우의 일부가
		지워졌다는 사실을
		[ WM_PAINT ]를 통하여 통보..


	4.	[ BeginPaint ] / [ EndPaint ]

		-	[ WM_PAINT ]가 발생했을때
			DC 핸들을 관리하는
			좀더 전문적인 함수..

		-	다른 메시지에선
			사용불가..


	5.	[ WM_PAINT ]

		-	무효화된 영역이 유효 영역으로
			변경되는 경우,
			운영체제( 윈도우즈 )는
			응용 프로그램 스스로
			지워졌던 그림을 복구할 수 있도록
			복구가 필요한 영역의 정보를 담은
			[ WM_PAINT ] 메시지를
			해당 응용 프로그램에 전달..


	6.	[ PAINTSTRUCT ]

		-	[ WinUser.h ]에 정의되어 있음..

		-	주요 멤버 변수..

			---------
			-	hdc..
			---------

				-	[ BeginPaint ] 함수로 얻은
					DC의 핸들 값..

			------------
			-	fErase..
			------------

				-	윈도우의 기본 배경을
					다시 그릴지 여부..

			-------------
			-	rcPaint..
			-------------

				-	다시 그려야할 영역 정보..


			-	나머지는 운영체제에 의해
				내부적으로 사용 됨..
*/
//======================================================
/*
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
				
		SetTextAlign(hdc, TA_CENTER);

		TextOut(hdc,200,60,TEXT("Beautiful Korea"),15);

		//	DC에 대한 속성 변경은
		//	그 후의 출력에도 유지됨..
		SetTextAlign(hdc, TA_LEFT);
		TextOut(
			hdc,
			200,80,
			TEXT("is My"),
			5);

		TextOut(
			hdc,
			200,100,
			TEXT("Lovely Home Country"),
			19);

		EndPaint(hWnd,&ps);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/
//======================================================
/*
	-----------------------------
	BOOL TextOut(
		HDC hdc,
		int nXStart, int nYStart,
		LPCTSTR lpStr,
		int cbStr )
	-----------------------------

		-	한줄 짜리 문자열 출력..

		-	주요 매개 변수..

			-	hdc..
				-	DC의 핸들..

			-	nXStart, nYStart..
				-	문자열 출력 좌표..
				-	윈도우 작업영역의
					원점을 기준..

			-	lpStr..
				-	출력할 문자열..

			-	cbStr..
				-	출력할 문자열의 길이..


	-------------------------
	UINT SetTextAlign(
		HDC hdc, UINT fMode )
	-------------------------
		
		-	정렬 상태 설정..

		-------------------
		-	주요 매개 변수..
		-------------------

			-	hdc..
				-	DC의 핸들..

			-	fMode..
				-	정렬 모드..
*/
//======================================================
/*
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
			hdc=BeginPaint(hWnd,&ps);
		
			//	--------------------
			//	CP..
			//	( Current Position )
			//	--------------------
			
			// 
			//	-	텍스트 모드의
			//		커서 역할..
			// 
			//	-	다음 문자가 출력될
			//		위치를 커서가 표시..
			// 
			//	-	그래픽 모드에서
			//		다음 그래픽이 출력될 위치를
			//		CP가 관리함..

			//	-------------
			//	TA_UPDATECP..
			//	-------------
			// 
			//	-	출력 위치를 지정하는
			//		인수를 무시하고
			//		CP의 위치에 문자열 출력..
			// 
			//	-	출력후 CP를 문자열 바로
			//		다음 위치로 이동시킴..

			SetTextAlign(hdc, TA_UPDATECP);
			TextOut(hdc,200,60,TEXT("One "),4);
			TextOut(hdc,200,80,TEXT("Two "),4);
			TextOut(hdc,200,100,TEXT("Three"),5);
			EndPaint(hWnd,&ps);
			return 0;

	}

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//*/
//======================================================