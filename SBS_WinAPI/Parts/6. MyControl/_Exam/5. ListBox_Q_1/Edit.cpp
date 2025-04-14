//============================================================================
#include <windows.h>
#include <tchar.h>
//============================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MyEdit");
//============================================================================
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
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
//============================================================================
#define ID_EDIT 100
#define ID_EDIT2 200
#define ID_EDIT3 250
#define ID_BTTN 300
#define ID_LISTBOX 400

HWND hEdit;
HWND hEdit2;
HWND hEdit3;
HWND hBttn;
HWND hList;
TCHAR *Items[] = { TEXT("+"),TEXT("-"),TEXT("*"),TEXT("/"), TEXT("%") };
enum OPERATION {
    PLUS,
    MINUS,
    MULTI,
    DIVIDE,
    REST
};

int g_lVal = 0;
int g_rVal = 0;
int g_select = -1;
//============================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	TCHAR str[128];
	HDC hdc;
	
	switch (iMessage)
	{
		case WM_CREATE:
			hEdit=CreateWindow(	TEXT("edit"),
								NULL,	//	NULL TEXT("글자 입력하면 뭐가 나오려나???")
								WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_WANTRETURN,	//	수평 스크롤을 지원.
								10,10,100,25,
								hWnd,
								(HMENU)ID_EDIT,
								g_hInst,
								NULL);

			hEdit2 = CreateWindow(TEXT("edit"),
				NULL,	//	NULL TEXT("글자 입력하면 뭐가 나오려나???")
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_WANTRETURN,	//	수평 스크롤을 지원.
				200, 10, 100, 25,
				hWnd,
				(HMENU)ID_EDIT3,
				g_hInst,
				NULL);

			hEdit3 = CreateWindow(TEXT("edit"),
				NULL,	//	NULL TEXT("글자 입력하면 뭐가 나오려나???")
				WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_WANTRETURN | ES_READONLY,	//	수평 스크롤을 지원.
				400, 10, 100, 25,
				hWnd,
				(HMENU)ID_EDIT2,
				g_hInst,
				NULL);


			hBttn = CreateWindow(TEXT("button"),
				TEXT("결과"),
				WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
				100, 200, 100, 25,
				hWnd, (HMENU)ID_BTTN, g_hInst, NULL);


			hList = CreateWindow(TEXT("listbox"),
				NULL,
				WS_CHILD | WS_VISIBLE | WS_BORDER | LBS_NOTIFY,	//	부모 윈도우로 통지 메시지 보내기
				10, 100, 80, 85,
				hWnd,
				(HMENU)ID_LISTBOX,
				g_hInst,
				NULL);
                
			for (int i = 0; i < 5; i++)
				SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)Items[i]);	//	항목 추가.
			return 0;


		case WM_COMMAND:
		{
			switch (LOWORD(wParam)) {
				case ID_BTTN:
					GetWindowText(hEdit, str, 128);
					g_lVal = _ttoi(str);
					GetWindowText(hEdit2, str, 128);
					g_rVal = _ttoi(str);

					TCHAR result[128];

					switch (g_select)
					{
						case PLUS:
							wsprintf(result, TEXT("%d"), g_lVal + g_rVal);
							break;

						case MINUS:
							wsprintf(result, TEXT("%d"), g_lVal - g_rVal);
							break;

						case MULTI:
							wsprintf(result, TEXT("%d"), g_lVal * g_rVal);
							break;

						case DIVIDE:
							wsprintf(result, TEXT("%d"), g_lVal / g_rVal);
							break;

						case REST:
							wsprintf(result, TEXT("%d"), g_lVal % g_rVal);
							break;

					}//	switch (g_select)
			
					SetWindowText(hEdit3, result);
					break;

				case ID_LISTBOX:
					switch (HIWORD(wParam))
					{
						case LBN_SELCHANGE:	//	선택 변경.
							g_select = SendMessage(hList, LB_GETCURSEL, 0, 0); break;
					}
					break;
		
			}//	switch (LOWORD(wParam))

		}//	case WM_COMMAND:
		return 0;

		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

	}//	switch (iMessage)
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//============================================================================