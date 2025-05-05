/*=============================================================================================

	------------------
	3-1.	체크 박스..
	------------------

		----------
		-	용도..
		----------

			-	주로 어떤 사항의 참,거짓
				또는 Yes,No 여부를 선택하는
				용도로 사용..



		---------------
		-	생성 하기..
		---------------

			-	버튼과 유사..

				-	윈도우 클래스..
					-	"button"..



			------------
			-	스타일..
			------------

				-	상태 변경시 어떤 처리가
					필요한지 설정..

					-	자동 / 수동..

					-	주로 자동 상태를 선택하여
						상태 값만 조사하는
						경우가 많음..


				-	선택 가능한 상태의 갯수..

					-	2가지 상태..
						-	선택 / 비선택..

					-	3가지 상태..						
						-	선택 / 비선택 / 알 수 없음 ( or 결정 불가 )..

						=====================================================
									|	수동				|	자동
						=====================================================
						2가지 상태	|	BS_CHECKBOX		|	BS_AUTOCHECKBOX
						3가지 상태	|	BS_3STATE		|	BS_AUTO3STATE
						=====================================================



	-------------------------
	3-2.	부모와 컨트롤간의
			통신..
	-------------------------

		----------------------
		-	부모 -> 체크박스..
			( SendMessage )
		----------------------

			-	BM_GETCHECK..

				-	현재 체크되어 있는지 조사..
					추가정보는 없음..



			-	BM_SETCHECK..

				-	체크 상태를 변경하며
					wParam에 변경할
					체크 상태를 보내줌..


		-	BM_GETCHECK에 의해 리턴 또는
			BM_SETCHECK로 설정할 수 있는 값..

			==========================================
				옵션..				|	기능..
			==========================================
				BST_CHECKED			|	체크..
			------------------------------------------
				BST_UNCHECKED		|	언 체크..
			------------------------------------------
				BST_INDETERMINATE	|	알수 없음 또는
									|	결정 불가..
			==========================================


=============================================================================================*/
#include <windows.h>
//============================================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("Check");
//============================================================================================
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
	//	윈도우 배경 브러시를 컨트롤의 색상과 일치.
	WndClass.hbrBackground=(HBRUSH)(COLOR_BTNFACE+1);
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
//============================================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static HWND chk2StateManual, chk2StateAuto, chk3StateManual, chk3StateAuto;
	static BOOL bEllipse = FALSE;
	switch (iMessage) {
	case WM_CREATE:
		
		//	2가지 상태 수동..
		chk2StateManual = CreateWindow(	TEXT("button"),
								TEXT("원 그리기?"),
								WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
								20,20,160,25,
								hWnd,
								(HMENU)0,
								g_hInst,
								NULL);

		//	2가지 상태 자동..
		chk2StateAuto = CreateWindow(	TEXT("button"),
								TEXT("종료 메시지 출력?"),
								WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
								20,50,160,25,
								hWnd,
								(HMENU)1,
								g_hInst,
								NULL);

		//	3가지 상태 수동..
		chk3StateManual = CreateWindow(	TEXT("button"),
								TEXT("3 State"),
								WS_CHILD | WS_VISIBLE | BS_3STATE,
								20,80,160,25,
								hWnd,
								(HMENU)2,
								g_hInst,
								NULL);

		//	3가지 상태 자동..
		chk3StateAuto = CreateWindow(	TEXT("button"),
								TEXT("Auto 3 State"),
								WS_CHILD | WS_VISIBLE | BS_AUTO3STATE,
								20,110,160,25,
								hWnd,
								(HMENU)3,
								g_hInst,
								NULL);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			//	수동 상태인 경우..
			//	-	통지 메시지값에 따라
			//		설정상태를 바꿔줘야 함..
			//		-	BM_GETCHECK : 현재 버튼 상태값 얻기..
			//		-	BM_SETCHECK : 현재 버튼 상태 설정하기..

			if (SendMessage(chk2StateManual,BM_GETCHECK,0,0)==BST_UNCHECKED)
			{
				SendMessage(chk2StateManual,BM_SETCHECK,BST_CHECKED,0);
				bEllipse = TRUE;
			}
			else
			{
				SendMessage(chk2StateManual,BM_SETCHECK,BST_UNCHECKED,0);
				bEllipse = FALSE;
			}

			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 2:
			//	수동 상태인 경우..
			//	-	통지 메시지값에 따라
			//		설정상태를 바꿔줘야 함..
			//		-	BM_GETCHECK : 현재 버튼 상태값 얻기..
			//		-	BM_SETCHECK : 현재 버튼 상태 설정하기..
			if (SendMessage(chk3StateManual,BM_GETCHECK,0,0)==BST_UNCHECKED)
				SendMessage(chk3StateManual,BM_SETCHECK,BST_CHECKED,0);
			else 
			if (SendMessage(chk3StateManual,BM_GETCHECK,0,0)==BST_INDETERMINATE)
				SendMessage(chk3StateManual,BM_SETCHECK,BST_UNCHECKED,0);
			else
				SendMessage(chk3StateManual,BM_SETCHECK,BST_INDETERMINATE,0);
			break;
		}
		return 0;


	case WM_PAINT:
		hdc=BeginPaint(hWnd,&ps);
		
		if (bEllipse == TRUE)
			Ellipse(hdc,200,100,400,200);
		else
			Rectangle(hdc,200,100,400,200);

		EndPaint(hWnd, &ps);
		return 0;


	case WM_DESTROY:
		if (SendMessage(chk2StateAuto,BM_GETCHECK,0,0)==BST_CHECKED)
			MessageBox(hWnd,TEXT("종료!!"),TEXT("알림"),MB_OK);

		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));
}
//============================================================================================