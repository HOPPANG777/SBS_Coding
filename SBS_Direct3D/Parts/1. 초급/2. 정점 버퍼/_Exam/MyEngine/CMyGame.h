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
	virtual INT		Render2D() { return S_OK; }
	virtual INT		Render3D();
	virtual INT		FrameMove();
	virtual void	Destroy();
	
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

	/*
		버텍스 버퍼..
		-	버텍스 정보를 가지고 있는
			메모리 블록..
		-	Lock() / Unlock()으로 포인터를
			얻어와서 버텍스 정보를 설정..
	*/
	LPDIRECT3DVERTEXBUFFER9	m_pVB;

	//	버텍스 버퍼 생성 및 초기화..
	HRESULT InitVB();

};// class CMyGame :	public CCore

extern CMyGame*	g_pApp;
//============================================
#endif // _MYGAME_H_
//============================================