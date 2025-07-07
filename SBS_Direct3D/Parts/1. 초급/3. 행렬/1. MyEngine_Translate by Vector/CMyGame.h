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

	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	HRESULT InitVB();

};// class CMyGame :	public CCore

extern CMyGame*	g_pApp;
//============================================
#endif // _MYGAME_H_
//============================================