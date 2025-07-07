//============================================
//	3.	행렬
//	[ 참고 : https://m.blog.naver.com/whdgkks12347/221347100241
//			 https://blog.hexabrain.net/184 ]
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

	/*
		행렬 - 1)
		
			-	트랜스폼 관련
				데이터 선언..
	*/
	float			_scale;
	float			_rotY;
	D3DXVECTOR3		_pos;

};// class CMyGame :	public CCore

extern CMyGame*	g_pApp;
//============================================
#endif // _MYGAME_H_
//============================================