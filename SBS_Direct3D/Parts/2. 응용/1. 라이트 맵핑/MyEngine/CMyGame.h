//============================================
//	1. 라이트 맵핑
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

	CDxTexture _tex1;
	CDxTexture _tex2;

	//------------------------------------------
	//	그리드.
	CDxGrid*	m_pGrid;
	//------------------------------------------	

};// class CMyGame :	public CCore

extern CMyGame*	g_pMyGame;
//============================================
#endif // _MYGAME_H_
//============================================
/*
	[ 참고 ]
		https://m.blog.naver.com/sipack7297/220424401873
		https://m.blog.naver.com/jsjhahi/201921597
		https://gamedev.stackexchange.com/questions/105889/what-causes-aliasing/105965#105965
		https://docs.unity3d.com/kr/2018.4/Manual/PostProcessing-Antialiasing.html
		https://m.blog.naver.com/sipack7297/220424403817
		https://m.blog.naver.com/sipack7297/220424409076
		https://docs.microsoft.com/en-us/windows/win32/direct3d9/d3dtexturestagestatetype
		https://blog.naver.com/is1040/20201534550
		https://blog.naver.com/jsjhahi/200889870
		http://telnet.or.kr/directx/graphics/reference/d3d/enums/d3dtexturestagestatetype.htm
*/
//============================================