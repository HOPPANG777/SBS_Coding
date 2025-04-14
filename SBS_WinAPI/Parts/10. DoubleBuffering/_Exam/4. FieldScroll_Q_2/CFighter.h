//==========================================================
//	플레이어 클래스.
//==========================================================
#pragma once
//==========================================================
#include "CGObject.h"

//	-	[ 클래스 전방선언 ]
//		[ 참고 : https://eastroot1590.tistory.com/entry/C-Reference-%ED%81%B4%EB%9E%98%EC%8A%A4-%EC%A0%84%EB%B0%A9%EC%84%A0%EC%96%B8class-forward-declaration ]
// 
//		-	정의
//			-	포인터 객체를 선언할 때 객체를 선언하기 전에 필요한 클래스를 명시..
//	
//		-	효과..
//			-	헤더파일의 중복 방지..
//			-	컴파일 시간 단축..
//				-	헤더파일에서 다른 헤더파일을 포함시키는 행위는 컴파일 시간을 증가..
class CEnemy;
class CBullet;
//==========================================================
#define BULLETCOUNT 5
class CFighter : public CGObject
{
public:
	CFighter(HWND hWnd, HINSTANCE hInst, int bmID, int posX, int posY, int hp);
	virtual ~CFighter();
	virtual bool Create();
	virtual void OnRender(HDC hMemDC);
	virtual void OnUpdate();
	void SetBulletBmID(int id) { _bulletBmID = id; }
	void SetTargets(CEnemy** pEnemies, int count);

protected:
	CBullet* _pBullets[BULLETCOUNT];
	int _bulletBmID;
	CEnemy** _pEnemies;
	int _enemyCount;

};
//==========================================================