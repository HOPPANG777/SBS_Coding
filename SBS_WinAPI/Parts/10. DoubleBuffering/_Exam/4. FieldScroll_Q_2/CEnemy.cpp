//==========================================================
#include "CEnemy.h"
#include "CBullet.h"
//==========================================================
CEnemy::CEnemy(HWND hWnd, HINSTANCE hInst, int bmID, int posX, int posY, int hp) : CFighter(hWnd, hInst, bmID, posX, posY, hp)
{
	_startTickCount = 0;
	SetActive(false);
}
//---------------------------------------------
bool CEnemy::Create()
{
	CGObject::Create();

	//	총알 생성..
	for (int cur = 0; cur < BULLETCOUNT; ++cur)
	{
		_pBullets[cur] = new CBullet(_hWnd, _hInst, _bulletBmID, 0, 0, 1, DIR_R_TO_L,1);
		_pBullets[cur]->Create();
	}

	//	총알 발사 시간 초기화..
	_startTickCount = GetTickCount();

	return true;

}//	bool CEnemy::Create()
//---------------------------------------------
void CEnemy::OnRender(HDC hMemDC) { CFighter::OnRender(hMemDC); }
//---------------------------------------------
void CEnemy::OnUpdate()
{
	//	총알 처리..
	for (int cur = 0; cur < BULLETCOUNT; ++cur)
	{
		//	총알 이동 정보 갱신..
		_pBullets[cur]->OnUpdate();

		//	총알과 충돌 체크..
		if ( _pTarget->IsActive() && _pBullets[cur]->IsActive() )
		{
			bool isCollision = _pBullets[cur]->IsCheckCollision(_pTarget->GetPosX(), _pTarget->GetPosY(), _pTarget->GetWidth(), _pTarget->GetHeight());
			if (isCollision)
			{
				_pTarget->DecreaseHP(_pBullets[cur]->GetPow());
				_pBullets[cur]->SetActive(false);
			}
		}		
	}
	
	if (!IsActive())
		return;

	DWORD curTickCount = GetTickCount();
	DWORD elapsedCount = curTickCount - _startTickCount;

	//	총알 발사..
	if (elapsedCount > SHOTTIME)
	{
		for (int cur = 0; cur < BULLETCOUNT; ++cur)
		{
			if (!_pBullets[cur]->IsActive())
			{
				_pBullets[cur]->SetInitPos(_posX - 20, _posY);
				_pBullets[cur]->SetActive(true);
				break;
			}
		}

		_startTickCount = GetTickCount();

	}//	if (elapsedCount > SHOTTIME)

	
	//	적기와 충돌체크..
	if (_pTarget->IsActive())
	{
		bool isCollision = IsCheckCollision(_pTarget->GetPosX(), _pTarget->GetPosY(), _pTarget->GetWidth(), _pTarget->GetHeight());
		if (isCollision)
		{
			_pTarget->DecreaseHP(1);
			SetActive(false);
		}
	}

	_posX -= _speed;
	
}//	void CEnemy::OnUpdate()
//==========================================================