/*==========================================================================

	-----------------
	5-1	에디트 박스..
	-----------------
		1.	용도	:	문자열을 직접 입력받을 때 사용.

		2.	생성하기

				-	윈도우 클래스
					-	"edit"

				-	============================================
					스타일..		|	기능..
					============================================
					ES_AUTOHSCROLL	|	수평 스크롤을 지원..
					--------------------------------------------
					ES_AUTOVSCROLL	|	여러줄 편집시
									|	수직 스크롤 지원..
					--------------------------------------------
					ES_LEFT			|	왼쪽 정렬..
					--------------------------------------------
					ES_CENTER		|	중앙 정렬..
					--------------------------------------------
					ES_RIGHT		|	오른쪽 정렬..
					--------------------------------------------
					ES_LOWERCASE	|	소문자로 변환하여 표시..
					--------------------------------------------
					ES_UPPERCASE	|	대문자로 변환하여 표시..
					--------------------------------------------
					ES_MULTILINE	|	여러줄을 편집..
					--------------------------------------------
					ES_NOHIDESEL	|	포커스를 잃더라도
									|	선택된 영역을 표시..
					--------------------------------------------
					ES_READONLY		|	읽기전용..
					============================================



	----------------------------
	5-2	부모와 컨트롤간의 통신..
	----------------------------

		-	에디트	->	부모

			EN_CHANGE		문자열이 변경..
			EN_UPDATE		문자열이 변경되기 직전..
			EN_ERRSPACE		메모리가 부족..
			EN_HSCROLL		사용자가 수평 스크롤 바를 클릭..
			EN_VSCROLL		사용자가 수직 스크롤 바를 클릭..
			EN_KILLFOCUS	포커스 잃음..
			EN_SETFOCUS		포커스 얻음..
			EN_MAXTEXT		지정한 문자열 길이 초과..

			EN_CHANGE
			-	문자열이 화면으로
				출력되고 난 후
				보내지는 메시지..

			EN_UPDATE
			-	문자열이 변경된 후
				화면에 출력하기 직전에
				보내는 메시지..
			-	문자열 길이에 따라
				에디트의 폭을 늘리거나
				별도의 조치를 취할 수 있음..

			호출 순서.
			-	문자열 변경
				-> EN_UPDATE 보냄..
				-> 화면에 출력..
				-> EN_CHANGE..


==========================================================================*/
#include <windows.h>
//==========================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MyEdit");
//==========================================================================
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

}//	int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
//==========================================================================
#define ID_EDIT 100
HWND hEdit;
int nTop = 10;
BOOL bShow = TRUE;
//==========================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	TCHAR str[128];
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR *Mes = TEXT("L Click : Move Down    /    R Click : Show & Hide");
	switch (iMessage)
	{
		case WM_CREATE:
			hEdit = CreateWindow(	TEXT("edit"),
									NULL,	//	NULL TEXT("글자 입력하면 뭐가 나오려나???")
									//	WS_BORDER		:	단선으로 된 경계선..
									//	ES_AUTOHSCROLL	:	수평 스크롤을 지원..
									//	ES_WANTRETURN	:	엔터키로 개행처리..
									WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_WANTRETURN,
									10,10,200,25,
									hWnd,
									(HMENU)ID_EDIT,
									g_hInst,
									NULL);
			return 0;
		case WM_COMMAND:
			switch ( LOWORD( wParam ) )
			{
				case ID_EDIT:
					switch (HIWORD(wParam))
					{
						case EN_CHANGE:	//	문자열이 변경될 때 호출.
							GetWindowText(hEdit,str,128);
							SetWindowText(hWnd,str);
					}
			}
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_LBUTTONDOWN:
			nTop += 10;
			MoveWindow(hEdit, 10, nTop, 200, 25, TRUE);
			return 0;

		case WM_RBUTTONDOWN:
			if (bShow) {
				bShow = FALSE;
				ShowWindow(hEdit, SW_HIDE);
			}
			else {
				bShow = TRUE;
				ShowWindow(hEdit, SW_SHOW);
			}
			return 0;

		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			TextOut(hdc, 200, 100, Mes, lstrlen(Mes));
			EndPaint(hWnd, &ps);
			return 0;

	}//	switch (iMessage)

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//=============================================================================
/*
	Q >	에디트박스와 버튼을 이용하여
		사칙연산을 처리하는
		간단한 계산기를 만듭니다..
*/
//=============================================================================