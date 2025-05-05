/*========================================================================
	--------------
	2-1.	버튼..
	--------------

		----------
		-	용도..
		----------

			-	사용자로부터 1회성으로
				처리 할 명령을 수행하는
				컨트롤..


		---------------
		-	버튼 생성..
		---------------

			===============================================
				스타일..				|	기능..
			===============================================
				BS_PUSHBUTTON		|	푸시 버튼..
			-----------------------------------------------
				BS_DEFPUSHBUTTON	|	디폴트 푸시 버튼..
			-----------------------------------------------
				BS_CHECKBOX			|	체크 박스..
			-----------------------------------------------
				BS_3STATE			|	3가지 상태를 가지는
									|	체크 박스..
			-----------------------------------------------
				BS_AUTOCEHCKBOX		|	자동 체크 박스..
			-----------------------------------------------
				BS_AUTO3STATE		|	3가지 상태를 가지는
									|	자동 체크 박스..
			-----------------------------------------------
				BS_RADIOBUTTON		|	라디오 버튼..
			-----------------------------------------------
				BS_GROUPBOX			|	그룹 박스..
			===============================================



			HWND CreateWindow(	TEXT("button"),			-	버튼 클래스..								
								
	
								TEXT("버튼 입니다."),	-	일반 윈도우의 경우
															캡션바에 나오는
															윈도우 타이틀..

														-	버튼은 상단에 출력,
															체크 박스, 라디오 버튼은
															좌측에 출력..

														-	리스트 박스, 스크롤 바등
															캡션이 필요없는 컨트롤은
															NULL 지정..

								WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,		윈도우 스타일..

								20,		위치..
								20,
								100,	크기..
								25,
								hWnd,	-	부모 윈도우..

										-	컨트롤은 차일드 윈도우이므로
											부모 윈도우가 있어야함..

										-	부모 윈도우의 작업 영역을
											기준으로 한 좌표에 생성..

										-	이벤트가 생성되면
											부모 윈도우에게
											통지 메시지 전송..

										-	부모 윈도우가 파괴될 때
											같이 파괴됨..

				
								(HMENU)0,	메뉴핸들..

											-	차일드 컨트롤의 경우
												컨트롤의 ID..
				
								g_hInst,	컨트롤을 만드는 인스턴스의 핸들..

								NULL);		MDI에서 사용하는 구조체..
											-	보통 무시..
					
								HWND 리턴..		-	일반 윈도우와 마찬가지로
													컨트롤의 핸들 반환..
													( 윈도우 핸들.. )

												-	부모 윈도우로부터
													메시지 처리시 사용..

													-	MoveWindow, ShowWindow등
														윈도우 핸들을 필요로 하는 함수..



		-------------------------
		2-2.	부모와 컨트롤간의
				통신..
		-------------------------

			-	컨트롤은 자신에게 이벤트가 발생했을 때
				( 버튼 클릭, 에디트에 입력 등..)

				부모 윈도우에게 통지 메시지를 전송..
				( Notification Message )

				-	[ WM_COMMAND ]와
					적절한 파라미터 값을 전달..

					-	HIWORD( wParam )..

						ㄴ	통지 코드..


					-	LOWORD( wParam )..

						ㄴ	컨트롤의 ID ..


					-	lParam..

						ㄴ	메시지를 보낸
							차일드 윈도우의 핸들..


			-	버튼	->	부모..

				-	HIWORD( wParam )

					-	통지 코드..

						ㄴ	항상 [ BN_CLICKED ]..



				-	LOWORD( wParam )

					-	버튼의 ID..


========================================================================*/
#include <windows.h>
//========================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MyButton");
//========================================================================
int APIENTRY WinMain(
		HINSTANCE hInstance,
		HINSTANCE hPrevInstance,
		LPSTR lpszCmdParam,
		int nCmdShow )
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
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
//========================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	switch (iMessage)
	{
		case WM_CREATE:

			CreateWindow(	TEXT("button"),
							TEXT("버튼 입니다."),
							WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
							20,20,100,25,
							hWnd,
							(HMENU)0,
							g_hInst,
							NULL);

			CreateWindow(	TEXT("button"),
							TEXT("나도!!"),
							WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
							20,50,100,25,
							hWnd,
							(HMENU)1,
							g_hInst,
							NULL);
			return 0;


			//	WM_COMMAND..
			//	-	컨트롤의 이벤트가
			//		발생했을 때 운영 체제로부터
			//		전달받는 메시지..
		case WM_COMMAND:

			if (HIWORD(wParam) == BN_CLICKED)
			{
				//	컨트롤의 ID..
				switch (LOWORD(wParam))
				{
				case 0: MessageBox(hWnd, TEXT("First Button Clicked"), TEXT("Button"), MB_OK);
					break;

				case 1: MessageBox(hWnd, TEXT("Second Button Clicked"), TEXT("Button"), MB_OK);
					break;

				}//	switch (LOWORD(wParam))
			}			
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
	}//	switch (iMessage)
	
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//===================================================================
/*
	Q ) 버튼을 이용하여
		간단한 가위, 바위, 보 게임을
		만들어 봅니다..
		
		-	룰	:	5번을 진행하여
					결과를 출력합니다.

					승 : xx회 / 무 : xx회 / 패 : xx회

					재시작 버튼을 이용하여
					게임을 다시 진행할지
					결정..
*/
//===================================================================