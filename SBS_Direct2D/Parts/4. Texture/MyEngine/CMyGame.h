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
	virtual INT		Render();
	virtual INT		FrameMove();
	virtual void	Destroy();

	//	°´Ã¼ ¼±¾ð
	LPDIRECT3DTEXTURE9	m_pD3DTxtr = NULL;

};// class CMyGame :	public CCore

extern CMyGame* g_pMyGame;
//============================================
#endif // _MYGAME_H_
//============================================