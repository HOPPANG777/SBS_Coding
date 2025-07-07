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

	CDxTexture		m_dxTxtrTest;
	CDxTextureAnim*	m_pDxTxtrAnim;
	CDxFont*		m_pDxFont;
	bool _isForward = true;
	//	입력 관련 메시지.
	TCHAR			m_tszMouseMsg[128];
	TCHAR			m_tszKbdMsg[128];
	TCHAR			m_tszMouseWheelMsg[128];

	const DWORD PRESSINGTIME = 3000;
	bool		_isLBttnPress = false;
	DWORD		_dwLBttnClickTime;	
	CDxFont*	_pDxFontLBttnMsg;
	TCHAR		_tszLBttnMsg[128];

};// class CMyGame :	public CCore

extern CMyGame* g_pMyGame;
//============================================
#endif // _MYGAME_H_
//============================================