//==========================================================
//	ÃÑ¾Ë ·»´õ¸µ ¹× ÀÌµ¿ Ã³¸®..
//==========================================================
#pragma once
//==========================================================
#include "CGObject.h"
//==========================================================
enum
{
	DIR_L_TO_R,
	DIR_R_TO_L,
};

class CBullet : public CGObject
{
public :	
	CBullet(HWND hWnd, HINSTANCE hInst, int bmID, int posX, int posY, int hp, int dir, int pow);
	virtual ~CBullet() {};
	virtual void OnRender(HDC hMemDC);
	virtual void OnUpdate();
	int GetPow() { return _pow; }
private:
	int _pow;
	int _dir;
};
//==========================================================