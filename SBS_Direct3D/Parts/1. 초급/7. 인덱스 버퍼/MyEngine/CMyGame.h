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
	//	인덱스 버퍼 2)
	//	-	인덱스 버퍼 선언.
	LPDIRECT3DINDEXBUFFER9	m_pIB;
	HRESULT InitVB();

	//	인덱스 버퍼 3)
	//	-	인덱스 버퍼 초기화 함수.
	HRESULT	InitIB();
	void SetMatrix();
	//------------------------------------------
	//	그리드.
	CDxGrid*	m_pGrid;
	//------------------------------------------	

};// class CMyGame :	public CCore

extern CMyGame*	g_pMyGame;
//============================================
#endif // _MYGAME_H_
//============================================