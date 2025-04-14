//===========================================
#include "CRectangle.h"
//===========================================
void CRectangle::Draw(HDC hdc)
{
	Rectangle(hdc, _posX, _posY, _width, _height);
}
//===========================================