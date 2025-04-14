//==============================================================
#include "CEnemyManager.h"
#include"resource.h"
#include <time.h>
#include <stdlib.h>
//==============================================================
void CEnemyManager::Create( HWND hWnd, HINSTANCE hInst, CFighter* pTarget)
{
	srand(time(NULL));
	for (int cur = 0; cur < ENEMYCOUNT; ++cur)
	{
		int startX = (rand() % 20) + 980;
		int startY = (rand() % 201) + 200;
		_pEnemies[cur] = new CEnemy(hWnd, hInst, IDB_BABY, startX, startY, 3);
		_pEnemies[cur]->SetBulletBmID(IDB_TOILET);
		_pEnemies[cur]->Create();		
		_pEnemies[cur]->SetTarget(pTarget);
	}
}
//----------------------------------------
void CEnemyManager::OnUpdate()
{
	for (int cur = 0; cur < ENEMYCOUNT; ++cur)
		_pEnemies[cur]->OnUpdate();
}
//----------------------------------------
void CEnemyManager::Spawn()
{
	//	2초마다 적 생성.
	for (int cur = 0; cur < ENEMYCOUNT; ++cur)
	{
		if (!_pEnemies[cur]->IsActive())
		{
			int startX = (rand() % 20) + 980;
			int startY = (rand() % 201) + 200;
			_pEnemies[cur]->SetActive(true);
			_pEnemies[cur]->SetInitPos(startX, startY);
			break;
		}
	}
}
//----------------------------------------
void CEnemyManager::OnRender(HDC hMemDC)
{
	for (int cur = 0; cur < ENEMYCOUNT; ++cur)
		_pEnemies[cur]->OnRender(hMemDC);
}
//----------------------------------------
void CEnemyManager::Destroy()
{
	for (int cur = 0; cur < ENEMYCOUNT; ++cur)
	{
		delete _pEnemies[cur];
		_pEnemies[cur] = NULL;
	};
}
//==============================================================