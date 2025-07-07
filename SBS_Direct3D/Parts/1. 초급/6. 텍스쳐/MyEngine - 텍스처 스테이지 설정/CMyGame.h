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
	void SetMatrix();
	void SetMaterial();
	void SetLight();
	//------------------------------------------
	//	그리드.
	CDxGrid*	m_pGrid;
	//------------------------------------------
	//	텍스쳐.
	CDxTexture*	m_pTex;
	//	텍스쳐 생성.
	HRESULT	InitTexture();
	//------------------------------------------

};// class CMyGame :	public CCore

extern CMyGame*	g_pMyGame;
//============================================
#endif // _MYGAME_H_
//============================================