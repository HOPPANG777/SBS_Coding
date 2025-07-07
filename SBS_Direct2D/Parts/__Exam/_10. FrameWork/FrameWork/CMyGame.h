//============================================
#pragma once
//============================================
#ifndef _MYGAME_H_
#define _MYGAME_H_
//============================================
#include "Global.h"
//============================================
class CMyGame :	public CDxCore
{
public:
	CMyGame();
	virtual ~CMyGame();

	virtual INT		Init();
	virtual INT		Render();
	virtual INT		FrameMove();
	virtual void	Destroy();

	virtual HRESULT	OnResetDevice();
	virtual HRESULT	OnLostDevice();

	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

};// class CMyGame :	public CDxCore

extern CMyGame* g_pMyGame;
//============================================
#endif // _MYGAME_H_
//============================================