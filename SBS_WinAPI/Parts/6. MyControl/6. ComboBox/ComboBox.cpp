/*=======================================================================

	------------------
	8-1.	콤보 박스..
	------------------
		
		----------
		-	용도..
		----------

			-	[ 에디트 박스 ] + [ 리스트 박스 ]

			-	목록에 있는 항목 중의
				하나를 선택..

			-	원하는 항목이 없을 경우
				에디트에 직접 원하는 항목을
				입력 가능..

			-	필요할 경우에만 목록을 열어
				선택하므로 화면 공간을
				적게 차지..

		---------------
		-	생성 하기..
		---------------
				
			-	윈도우 클래스
				-	"combobox"

			-	주요 스타일..

				=================================================
				CBS_SIMPLE			|	에디트 only..
				-------------------------------------------------
				CBS_DROPDOWN		|	에디트 || 리스트 박스..
				-------------------------------------------------
				CBS_DROPDOWNLIST	|	리스트 박스 only..
									|	에디트에 항목 입력 불가..
				=================================================

			-	이 외의 스타일이나 메시지들은
				[ 에디트 ]와 [ 리스트 ]의 것들과
				거의 동일..
				
				ㄴ	접두어만 조금씩 다름..

				예) 리스트 박스	- LB_ADDSTRING
					콤보 박스	- CB_ADDSTRING



	------------------------
	8-2.	부모와 컨트롤간의
			통신..
	------------------------

		-	[ 에디트 박스 ],
			[ 리스트 박스 ]와 유사..

			--------------------
			부모 -> 리스트 박스..
			--------------------

				-	CB_ADDSTRING..

					-	항목 추가..
					-	lParam
						-	추가하고자 하는
							문자열의 주소 전달..


				-	CB_GETCURSEL..

					-	현재 선택된 항목의
						번호(Index) 전달..



			--------------------
			리스트 박스 -> 부모..
			--------------------

				-	CBN_EDITCHANGE..

					-	[ 콤보 박스 ]에 부착된
						[ 에디트 박스 ]의
						내용 수정..



				-	CBN_SELCHANGE..

					-	선택 변경..
					-	가장 많이 사용됨..

=======================================================================*/
#include <windows.h>
//=======================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MyComboBox");
//=======================================================================
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
}
//=======================================================================
#define ID_COMBOBOX 100
TCHAR *Items[] = { TEXT("사과"),TEXT("오렌지"),TEXT("메론"),TEXT("포도"), TEXT("딸기") };
HWND hCombo;
//=======================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	int i;
	TCHAR str[128];
	
	switch (iMessage)
	{
		case WM_CREATE:
			hCombo = CreateWindow(	TEXT("combobox"),
									NULL,
									WS_CHILD | WS_VISIBLE | CBS_DROPDOWN,	//	에디트 || 리스트 박스..
									10,10,80,120,
									hWnd,
									(HMENU)ID_COMBOBOX,
									g_hInst,
									NULL);

			//	항목 추가...
			for (i=0;i<5;i++)
				SendMessage(hCombo,CB_ADDSTRING,0,(LPARAM)Items[i]);

			//	인덱스로 항목 선택..
			SendMessage(hCombo, CB_SETCURSEL, 0, 0);
			return 0;


		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case ID_COMBOBOX:
					switch (HIWORD(wParam))
					{
						//	선택 변경..
						case CBN_SELCHANGE:

							//	현재 선택된 항목의 번호(Index) 전달..
							i = SendMessage(hCombo, CB_GETCURSEL,0,0);

							//	지정한 항목의 문자열을 전달..
							SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)str);
							SetWindowText(hWnd, str);
							break;

						//	콤보박스의 에디트 갱신..
						case CBN_EDITCHANGE:
							GetWindowText(hCombo, str, 128);
							SetWindowText(hWnd,str);
							break;

					}//	switch (HIWORD(wParam))

			}//	switch (LOWORD(wParam))
			return 0;


		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

	}//	switch (iMessage)

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
/*=======================================================================
    Q > 리스트 박스과제를 콤보박스로 교체하여
		5칙연산(+,-,*,/,%)를 완성하세요
=======================================================================*/