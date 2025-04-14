//================================================
#pragma once
//================================================
#include <Windows.h>
//================================================
class CFigureBase
{
protected:
	int _posX, _posY;
	int _width, _height;

public :
	void SetPos(int x, int y)		{ _posX = x; _posY = y; }
	void SetWidHei(int wid, int hei){ _width = wid; _height = hei; }
	virtual void Draw(HDC hdc) = 0;
};
//================================================