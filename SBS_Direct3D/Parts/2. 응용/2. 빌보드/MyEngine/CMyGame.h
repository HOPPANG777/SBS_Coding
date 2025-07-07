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
	//------------------------------------------
	//	로그 출력.
	void ShowLog();
	//------------------------------------------
	//	그리드.
	CDxGrid*	m_pGrid;
	//------------------------------------------
	//	물.
	CDxWater* m_pWater = NULL;
	//------------------------------------------
	// 빌보드로 사용할 텍스처
	CDxTexture m_txtrBillboard[4];
	bool m_bisBillboard = TRUE;	// 빌보드처리를 할것인가?
	void DrawBillBoard();
	//------------------------------------------

};// class CMyGame :	public CCore

extern CMyGame*	g_pMyGame;
//============================================
#endif // _MYGAME_H_
//============================================