//==============================================================
#include "CDrawManager.h"
//==============================================================
CDrawManager::CDrawManager(int offScrWidth, int offScrHeight)
{
	_offScrWidth = offScrWidth;
	_offScrHeight = offScrHeight;

}//	CDrawManager::CDrawManager(int offScrWidth, int offScrHeight)
//==============================================================
HDC CDrawManager::BeginDraw(HWND hWnd)
{
	//	화면 DC 가져오기..
	_hdc = BeginPaint(hWnd, &_ps);

	//	메모리 DC 생성..
	_hMemDC = CreateCompatibleDC(_hdc);

	//	오프스크린 비트맵 생성..
	_hOffScrBitmap = CreateCompatibleBitmap(_hdc, _offScrWidth, _offScrHeight);

	//	메모리 DC + 오프스크린 비트맵 = 가상 화면..
	_hOldBitmap = (HBITMAP)SelectObject(_hMemDC, _hOffScrBitmap);

	//	가상 화면 전달..
	return _hMemDC;

}//	HDC CDrawManager::BeginDraw(HWND hWnd)
//==============================================================
void CDrawManager::EndDraw(HWND hWnd)
{
	BitBlt(_hdc, 0, 0, _offScrWidth, _offScrHeight, _hMemDC, 0, 0, SRCCOPY);
	SelectObject(_hMemDC, _hOldBitmap);
	DeleteObject(_hOffScrBitmap);
	DeleteDC(_hMemDC);
	EndPaint(hWnd, &_ps);

}//	void CDrawManager::EndDraw(HWND hWnd)
//==============================================================