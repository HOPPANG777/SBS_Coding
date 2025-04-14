//==================================================================================
#include "CBullet.h"
//==================================================================================
CBullet::CBullet(HWND hWnd, HINSTANCE hInst, int bmID, int posX, int posY, int hp, int dir, int pow) : CGObject(hWnd, hInst, bmID, posX, posY, hp, 20)
{
	SetActive(false);
	_dir = dir;
	_pow = pow;
}
//---------------------------------------------
void CBullet::OnRender(HDC hMemDC)
{
	if (IsActive())
		CGObject::OnRender(hMemDC);
}
//---------------------------------------------
void CBullet::OnUpdate()
{
	if (IsActive())
	{
		switch (_dir)
		{
		case DIR_L_TO_R:
			_posX += _speed;
			if (_posX > 1000)
				SetActive(false);
			break;

		case DIR_R_TO_L:
			_posX -= _speed;
			if (_posX < 0)
				SetActive(false);
			break;
		}
	}
}
//==================================================================================