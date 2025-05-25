//====================================================
#include "CView.h"
//====================================================
CView g_View;
CViewFuncPt fpCViewGlobal;
//====================================================
void CView::OnCreate() { MessageBox(_hWnd, TEXT("OnCreate"), TEXT("Custom MFC"), MB_ICONEXCLAMATION | MB_OK); }
//====================================================
void CView::OnDraw()
{
	HDC         hdc;
	PAINTSTRUCT ps;
	RECT        rect;

	hdc = BeginPaint(_hWnd, &ps);
	GetClientRect(_hWnd, &rect);
	DrawText(hdc, TEXT("OnDraw"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	EndPaint(_hWnd, &ps);

}//	void CView::OnDraw()
 //====================================================
void CView::OnLButtonDown() { MessageBox(_hWnd, TEXT("OnLButtonDown"), TEXT("Custom MFC"), MB_ICONEXCLAMATION | MB_OK); }
//====================================================
void CView::OnDestroy()
{
	MessageBox(_hWnd, TEXT("OnDestroy"), TEXT("Custom MFC"), MB_ICONEXCLAMATION | MB_OK);
	PostQuitMessage(0);	
}
//====================================================
MessageMap CView::messageMap[] =
{
	{ WM_CREATE,		&CView::OnCreate },
	{ WM_PAINT,			&CView::OnDraw },
	{ WM_LBUTTONDOWN,	&CView::OnLButtonDown },
	{ WM_DESTROY,		&CView::OnDestroy },

	{ 0,NULL }
};
//====================================================
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	int i = 0;
	while (CView::messageMap[i].iMsg != 0)
	{
		if (iMsg == CView::messageMap[i].iMsg)
		{
			//	참고 :	함수포인터
			//			https://hombody.tistory.com/39
			/*
				static 이 아닌 멤버함수는
				인스턴스를 생성하기 전까지는
				메모리에 존재하지 않으므로
				인스턴스가 필요함.
			*/
			fpCViewGlobal = CView::messageMap[i]._fp;
			(g_View.*fpCViewGlobal)();

			break;
		}
		++i;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);

}//LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
//====================================================