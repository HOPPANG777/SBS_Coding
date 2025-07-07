//============================================
#pragma once
//============================================
#ifndef _MYGAME_H_
#define _MYGAME_H_
//============================================
#include "Global.h"
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
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	HRESULT InitVB();
	void SetLights();
	//------------------------------------------
	//	로그 출력.
	void ShowLog();
	//------------------------------------------
	//	그리드.
	CDxGrid*	m_pGrid;
	//------------------------------------------	
	CDxTexture m_pTxtrDiffuse;
	//	노멀 맵에 사용될 이미지.
	CDxTexture m_pTxtrNormal;

	// 광원벡터
	D3DXVECTOR3	m_vLight;

	//	조명 연산.
	void BuildLight();

	//	벡터를 RGB로 변환.
	DWORD VectortoRGBA(D3DXVECTOR3* v, FLOAT fHeight);

	//	노멀맵 그리기.
	void DrawNormalMap();

};// class CMyGame :	public CCore

extern CMyGame*	g_pMyGame;
//============================================
#endif // _MYGAME_H_
//============================================