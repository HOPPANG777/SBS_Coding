//===========================================================
#pragma once
//===========================================================
#include "CFigureBase.h"
#include <list>
using namespace std;
//===========================================================
enum { F_LINE, F_RECTANGLE,	F_CIRCLE };
//===========================================================
typedef list<CFigureBase*>		FIGURELIST;
typedef FIGURELIST::iterator	FIGURELISTITER;
//===========================================================
class CFigureFactory
{
	FIGURELIST _FigureList;
public:
	~CFigureFactory();
	CFigureBase* Create(int figureType, int posX, int posY, int wid, int hei);
};
//===========================================================