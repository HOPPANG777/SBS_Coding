//=================================================================
//	참고 : https://m.blog.naver.com/power2845/50143021565
//=================================================================
#include <windows.h>
//=================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass=TEXT("Mouse");
//=================================================================
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
	//WndClass.style=CS_HREDRAW | CS_VREDRAW;
	//	4. 더블 클릭.
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
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
//=================================================================
// 도형 상수.
enum
{
	LINE,
	RECTANGLE,
	CIRCLE
};
// 색깔 상수.
enum
{
	RED,
	GREEN,
	BLACK,
	BLUE,
	WHITE
};
//=================================================================
//	5.	wParam, lParam 참고.
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	static int x;
	static int y;

	static BOOL bNowDraw=FALSE;

	static int drawMode = LINE;		//	그리기 모드.
	static int penColor = BLACK;	//	펜 색.
	static int brushColor = WHITE;	//	브러쉬 색.

	static bool isShift = false;	//	쉬프트 버튼이 눌렸나?
	static bool isCtrl = false;		//	컨트롤 버튼이 눌렸나?

	static TCHAR szDrawMode[30] = "선 그리기.";		//	현재 그리기 모드 출력.
	static TCHAR szPenColor[30] = "검은 펜.";		//	현재 펜 색상 출력.
	static TCHAR szBrushColor[30] = "하얀 브러쉬.";	//	현재 브러쉬 색상 출력.
	
	//	선의 색상 핸들.
	HPEN curPen = NULL;
	HPEN oldPen = NULL;

	//	도형 색상.
	HBRUSH curBrush = NULL;
	HBRUSH oldBrush = NULL;

	switch (iMessage) {

		case WM_KEYDOWN:
		{
			isShift = false;
			isCtrl = false;

			if (GetAsyncKeyState(VK_SHIFT) & 0x8000)	//	시프트 버튼이 눌렸나?
				isShift = true;

			if (GetAsyncKeyState(VK_CONTROL) & 0x8000)	//	컨트롤 버튼이 눌렸나?
				isCtrl = true;

			switch (wParam)
			{			
				case 0x31:	//	숫자 1
				{
					if (isShift)
					{
						strcpy(szPenColor, "검은 펜.");
						penColor = BLACK;
					}					
					else if (isCtrl)
					{
						strcpy(szBrushColor, "하얀 브러쉬.");
						brushColor = WHITE;
					}					
					else
					{
						strcpy(szDrawMode, "선 그리기.");
						drawMode = LINE;
					}

				}//	case 0x31:
				break;

				case 0x32:	//	숫자 2
				{
					if (isShift)
					{
						strcpy(szPenColor, "빨간 펜.");
						penColor = RED;
					}
					else if (isCtrl)
					{
						strcpy(szBrushColor, "빨간 브러쉬.");
						brushColor = RED;
					}
					else
					{
						strcpy(szDrawMode, "사각형 그리기.");
						drawMode = RECTANGLE;
					}
			
				}//	case 0x32:
				break;

				case 0x33:	//	숫자 3
				{
					if (isShift)
					{
						strcpy(szPenColor, "녹색 펜.");
						penColor = GREEN;
					}
					else if (isCtrl)
					{
						strcpy(szBrushColor, "녹색 브러쉬.");
						brushColor = GREEN;
					}
					else
					{
						strcpy(szDrawMode, "원 그리기.");
						drawMode = CIRCLE;
					}

				}//	case 0x33:
				break;

				case 0x34:	//	숫자 4
				{
					if (isShift)
					{
						strcpy(szPenColor, "파란 펜.");
						penColor = BLUE;
					}					
					else if (isCtrl)
					{
						strcpy(szBrushColor, "파란 브러쉬.");
						brushColor = BLUE;
					}					

				}//	case 0x34:
				break;

			}//	switch (wParam)

			InvalidateRect(hWnd, NULL, TRUE);

		}//	case WM_KEYDOWN:
		return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);

			TextOut(hdc, 1000, 40, szDrawMode, strlen(szDrawMode));			//	현재 그리기 모드 출력.
			TextOut(hdc, 1000, 80, szPenColor, strlen(szPenColor));			//	현재 펜 색상 출력.
			TextOut(hdc, 1000, 120, szBrushColor, strlen(szBrushColor));	//	현재 브러쉬 색상 출력.

			EndPaint(hWnd, &ps);
		}
		return 0;

		case WM_LBUTTONDOWN:
			x=LOWORD(lParam);
			y=HIWORD(lParam);
			bNowDraw=TRUE;
			return 0;

		case WM_MOUSEMOVE:
			if (bNowDraw==TRUE) {
				hdc=GetDC(hWnd);

				//	펜 생성.
				switch (penColor)
				{
				case RED:
					curPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
					break;

				case GREEN:
					curPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
					break;

				case BLUE:
					curPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
					break;
				}
				oldPen = (HPEN)SelectObject(hdc, curPen);			//	생성된 펜을 dc에 전달하면 기존 펜 리소스 데이터가 반환됨.

				//	브러쉬 생성.
				switch (brushColor)
				{
				case RED:
					curBrush = CreateSolidBrush(RGB(255, 0, 0));
					break;

				case GREEN:
					curBrush = CreateSolidBrush(RGB(0, 255, 0));
					break;

				case BLUE:
					curBrush = CreateSolidBrush(RGB(0, 0, 255));
					break;
				}
				oldBrush = (HBRUSH)SelectObject(hdc, curBrush);		//	생성된 브러쉬를 dc에 전달하면 기존 브러쉬 리소스 데이터가 반환됨.

				//	그리기 모드.
				switch (drawMode)
				{
				case LINE:
					MoveToEx(hdc, x, y, NULL);
					x = LOWORD(lParam);
					y = HIWORD(lParam);
					LineTo(hdc, x, y);
					break;

				case RECTANGLE:
					x = LOWORD(lParam);
					y = HIWORD(lParam);
					Rectangle(hdc, x - 50, y - 50, x + 50, y + 50);
					break;

				case CIRCLE:
					x = LOWORD(lParam);
					y = HIWORD(lParam);
					Ellipse(hdc, x - 50, y - 50, x + 50, y + 50);
					break;
				}

				if (oldPen != NULL)
					SelectObject(hdc, oldPen);	//	기존 펜 리소스를 dc에 반환.
				if (curPen != NULL)
					DeleteObject(curPen);		//	생성한 펜 리소스 제거.

				if (oldBrush != NULL)
					SelectObject(hdc, oldBrush);	//	기존 브러시 리소스를 dc에 반환.
				if (curBrush != NULL)
					DeleteObject(curBrush);			//	생성한 브러시 리소스 제거.

				ReleaseDC(hWnd,hdc);

			}//	if (bNowDraw==TRUE)
			return 0;

			//	버튼 업( 그림을 다 그린 후 ) 리소스를 정리한다.
		case WM_LBUTTONUP:
			bNowDraw = FALSE;
			return 0;
			
		case WM_LBUTTONDBLCLK:
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

	}//	switch (iMessage)

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//=================================================================