//============================================
//	4.	광원.
//	[ 참고 : https://docs.google.com/viewer?a=v&pid=sites&srcid=ZGVmYXVsdGRvbWFpbnwzZGdhbWVwcm9ncmFtfGd4OjE5MDQ1YjM5OGVmMmFjMGI
//			 https://openhead.tistory.com/entry/%EA%B4%91%EC%9B%90-%EC%B4%88%EA%B8%B0%ED%99%94
//			 https://euncero.tistory.com/264
//			 https://sites.google.com/site/ub8566/3d/05-gwang-won
//			 https://cuca.tistory.com/entry/%EC%A3%BC%EB%B3%80%EA%B4%91ambient-%EB%B6%84%EC%82%B0%EA%B4%91diffuse-%EB%B0%98%EC%82%AC%EA%B4%91specular
//			 https://blog.naver.com/websearch/221386795385
//			 https://devbot.tistory.com/entry/%EA%B4%91%EC%9B%90 ]
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
	//	광원 - 2)
	//	-	재질, 조명 설정..
	void SetMaterial();
	void SetLight();
	//------------------------------------------

};// class CMyGame :	public CCore

extern CMyGame*	g_pApp;
//============================================
#endif // _MYGAME_H_
//============================================