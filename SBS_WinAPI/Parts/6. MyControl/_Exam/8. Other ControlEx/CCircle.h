#pragma once
#include "CFigureBase.h"
class CCircle :
	public CFigureBase
{
public:
	virtual void Draw(HDC hdc);
};