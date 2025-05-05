/*========================================================================

	--------------------
	6.	컨트롤도 윈도우..
	--------------------

		-	[ CreateWindow ]로
			생성하는 윈도우..

			-	컨트롤도 [ CreateWindow ]로
				생성하는 일종의 윈도우..

			-	여러가지 스타일로 생성 가능..

			-	부모 윈도우가 메시지를 보내면
				해당 메시지를 처리..
				
				예)	체크 박스는 [ SendMessage ]함수를
					통하여 [ BM_SETCHECK ]를 받으면
					[ wParam ]값에 따라 자신의
					체크 상태를 갱신..

			-	[ CreateWindow ], [ SetWindowText ],
				[ MoveWindow ], [ ShowWindow ]등의
				윈도우 처리 함수 사용 가능..

			-	내부에서 [ WM_PAINT ] 메시지를
				처리하여 스스로 이미지를 갱신..



	--------------------
	7-1.	리스트 박스..
	--------------------

		----------
		-	용도..
		----------

			-	선택 가능한 여러 개의 항목들을
								( 주로 문자열 )
				나열해 놓고 그 중 하나 또는
				여러 개를 선택..



		---------------
		-	생성 하기..
		---------------

			-	윈도우 클래스
				-	"listbox"

			-	==============================================
				스타일			|	설명..
				==============================================
				LBS_MULTIPLESEL	|	여러개의 항목을 선택..
								|	-	디폴트는 하나만 선택..
				----------------------------------------------
				LBS_NOTIFY		|	목록 중 하나를 선택했을 때
								|	부모 윈도우로 통지 메시지
								|	보내기..
				----------------------------------------------
				LBS_SORT		|	추가된 항목들 자동 정렬..
				----------------------------------------------
				LBS_OWNERDRAW	|	문자열이 아닌
								|	비트맵이나 그림허용..
				----------------------------------------------
				LBS_STANDARD	|	LBS_NOTIFY | LBS_SORT | 
								|	WS_BORDER
				==============================================

				-	부모 윈도우로 통지 메시지를
					보내는 것이 일반적 이므로
					[ LBS_NOTIFY ]는 거의 필수..



	-------------------------
	7-2.	부모와 컨트롤간의
			통신..
	-------------------------

		-	부모	->	리스트박스..

			================================================
			메시지..			|	기능..
			================================================
			LB_ADDSTRING	|	-	항목 추가..
							|	-	lParam
							|		-	추가하고자 하는
							|			문자열의 주소 전달..
			------------------------------------------------
			LB_DELETESTRING	|	-	항목 삭제..
							|	-	wParam
							|		-	항목의 번호 전달..
							|	-	남은 문자열수를 반환..
			------------------------------------------------
			LB_GETCURSEL	|	-	현재 선택된 항목의
							|		번호(Index) 전달..
			------------------------------------------------
			LB_GETTEXT		|	-	지정한 항목의
							|		문자열을 전달..
							|	-	wParam
							|		-	항목 번호..
							|	-	lParam
							|		-	문자열 버퍼의
							|			주소를 넘겨주면
							|			버퍼에 문자열을
							|			채워줌..
			------------------------------------------------
			LB_GETCOUNT		|	-	항목의 개수 전달..
			------------------------------------------------
			LB_SETCURSEL	|	-	wParam
							|		-	선택하고자 하는
							|			항목 인덱스..
			================================================


		-	리스트 박스	->	부모..

			==========================================
			메시지..			|	기능..
			==========================================
			LBN_DBLCLK		|	-	리스트 박스
							|		더블클릭..
			------------------------------------------
			LBN_SELCANCEL	|	-	선택 취소..
			------------------------------------------
			LBN_SELCHANGE	|	-	선택 변경..
							|	-	가장 많이 사용됨..
			------------------------------------------
			LBN_KILLFOCUS	|	키보드 포커스 잃음..
			------------------------------------------
			LBN_SETFOCUS	|	키보드 포커스 얻음..
			------------------------------------------
			LBN_ERRSPACE	|	메모리가 부족..
			==========================================


========================================================================*/
#include <windows.h>
//========================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MyListBox");
//========================================================================
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
//========================================================================
#define ID_LISTBOX 100
TCHAR *Items[]={TEXT("사과"),TEXT("오렌지"),TEXT("메론"),TEXT("포도"), TEXT("딸기")};
HWND hList;
//========================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	int i;
	TCHAR str[128];
	switch (iMessage) {

		case WM_CREATE:
			hList = CreateWindow(	TEXT("listbox"),
									NULL,
									WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,	//	부모 윈도우로 통지 메시지 보내기..
									10,10,80,85,
									hWnd,
									(HMENU)ID_LISTBOX,
									g_hInst,
									NULL);
			for (i=0;i<5;i++)
				SendMessage(hList,LB_ADDSTRING,0,(LPARAM)Items[i]);	//	항목 추가..
			return 0;


		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
			case ID_LISTBOX:
				switch (HIWORD(wParam))
				{
				case LBN_SELCHANGE:	//	선택 변경..
					i = SendMessage(hList, LB_GETCURSEL,0,0);			//	현재 선택된 항목의 번호(Index) 전달..
					SendMessage( hList, LB_GETTEXT, i, (LPARAM)str );	//	지정한 항목의 문자열을 전달..
					SetWindowText( hWnd, str );
					break;
				}
				break;
			}
			return 0;
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

	}//	switch (iMessage)

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
/*========================================================================

    Q > 에디트 박스 과제에 리스트 박스기능을 추가하여
		5칙연산(+,-,*,/,%)를 완성하세요

========================================================================*/