//==========================================================================
#include <windows.h>
#include <stdlib.h>
#include "CControlFactory.h"
#include "CScrollBar.h"
#include "CEdit.h"
#include "CButton.h"
#include "CListBox.h"
#include "CComboBox.h"
#include "CStatic.h"
#include "CFigureFactory.h"
#include "CLine.h"
#include "CRectangle.h"
#include "CCircle.h"
//==========================================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND hWndMain;
LPCTSTR lpszClass=TEXT("MyScrollBar");
//==========================================================================
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
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

}//	int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance ,LPSTR lpszCmdParam,int nCmdShow)
//==========================================================================
//	색 모드.
enum
{	
	PENCOLOR,
	BRUSHCOLOR,
};
//	색 모드.
int g_ColorMode = PENCOLOR;

//	그리기 모드.
enum
{
	LINE,
	RECTANGLE,
	CIRCLE,
};
int g_curDrawMode = LINE;

//	컨트롤 ID.
enum
{
	ID_SCRRED = 100,
	ID_SCRGREEN,
	ID_SCRBLUE,

	ID_EDITRED,
	ID_EDITGREEN,
	ID_EDITBLUE,

	ID_BUTTONRED,
	ID_BUTTONGREEN,
	ID_BUTTONBLUE,

	ID_LISTBOX,

	ID_COMBOBOX

};
//==========================================================================
//	컨트롤 팩토리.
CControlFactory* g_pControlFactory;
//==========================================================================
//	스크롤 컨트롤 배열 인덱스.
enum
{
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE,

