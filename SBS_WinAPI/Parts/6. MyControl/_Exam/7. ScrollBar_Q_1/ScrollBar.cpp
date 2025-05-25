//=======================================================================================
#include <windows.h>
#include <tchar.h>
//=======================================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MyScrollBar");
//=======================================================================================
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

}// int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
//=======================================================================================
#define ID_EDIT 100
#define ID_SCR 200
#define ID_BTTN 300

HWND hScroll;
HWND hEdit;
HWND hBttn;

int g_value = 0;
//=======================================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	int TempPos;
	
    switch (iMessage)
    {
	    case WM_CREATE:
        {
            hBttn = CreateWindow(TEXT("button"),
                TEXT("ok"),
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                120, 10, 100, 25,
                hWnd, (HMENU)ID_BTTN, g_hInst, NULL);


            hEdit = CreateWindow(TEXT("edit"),
                NULL,	//	NULL TEXT("글자 입력하면 뭐가 나오려나???")
                WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_WANTRETURN,	//	수평 스크롤을 지원..
                10, 10, 100, 25,
                hWnd,
                (HMENU)ID_EDIT,
                g_hInst,
                NULL);
            TCHAR szTmp[128] = { 0, };
            wsprintf(szTmp, "%d", g_value);
            SetWindowText(hEdit, szTmp);

            hScroll = CreateWindow(TEXT("scrollbar"),
                NULL,
                WS_CHILD | WS_VISIBLE | SBS_HORZ,
                10, 40, 100, 20,
                hWnd,
                (HMENU)ID_SCR,
                g_hInst,
                NULL);
            SetScrollRange(hScroll, SB_CTL, 0, 255, TRUE);
            SetScrollPos(hScroll, SB_CTL, g_value, TRUE);

        }// case WM_CREATE:
        return 0;



        case WM_COMMAND:
        {
            switch (LOWORD(wParam))
            {
                case ID_BTTN:
                {
                    TCHAR str[128];
                    GetWindowText(hEdit, str, 128);
                    g_value = _ttoi(str);
                    if (255 < g_value)
                    {
                        g_value = 255;
                        TCHAR szTmp[128] = { 0, };
                        wsprintf(szTmp, "%d", g_value);
                        SetWindowText(hEdit, szTmp);
                    
                    }// if (255 < g_value)
                    else if (g_value < 0)
                    {
                        g_value = 0;
                        TCHAR szTmp[128] = { 0, };
                        wsprintf(szTmp, "%d", g_value);
                        SetWindowText(hEdit, szTmp);

                    }// else if (g_value < 0)

                    SetScrollPos(hScroll, SB_CTL, g_value, TRUE);
                
                }// case ID_BTTN:
                break;

            }// switch (LOWORD(wParam))

        }// case WM_COMMAND:
        return 0;



	    case WM_HSCROLL:
        {
            TempPos = g_value;

            switch (LOWORD(wParam))
            {
                case SB_LINELEFT: TempPos = max(0, TempPos - 1); break;
                case SB_LINERIGHT: TempPos = min(255, TempPos + 1); break;
                case SB_PAGELEFT: TempPos = max(0, TempPos - 10); break;
                case SB_PAGERIGHT: TempPos = min(255, TempPos + 10); break;
                case SB_THUMBTRACK: TempPos = HIWORD(wParam); break;

            }// switch (LOWORD(wParam))

            g_value = TempPos;

            SetScrollPos((HWND)lParam, SB_CTL, TempPos, TRUE);

            TCHAR szTmp[128] = { 0, };
            wsprintf(szTmp, "%d", g_value);
            SetWindowText(hEdit, szTmp);

        }// case WM_HSCROLL:
        return 0;


	    case WM_DESTROY: PostQuitMessage(0); return 0;

	}// switch (iMessage)
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}// LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//=======================================================================================