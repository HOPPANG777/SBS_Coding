//==================================================================
//	플레이어, 적, 총알등의 공통의 기능 적용을 위한 부모 클래스.
//==================================================================
#pragma once
#include <windows.h>
#include "CBitMap.h"
class CGObject
{
public :
	CGObject(HWND hWnd, HINSTANCE hInst, int bmID, int posX, int posY, int hp, int speed = 10, COLORREF _colorKey = RGB(255, 0, 255));
	virtual ~CGObject();
	virtual bool Create();
	virtual void OnUpdate() = 0;
	virtual void OnRender(HDC hMemDC);
	void SetInitPos(int posX, int posY);
	bool IsCheckCollision(int targetX, int targetY, int targetWidth, int targetHeight);	

	void SetActive( bool isAct ) { _isActive = isAct; }
	bool IsActive() { return _isActive; }	
	int GetPosX() { return _posX; }
	int GetPosY() { return _posY; }
	int GetWidth() { return _width; }
	int GetHeight() { return _height; }
	void DecreaseHP(int pow);

protected:
	CBitMap* _pBitmap;
	int _posX, _posY;
	int _width, _height;	
	int _bmID;
	HWND _hWnd;
	HINSTANCE _hInst;
	COLORREF _colorKey;
	
	int _hp;
	int _speed;

private:
	bool _isActive;
	
	
};