	COLOR_SIZE
};
//	스크롤 객체.
CScrollBar* g_pScrollBar[COLOR_SIZE] = { 0, };
//==========================================================================
//	에디트 객체.
CEdit *g_pEdit[COLOR_SIZE] = { 0, };
//-------------------------------------------
//	버튼 객체.
CButton* g_pButton[COLOR_SIZE] = { 0, };
//-------------------------------------------
//	리스트 박스.
CListBox* g_pListBox = 0;
//-------------------------------------------
//	콤보 박스.
CComboBox* g_pComboBox = 0;
//-------------------------------------------
//	스태틱.
CStatic* g_pStatic[COLOR_SIZE] = { 0, };
//-------------------------------------------
//	브러쉬 컬러.
int g_BrushColor[COLOR_SIZE] = { 0, };
//	펜 컬러.
int g_PenColor[COLOR_SIZE] = { 0, };
//-------------------------------------------
CLine* g_pLine = NULL;
CRectangle* g_pRect = NULL;
CCircle* g_pCircle = NULL;
CFigureFactory* g_figureFactory = NULL;
//==========================================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HBRUSH MyBrush, OldBrush;
	HPEN myPen, oldPen;
	switch (iMessage)
	{
		//-----------------------------
		case WM_CREATE:
		{
			//------------------
			//	콘트롤 팩토리 생성.
			g_pControlFactory = new CControlFactory(hWnd, g_hInst);
			g_figureFactory = new CFigureFactory();
			//------------------
			//	스크롤 생성.
			int posX = 500, posY = 80, offsetY = 45;
			g_pScrollBar[COLOR_RED] = (CScrollBar*)g_pControlFactory->Create(SCROLLBAR, (HMENU)ID_SCRRED, NULL, posX, posY, 255, 20);
			if (!g_pScrollBar[COLOR_RED]->Create(0, 0, 255))
				MessageBox(hWnd, "ID_SCRRED 생성 실패.", "에러", MB_OK);

			g_pScrollBar[COLOR_GREEN] = (CScrollBar*)g_pControlFactory->Create(SCROLLBAR, (HMENU)ID_SCRGREEN, NULL, posX, posY + offsetY, 255, 20);
			if (!g_pScrollBar[COLOR_GREEN]->Create(0, 0, 255))
				MessageBox(hWnd, "ID_SCRGREEN 생성 실패.", "에러", MB_OK);

			g_pScrollBar[COLOR_BLUE] = (CScrollBar*)g_pControlFactory->Create(SCROLLBAR, (HMENU)ID_SCRBLUE, NULL, posX, posY + offsetY * 2, 255, 20);
			if (!g_pScrollBar[COLOR_BLUE]->Create(0, 0, 255))
				MessageBox(hWnd, "ID_SCRBLUE 생성 실패.", "에러", MB_OK);

			//------------------
			//	에디트 생성.
			TCHAR szTmp[10];
			g_pEdit[COLOR_RED] = (CEdit*)g_pControlFactory->Create(EDIT, (HMENU)ID_EDITRED, NULL, posX + 280, posY, 30, 20);
			if (!g_pEdit[COLOR_RED]->Create())
				MessageBox(hWnd, "ID_EDITRED 생성 실패.", "에러", MB_OK);
			g_pScrollBar[COLOR_RED]->GetValueString(szTmp);
			g_pEdit[COLOR_RED]->SetText(szTmp);

			g_pEdit[COLOR_GREEN] = (CEdit*)g_pControlFactory->Create(EDIT, (HMENU)ID_EDITGREEN, NULL, posX + 280, posY + offsetY, 30, 20);
			if (!g_pEdit[COLOR_GREEN]->Create())
				MessageBox(hWnd, "ID_EDITGREEN 생성 실패.", "에러", MB_OK);
			g_pScrollBar[COLOR_GREEN]->GetValueString(szTmp);
			g_pEdit[COLOR_GREEN]->SetText(szTmp);

			g_pEdit[COLOR_BLUE] = (CEdit*)g_pControlFactory->Create(EDIT, (HMENU)ID_EDITBLUE, NULL, posX + 280, posY + offsetY * 2, 30, 20);
			if (!g_pEdit[COLOR_BLUE]->Create())
				MessageBox(hWnd, "ID_EDITBLUE 생성 실패.", "에러", MB_OK);
			g_pScrollBar[COLOR_BLUE]->GetValueString(szTmp);
			g_pEdit[COLOR_BLUE]->SetText(szTmp);

			//------------------
			//	버튼 생성.
			g_pButton[COLOR_RED] = (CButton*)g_pControlFactory->Create(BUTTON, (HMENU)ID_BUTTONRED, "확인", posX + 320, posY - 5, 60, 30);
			if (!g_pButton[COLOR_RED]->Create())
				MessageBox(hWnd, "ID_BUTTONRED 생성 실패.", "에러", MB_OK);

			g_pButton[COLOR_GREEN] = (CButton*)g_pControlFactory->Create(BUTTON, (HMENU)ID_BUTTONGREEN, "확인", posX + 320, posY - 5 + offsetY, 60, 30);
			if (!g_pButton[COLOR_GREEN]->Create())
				MessageBox(hWnd, "ID_BUTTONGREEN 생성 실패.", "에러", MB_OK);

			g_pButton[COLOR_BLUE] = (CButton*)g_pControlFactory->Create(BUTTON, (HMENU)ID_BUTTONBLUE, "확인", posX + 320, posY - 5 + offsetY * 2, 60, 30);
			if (!g_pButton[COLOR_BLUE]->Create())
				MessageBox(hWnd, "ID_BUTTONBLUE 생성 실패.", "에러", MB_OK);

			//------------------
			//	리스트 박스 생성.
			g_pListBox = (CListBox*)g_pControlFactory->Create(LISTBOX, (HMENU)ID_LISTBOX, NULL, posX, posY + 120, 70, 60);
			if (!g_pListBox->Create())
				MessageBox(hWnd, "ID_LISTBOX 생성 실패.", "에러", MB_OK);
			TCHAR *ppszDrawMode[] = { TEXT("선"),TEXT("사각형"),TEXT("원") };
			g_pListBox->Add(ppszDrawMode, 3);
			g_pListBox->SetCurSel(0);

			//------------------
			//	콤보 박스 생성.
			g_pComboBox = (CComboBox*)g_pControlFactory->Create(COMBOBOX, (HMENU)ID_COMBOBOX, NULL, posX + 80, posY + 120, 120, 60);
			if (!g_pComboBox->Create())
				MessageBox(hWnd, "ID_LISTBOX 생성 실패.", "에러", MB_OK);
			TCHAR *ppszColorMode[] = { TEXT("펜 컬러"),TEXT("브러시 컬러") };
			g_pComboBox->Add(ppszColorMode, 2);
			g_pComboBox->SetCurSel(0);

			//------------------
			//	스태틱 생성.
			g_pStatic[COLOR_RED] = (CStatic*)g_pControlFactory->Create(STATIC, (HMENU)-1, "빨간색", posX, posY - 20, 60, 20);
			if (!g_pStatic[COLOR_RED]->Create())
				MessageBox(hWnd, "빨간색 스태틱 생성 실패.", "에러", MB_OK);
		
			g_pStatic[COLOR_GREEN] = (CStatic*)g_pControlFactory->Create(STATIC, (HMENU)-1, "녹색", posX, posY - 20 + offsetY, 60, 20);
			if (!g_pStatic[COLOR_GREEN]->Create())
				MessageBox(hWnd, "녹색 스태틱 생성 실패.", "에러", MB_OK);

			g_pStatic[COLOR_BLUE] = (CStatic*)g_pControlFactory->Create(STATIC, (HMENU)-1, "파란색", posX, posY - 20 + offsetY*2, 60, 20);
			if (!g_pStatic[COLOR_BLUE]->Create())
				MessageBox(hWnd, "파란색 스태틱 생성 실패.", "에러", MB_OK);

			//------------------
			//	도형 생성.
			if (g_pLine == NULL)
				g_pLine = (CLine*)g_figureFactory->Create(F_LINE, 10, 80, 410, 300);

			if (g_pRect == NULL)
				g_pRect = (CRectangle*)g_figureFactory->Create(F_RECTANGLE, 10, 80, 410, 300);

			if (g_pCircle == NULL)
				g_pCircle = (CCircle*)g_figureFactory->Create(F_CIRCLE, 10, 80, 410, 300);


		} return 0;
		//-----------------------------
		case WM_HSCROLL:

			for (int i = 0; i < COLOR_SIZE; ++i)
			{
				if ((HWND)lParam == g_pScrollBar[i]->GetHwnd())
				{
					if( g_ColorMode == BRUSHCOLOR)
						g_BrushColor[i] = g_pScrollBar[i]->OnHScroll(wParam);
					else
						g_PenColor[i] = g_pScrollBar[i]->OnHScroll(wParam);

					TCHAR szTmp[10];
					g_pScrollBar[i]->GetValueString(szTmp);
					g_pEdit[i]->SetText(szTmp);
					break;

				}//	if ((HWND)lParam == g_pScrollBar[i]->GetHwnd())

			}//	for (int i = 0; i < COLOR_SIZE; ++i)
		
			InvalidateRect(hWnd, NULL, TRUE);
			return 0;
			//-----------------------------
			case WM_COMMAND: //	컨트롤의 통지 메시지 전달시 호출되는 메시지.
			{
				int id = LOWORD(wParam);
				if (g_pComboBox != NULL && id == g_pComboBox->GetID())
				{
					g_ColorMode = g_pComboBox->GetCurSel();

					for (int i = 0; i < COLOR_SIZE; ++i)
					{
						int tmp;
						if (g_ColorMode == BRUSHCOLOR)
							tmp = g_BrushColor[i];
						else
							tmp = g_PenColor[i];

						g_pScrollBar[i]->SetValue(tmp);

						TCHAR szTmp[10];
						wsprintf(szTmp, "%d", tmp);
						g_pEdit[i]->SetText(szTmp);

					}//	for (int i = 0; i < COLOR_SIZE; ++i)
			
				}//	if (g_pComboBox != NULL && id == g_pComboBox->GetID())
				else if (g_pListBox != NULL && id == g_pListBox->GetID())
					g_curDrawMode = g_pListBox->GetCurSel();
				else
				{
					for (int i = 0; i < COLOR_SIZE; ++i)
					{
						if (g_pButton[i] != NULL && g_pButton[i]->GetID() == id)
						{
							TCHAR szTmp[10];
							g_pEdit[i]->GetText(szTmp, 10);
							int value = atoi(szTmp);
							g_pScrollBar[i]->SetValue(value);
							if (g_ColorMode == BRUSHCOLOR)
								g_BrushColor[i] = value;
							else
								g_PenColor[i] = value;

							break;

						}//	if (g_pButton[i] != NULL && g_pButton[i]->GetID() == id)

					}//	for (int i = 0; i < COLOR_SIZE; ++i)

				}//	~if ((HWND)lParam == g_pListBox->GetHwnd())
			
				InvalidateRect(hWnd, NULL, TRUE);

			}//	case WM_COMMAND:
			return 0;
			//-----------------------------
		case WM_PAINT:
			{
				hdc = BeginPaint(hWnd, &ps);
				MyBrush = CreateSolidBrush(RGB(g_BrushColor[COLOR_RED], g_BrushColor[COLOR_GREEN], g_BrushColor[COLOR_BLUE]));
				OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);

				myPen = CreatePen(PS_SOLID, 3, RGB(g_PenColor[COLOR_RED], g_PenColor[COLOR_GREEN], g_PenColor[COLOR_BLUE]));
				oldPen = (HPEN)SelectObject(hdc, myPen);

				//--------------------------
				CFigureBase* pTmpFigure = NULL;
				switch (g_curDrawMode)
				{
					case LINE:		pTmpFigure = g_pLine; break;
					case RECTANGLE: pTmpFigure = g_pRect; break;
					case CIRCLE:	pTmpFigure = g_pCircle; break;
				}
				pTmpFigure->Draw(hdc);
				//--------------------------

				SelectObject(hdc, OldBrush);
				DeleteObject(MyBrush);

				SelectObject(hdc, oldPen);
				DeleteObject(myPen);

				EndPaint(hWnd, &ps);
		
			}
			return 0;
			//-----------------------------
		case WM_DESTROY:
			if (g_pControlFactory != NULL)
			{
				delete g_pControlFactory;
				g_pControlFactory = NULL;
			}

			if(g_figureFactory != NULL)
			{
				delete g_figureFactory;
				g_figureFactory = NULL;
			}

			PostQuitMessage(0);
			return 0;
			//-----------------------------

	}//	switch (iMessage)
	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//==========================================================================