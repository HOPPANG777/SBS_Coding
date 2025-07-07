//============================================
#pragma once
//============================================
#ifndef _MYGAME_H_
#define _MYGAME_H_
//============================================
#include "Global.h"
//============================================
struct BoundingSphere
{
	D3DXVECTOR3 _center;
	float       _radius;
};

struct Ray
{
	D3DXVECTOR3 _origin;
	D3DXVECTOR3 _direction;
};
//============================================
class CMyGame :	public CCore
{
public:
	CMyGame();
	virtual ~CMyGame();

	virtual INT		Init();
	virtual INT		Render2D();
	virtual INT		Render3D();
	virtual INT		FrameMove();
	virtual void	Destroy();
	
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	CDxFont*				m_pDxFont;
	
	//------------------------------------------
	void SetLights();
	D3DLIGHT9 InitDirectionalLight(D3DXVECTOR3* direction, D3DXCOLOR* color);
	D3DMATERIAL9 InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p);	
	const D3DMATERIAL9 WHITE_MTRL = InitMtrl(WHITE, WHITE, WHITE, BLACK, 2.0f);
	const D3DMATERIAL9 RED_MTRL = InitMtrl(RED, RED, RED, BLACK, 2.0f);
	const D3DMATERIAL9 GREEN_MTRL = InitMtrl(GREEN, GREEN, GREEN, BLACK, 2.0f);
	const D3DMATERIAL9 BLUE_MTRL = InitMtrl(BLUE, BLUE, BLUE, BLACK, 2.0f);
	const D3DMATERIAL9 YELLOW_MTRL = InitMtrl(YELLOW, YELLOW, YELLOW, BLACK, 2.0f);
	//------------------------------------------
	//	로그 출력.
	void ShowLog();
	//------------------------------------------
	//	그리드.
	CDxGrid*	m_pGrid;
	//------------------------------------------
	//	주전자 메쉬..
	ID3DXMesh* m_pTeapot = 0;
	//	경계구 메쉬..
	BoundingSphere m_boundSphere;
	//	메쉬 인터페이스..
	ID3DXMesh* m_pSphere = 0;
	D3DXMATRIX m_matWorld;

	Ray CalculatePickingRay(int x, int y);
	void TransformRay(Ray* ray, D3DXMATRIX* T);
	bool RaySphereIntTest(Ray* ray, BoundingSphere* sphere);
	//------------------------------------------

};// class CMyGame :	public CCore

extern CMyGame*	g_pMyGame;
//============================================
#endif // _MYGAME_H_
//============================================