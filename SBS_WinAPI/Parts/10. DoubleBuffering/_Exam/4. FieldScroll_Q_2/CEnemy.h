//==========================================================
//	적 클래스.
//	-	플레이어의 기능을 기반으로 주요 기능들 오버 라이딩..
//==========================================================
#pragma once
//==========================================================
#include "CFighter.h"
//==========================================================
#define SHOTTIME 1500
class CEnemy :	public CFighter
{
public:
	CEnemy(HWND hWnd, HINSTANCE hInst, int bmID, int posX, int posY, int hp);
	virtual ~CEnemy() {};
	virtual bool Create();
	virtual void OnRender(HDC hMemDC);
	virtual void OnUpdate();
	void SetTarget(CFighter* pTarget) { _pTarget = pTarget; }
private:
	DWORD _startTickCount;
	CFighter* _pTarget;

};
//==========================================================