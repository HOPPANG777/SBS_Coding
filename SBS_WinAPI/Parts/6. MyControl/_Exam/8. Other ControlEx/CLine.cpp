//===========================================
#include "CLine.h"
//===========================================
void CLine::Draw(HDC hdc)
{
	MoveToEx(hdc, _posX, _posY, NULL);
	LineTo(hdc, _width, _height);
}
//===========================================