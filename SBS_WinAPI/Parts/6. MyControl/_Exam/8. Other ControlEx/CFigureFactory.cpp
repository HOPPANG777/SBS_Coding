//=============================================================
#include "CFigureFactory.h"
#include "CLine.h"
#include "CRectangle.h"
#include "CCircle.h"
//=============================================================
CFigureFactory::~CFigureFactory()
{
	FIGURELISTITER iterBegin = _FigureList.begin();
	FIGURELISTITER iterEnd = _FigureList.end();
	FIGURELISTITER iterCur;

	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CFigureBase* pTmp = (*iterCur);
		delete pTmp;
		pTmp = NULL;

	}//	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)

}//	CFigureFactory::~CFigureFactory()
//------------------------------------------------
CFigureBase* CFigureFactory::Create(int figureType, int posX, int posY, int wid, int hei)
{
	CFigureBase* pTmp = NULL;

	switch (figureType)
	{
	case F_LINE:		pTmp = new CLine(); break;
	case F_RECTANGLE:	pTmp = new CRectangle(); break;
	case F_CIRCLE:		pTmp = new CCircle(); break;

	}//	switch (figureType)

	pTmp->SetPos(posX, posY);
	pTmp->SetWidHei(wid, hei);

	_FigureList.push_back(pTmp);

	return pTmp;

}//	CFigureBase* CFigureFactory::Create(HDC hdc, int figureType, int posX, int posY, int wid, int hei)
//=============================================================