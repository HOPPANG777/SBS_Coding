//==========================================================
#include "CBitMap.h"
//==========================================================
CBitMap::CBitMap(HWND hWnd)
{
	_hWnd = hWnd;
	_hBitMap = NULL;
}
//-------------------------------
CBitMap::~CBitMap() { DeleteBitmap(); }
//-------------------------------
bool CBitMap::Load( HINSTANCE hInst, int id )
{
	_hBitMap = LoadBitmap( hInst, MAKEINTRESOURCE( id ) );

	if (_hBitMap == NULL)
		return false;

	return true;

}//	bool CBitMap::Load( HINSTANCE hInst, int id )
//-------------------------------
void CBitMap::Draw(HDC hdc, int posX, int posY)
{
	if (_hBitMap == NULL)
		return;

	HDC MemDC;
	HBITMAP OldBitmap;
	int bx, by;
	BITMAP bit;

	MemDC = CreateCompatibleDC( hdc );
	OldBitmap = (HBITMAP)SelectObject(MemDC, _hBitMap);

	GetObject(_hBitMap, sizeof(BITMAP), &bit);
	bx = bit.bmWidth;
	by = bit.bmHeight;

	BitBlt(hdc, posX, posY, bx, by, MemDC, 0, 0, SRCCOPY);

	SelectObject(MemDC, OldBitmap);
	DeleteDC(MemDC);

}//	void CBitMap::Draw(HDC hdc, int posX, int posY)
//-------------------------------
BOOL CBitMap::DeleteBitmap()
{
	//	비트맵 제거.
	if (_hBitMap == NULL)
		return TRUE;

	if (DeleteObject(_hBitMap))
	{
		_hBitMap = NULL;
		return TRUE;
	}

	MessageBox(_hWnd, "비트맵 제거 실패", "에러", MB_OK);
	return FALSE;

}//	BOOL CBitMap::DeleteBitmap()
//==========================================================