//============================================================================
#include"CGObject.h"
//============================================================================
CGObject::CGObject(HWND hWnd, HINSTANCE hInst, int bmID, int posX, int posY, int hp, int speed, COLORREF colorKey)
{
	_hWnd = hWnd;
	_hInst = hInst;
	_pBitmap = NULL;
	_bmID = bmID;
	_colorKey = colorKey;

	_hp = hp;
	_speed = speed;
	SetInitPos(posX, posY);
}
//---------------------------------------------
CGObject::~CGObject()
{
	delete _pBitmap;
	_pBitmap = NULL;
}
//---------------------------------------------
bool CGObject::Create()
{
	_pBitmap = new CBitMap(_hWnd, _hInst);
	if (_pBitmap->Load(_bmID))
	{
		_width = _pBitmap->GetWidth();
		_height = _pBitmap->GetHeight();
		return true;
	}

	return false;
}
//---------------------------------------------
void CGObject::OnRender(HDC hMemDC)
{
	_pBitmap->TransDrawForDBuff(hMemDC, _posX, _posY, _colorKey);
}
//---------------------------------------------
void CGObject::DecreaseHP(int pow)
{
	if (!IsActive())
		return;

	_hp -= pow;

	if (_hp <= 0)
		SetActive(0);
}
//---------------------------------------------
void CGObject::SetInitPos(int posX, int posY)
{
	_posX = posX;
	_posY = posY;
}
//---------------------------------------------
bool CGObject::IsCheckCollision(int targetX, int targetY, int targetWidth, int targetHeight)
{
	if (_posX + _width > targetX && targetX + targetWidth > _posX)
		if (_posY + _height > targetY && targetY + targetHeight > _posY)
				return true;

	return false;
}
//============================================================================