//==========================================================
#include"CFighter.h"
#include "CBullet.h"
#include "CEnemy.h"
//==========================================================
CFighter::CFighter(HWND hWnd, HINSTANCE hInst, int bmID, int posX, int posY, int hp) : CGObject(hWnd, hInst, bmID, posX, posY, hp)
{
	SetActive(true);
}
//---------------------------------------------
CFighter::~CFighter()
{
	for (int cur = 0; cur < BULLETCOUNT; ++cur)
	{
		delete _pBullets[cur];
		_pBullets[cur] = NULL;
	}
}
//---------------------------------------------
bool CFighter::Create()
{
	CGObject::Create();

	for (int cur = 0; cur < BULLETCOUNT; ++cur)
	{
		_pBullets[cur] = new CBullet(_hWnd, _hInst, _bulletBmID, 0, 0, 1, DIR_L_TO_R, 1);
		_pBullets[cur]->Create();
	}

	return true;
}
//---------------------------------------------
void CFighter::SetTargets(CEnemy** pEnemies, int count)
{
	_pEnemies = pEnemies;
	_enemyCount = count;
}
//---------------------------------------------
void CFighter::OnUpdate()
{
	for (int cur = 0; cur < BULLETCOUNT; ++cur)
	{
		_pBullets[cur]->OnUpdate();
		
		for (int curEnemy = 0; curEnemy < _enemyCount; ++curEnemy)
		{
			if (_pEnemies[curEnemy]->IsActive() && _pBullets[cur]->IsActive())
			{
				bool isCollision = _pEnemies[curEnemy]->IsCheckCollision(_pBullets[cur]->GetPosX(), _pBullets[cur]->GetPosY(), _pBullets[cur]->GetWidth(), _pBullets[cur]->GetHeight());
				if (isCollision)
				{
					_pEnemies[curEnemy]->DecreaseHP( _pBullets[cur]->GetPow() );
					_pBullets[cur]->SetActive(false);
				}
			}		
		}
	}

	if (!IsActive())
		return;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		_posY -= _speed;
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		_posY += _speed;

	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		_posX -= _speed;
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		_posX += _speed;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		for (int cur = 0; cur < BULLETCOUNT; ++cur)
		{
			if (!_pBullets[cur]->IsActive())
			{
				_pBullets[cur]->SetInitPos(_posX + 20, _posY);
				_pBullets[cur]->SetActive(true);
				break;
			}
		}
	}
}
//---------------------------------------------
void CFighter::OnRender(HDC hMemDC)
{
	for (int cur = 0; cur < BULLETCOUNT; ++cur)
		_pBullets[cur]->OnRender(hMemDC);

	if (!IsActive())
		return;

	CGObject::OnRender(hMemDC);

}
//==========================================================