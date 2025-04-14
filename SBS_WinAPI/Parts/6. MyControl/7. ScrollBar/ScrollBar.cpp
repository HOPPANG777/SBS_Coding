/*=====================================================================================
	---------------
	9-1	스크롤 바..
	---------------
		-	용도
			-	윈도우 스크롤 상태 관리..
			-	일정 범위에 있는 값을
				대략적으로 선택할 경우 사용..
				-	사운드 볼륨,
					게임내의 속성값 등..

		-	생성하기..
				-	윈도우 클래스..
					-	"scrollbar"

				-	스타일
					SBS_HORZ	:	수평 스크롤 바
					SBS_VERT	:	수직 스크롤 바

			//	스크롤 범위 설정
			BOOL SetScrollRange( HWND hWnd, int nBar, int nMinPos, int nMaxPos, BOOL bRedraw )
				hWnd	:	스크롤바 핸들..
				nBar	:	메인 윈도우에 부착된 스크롤 바 또는
							별도의 스크롤 바 컨트롤..
							SB_CTL 이면 별도의 스크롤 바.
				nMinPos / nMaxPos	:	스크롤 범위..
				bRedraw	:	컨트롤 다시 그리기..


			//	스크롤바 현재 위치 설정.
			int SetScrollPos( HWND hWnd, int nBar, int nPos, BOOL bRedraw )
				nPos	:	현재 위치.



	----------------------------
	9-2	부모와 컨트롤간의 통신..
	----------------------------

		-	스크롤 바	->	부모..

			다른 컨트롤들은
			[ WM_COMMAND ]를 통해
			통지 메시지를 전달하지만
			스크롤 바는
			[ WM_HSCROLL ] 또는
			[ WM_VSCROLL ]를 통해
			전달함..

				LOWORD(wParam)
				-	스크롤 바 내에서
					마우스로 클릭한 위치..

				HIWORD(wParam)
				-	현재 위치..

				lParam
				-	스크롤 바의
					윈도우 핸들..


			LOWORD(wParam)으로 전달 되는 값..

				SB_LINELEFT ( SB_LINEUP )
					왼쪽 화살표 버튼 클릭..
					왼쪽(위)으로 한 단위 스크롤..

				SB_LINERIGHT ( SB_LINEDOWN )
					오른쪽 화살표 버튼 클릭..
					오른쪽(아래)으로 한 단위 스크롤..

				SB_PAGELEFT ( SB_PAGEUP )
					왼쪽 몸통 부분 클릭..
					한페이지 왼쪽으로 스크롤..

				SB_PAGERIGHT ( SB_PAGEDOWN )
					오른쪽 몸통 부분 클릭..
					한페이지 오른쪽(아래)으로 스크롤..

				SB_THUMBPOSITION
					스크롤 박스를 드래그한 후
					마우스 버튼 업..

				SB_THUMBTRACK
					스크롤 박스를
					드래그하고 있는 중..
					마우스 버튼을 놓을 때까지
					계속 전달 됨..
=====================================================================================*/
#include <windows.h>
//=====================================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MyScrollBar");
//=====================================================================================
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
//=====================================================================================
#define ID_SCRRED 100
#define ID_SCRGREEN 101
#define ID_SCRBLUE 102
HWND hRed,hGreen,hBlue;
int Red,Green,Blue;
//=====================================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH MyBrush, OldBrush;
	int TempPos;
	
	switch (iMessage)
	{
		case WM_CREATE:
			hRed = CreateWindow(	TEXT("scrollbar"),
									NULL,
									WS_CHILD | WS_VISIBLE | SBS_VERT,	//	수직 스크롤
									420,10,20,290,
									hWnd,
									(HMENU)ID_SCRRED,
									g_hInst,
									NULL);
			SetScrollRange(hRed, SB_CTL, 0, 255, TRUE);
			SetScrollPos(hRed, SB_CTL, 0, TRUE);
			Red = 0;

			hGreen = CreateWindow(	TEXT("scrollbar"),
									NULL,
									WS_CHILD | WS_VISIBLE | SBS_HORZ,	//	수평 스크롤
									10,10,400,20,
									hWnd,
									(HMENU)ID_SCRGREEN,
									g_hInst,
									NULL);
			SetScrollRange(hGreen, SB_CTL, 0, 255, TRUE);
			SetScrollPos(hGreen, SB_CTL, 0, TRUE);
			Green = 0;
		
			hBlue = CreateWindow(	TEXT("scrollbar"),
									NULL,
									WS_CHILD | WS_VISIBLE | SBS_HORZ,
									10,40,400,20,
									hWnd,
									(HMENU)ID_SCRBLUE,
									g_hInst,
									NULL);
			SetScrollRange(hBlue,SB_CTL,0,255,TRUE);
			SetScrollPos(hBlue,SB_CTL,0,TRUE);
			Blue = 0;
		
			return 0;

		case WM_VSCROLL:
			if ((HWND)lParam == hRed) TempPos = Red;

			switch (LOWORD(wParam))
			{		
				case SB_LINEUP:
					TempPos = max(0, TempPos - 1);
					break;

				case SB_LINEDOWN:
					TempPos = min(255, TempPos + 1);
					break;
		
				case SB_PAGEUP:
					TempPos = max(0, TempPos - 10);
					break;
		
				case SB_PAGEDOWN:
					TempPos = min(255, TempPos + 10);
					break;
				case SB_THUMBTRACK:
					TempPos = HIWORD(wParam);
					break;

			}//	switch (LOWORD(wParam))
				
			Red = TempPos;

			SetScrollPos(hRed, SB_CTL, TempPos, TRUE);
			InvalidateRect(hWnd, NULL, FALSE);
			return 0;


		case WM_HSCROLL:
		
			if ((HWND)lParam == hGreen) TempPos = Green;
			else TempPos = Blue;
		
			switch (LOWORD(wParam))
			{
				case SB_LINELEFT:		
					TempPos=max(0,TempPos-1);
					break;
				case SB_LINERIGHT:
					TempPos=min(255,TempPos+1);
					break;
				case SB_PAGELEFT:
					TempPos=max(0,TempPos-10);
					break;
				case SB_PAGERIGHT:
					TempPos=min(255,TempPos+10);
					break;
				case SB_THUMBTRACK:
					TempPos=HIWORD(wParam);
					break;

			}//	switch (LOWORD(wParam))
		
			if ((HWND)lParam == hGreen)
				Green=TempPos;
			else 
				Blue=TempPos;

			SetScrollPos((HWND)lParam,SB_CTL,TempPos, TRUE);
			InvalidateRect(hWnd,NULL, TRUE);
			return 0;

		case WM_PAINT:
			hdc = BeginPaint( hWnd, &ps );
			MyBrush = CreateSolidBrush( RGB( Red, Green, Blue ) );
			OldBrush = ( HBRUSH )SelectObject( hdc, MyBrush );
			Rectangle( hdc, 10, 80, 410, 300 );
			SelectObject( hdc, OldBrush );
			DeleteObject( MyBrush );
			EndPaint( hWnd, &ps );
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

	}//	switch (iMessage)

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
/*=====================================================================================
    Q > 스크롤바, 에디트박스, 버튼을 이용하여 
        스크롤바와 에디트 박스간의
		통신을 처리하는 프로그램을 만듭니다..
        
        0 ~ 255로 값을 설정한 값이
		서로에게 반영되도록 합니다..
        단, 값의 범위를 넘지않도록 합니다..
=====================================================================================*/