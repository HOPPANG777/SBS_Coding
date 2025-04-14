//==========================================================
//	적 생성 및 정보 갱신..
//==========================================================
#pragma once
//==========================================================
#include "CEnemy.h"
//==========================================================
#define		ENEMYCOUNT		20
#define		ENEMYSPAWNTIME	2000
//==========================================================
class CEnemyManager
{	
	CEnemy*		_pEnemies[ENEMYCOUNT];
public:
	~CEnemyManager() { Destroy(); }
	void Create( HWND hWnd, HINSTANCE hInst, CFighter* pTarget);
	void OnUpdate();
	void Spawn();
	void OnRender(HDC hMemDC);
	void Destroy();
	CEnemy** GetEnemies() { return _pEnemies; }
	int GetEnemyCount() { return ENEMYCOUNT; }
};
//==========================================================