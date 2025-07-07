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
	
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

	CDxTexture*		m_pDxTexture1;
	CDxTexture*		m_pDxTexture2;
	D3DXVECTOR3		m_vec3Pos1;
	D3DXVECTOR3		m_vec3Pos2;

	CDxFont			m_dxFont;

	bool m_isAABB;
	CCollisionBase* m_pCollBase1;
	CCollisionBase* m_pCollBase2;

	CCollisionAABB* m_pCollAABB1;
	CCollisionAABB* m_pCollAABB2;

	CCollisionSphere* m_pCollSphere1;
	CCollisionSphere* m_pCollSphere2;

};// class CMyGame :	public CCore

extern CMyGame* g_pMyGame;
//============================================
#endif // _MYGAME_H_
//============================================