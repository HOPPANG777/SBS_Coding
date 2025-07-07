//======================================================
#pragma once
#ifndef __CHECK_COLLISION_H__
#define __CHECK_COLLISION_H__
//======================================================
// 참고 : https://blog.naver.com/jerrypoiu/221172549241
//======================================================
class CheckCollision
{
	D3DXVECTOR2 _myPos;

	RECT _myRect;
	float _myRad;

public:
	CheckCollision()
	{
		_myPos = D3DXVECTOR2(0, 0);

		_myRect = RECT{ 0,0,0,0 };
		_myRad = 0.f;
	}
	D3DXVECTOR2 GetPos() { return _myPos; }
	void SetPos(D3DXVECTOR2 pos) { _myPos = pos; }

	//	AABB ( 박스 충돌 )
	bool IsCollisionByAABB(CheckCollision* pTmpCheck);
	RECT GetRect() { return _myRect; }
	void SetRect(int left, int top, int width, int height);

	//	Sphere ( 구 충돌 )
	bool IsCollisionBySphere(CheckCollision* pTmpCheck);	
	void SetRad(float rad) { _myRad = rad; }
	float GetRad() { return _myRad; }
};
//======================================================
#endif __CHECK_COLLISION_H__
//======================================================//