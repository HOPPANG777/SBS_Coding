//==========================================================
#include "CBitMap.h"
//==========================================================
CBitMap::CBitMap(HWND hWnd, HINSTANCE hInst)
{
	_hWnd = hWnd;
	_hInst = hInst;
	_hBitMap = NULL;
}
//-------------------------------
CBitMap::~CBitMap() { DeleteBitmap(); }
//-------------------------------
bool CBitMap::Load(int id)
{
	_hBitMap = LoadBitmap(_hInst, MAKEINTRESOURCE(id));

	if (_hBitMap == NULL)
		return false;

	GetObject(_hBitMap, sizeof(BITMAP), (LPSTR)&_bm);

	return true;
}
//-------------------------------
void CBitMap::Draw(HDC hdc, int posX, int posY)
{
	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC(hdc);
	OldBitmap = (HBITMAP)SelectObject(MemDC, _hBitMap);

	BitBlt(hdc, posX, posY, _bm.bmWidth, _bm.bmHeight, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);
}
//-------------------------------
void CBitMap::DrawForDBuff(HDC hMemDC, int posX, int posY, int width, int height, int srcX, int srcY)
{
	HDC myMemDC;

	//	비트맵을 위한 메모리 DC 생성.
	myMemDC = CreateCompatibleDC(hMemDC);

	//	메모리 DC에 배경 비트맵 적용.
	SelectObject(myMemDC, GetHBitMap());

	//	가상 화면 DC에 메모리 DC 복사.
	BitBlt(hMemDC, posX, posY, width, height, myMemDC, srcX, srcY, SRCCOPY);

	//	메모리 DC 제거.
	DeleteDC(myMemDC);
}
//-------------------------------
//  참고 : 윈도우즈 api 정복( 김상형 저 )
//	TransparentBlt 단점 보완.
//	-	윈도우즈 95에서는 사용 불가.
//	-	속도 느림.
void CBitMap::TransDrawForDBuff(HDC hMemDC, int posX, int posY, COLORREF transColor)
{
	COLORREF cColor;
	HBITMAP bmAndBack, bmAndObject, bmAndMem, bmSave;
	HBITMAP bmBackOld, bmObjectOld, bmMemOld, bmSaveOld;
	HDC		hdcMem, hdcBack, hdcObject, hdcTemp, hdcSave;
	POINT	ptSize;

	hdcTemp = CreateCompatibleDC(hMemDC);
	SelectObject(hdcTemp, GetHBitMap());
	ptSize.x = _bm.bmWidth;
	ptSize.y = _bm.bmHeight;
	DPtoLP(hdcTemp, &ptSize, 1);

	hdcBack = CreateCompatibleDC(hMemDC);
	hdcObject = CreateCompatibleDC(hMemDC);
	hdcMem = CreateCompatibleDC(hMemDC);
	hdcSave = CreateCompatibleDC(hMemDC);

	bmAndBack = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndObject = CreateBitmap(ptSize.x, ptSize.y, 1, 1, NULL);
	bmAndMem = CreateCompatibleBitmap(hMemDC, ptSize.x, ptSize.y);
	bmSave = CreateCompatibleBitmap(hMemDC, ptSize.x, ptSize.y);

	bmBackOld = (HBITMAP)SelectObject(hdcBack, bmAndBack);
	bmObjectOld = (HBITMAP)SelectObject(hdcObject, bmAndObject);
	bmMemOld = (HBITMAP)SelectObject(hdcMem, bmAndMem);
	bmSaveOld = (HBITMAP)SelectObject(hdcSave, bmSave);

	SetMapMode(hdcTemp, GetMapMode(hMemDC));

	BitBlt(hdcSave, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	cColor = SetBkColor(hdcTemp, transColor);

	BitBlt(hdcObject, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCCOPY);

	SetBkColor(hdcTemp, cColor);

	BitBlt(hdcBack, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, NOTSRCCOPY);
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hMemDC, posX, posY, SRCCOPY);
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcObject, 0, 0, SRCAND);
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcBack, 0, 0, SRCAND);
	BitBlt(hdcMem, 0, 0, ptSize.x, ptSize.y, hdcTemp, 0, 0, SRCPAINT);
	BitBlt(hMemDC, posX, posY, ptSize.x, ptSize.y, hdcMem, 0, 0, SRCCOPY);
	BitBlt(hdcTemp, 0, 0, ptSize.x, ptSize.y, hdcSave, 0, 0, SRCCOPY);

	DeleteObject(SelectObject(hdcBack, bmBackOld));
	DeleteObject(SelectObject(hdcObject, bmObjectOld));
	DeleteObject(SelectObject(hdcMem, bmMemOld));
	DeleteObject(SelectObject(hdcSave, bmSaveOld));

	DeleteDC(hdcMem);
	DeleteDC(hdcBack);
	DeleteDC(hdcObject);
	DeleteDC(hdcSave);
	DeleteDC(hdcTemp);
}
//-------------------------------
BOOL CBitMap::DeleteBitmap()
{
	if (_hBitMap == NULL)
		return TRUE;

	if (DeleteObject(_hBitMap))
	{
		_hBitMap = NULL;
		return TRUE;
	}

	MessageBox(_hWnd, "비트맵 제거 실패", "에러", MB_OK);
	return FALSE;
}
//==========================================================