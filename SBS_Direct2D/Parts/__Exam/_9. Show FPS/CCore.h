//========================================================
#pragma once
//========================================================
#ifndef _CORE_H_
#define _CORE_H_
//========================================================
class CDx;
class CCore
{
protected:
	//-------------------------------
	//	win
	HINSTANCE	m_hInst;
	HWND		m_hWnd;
	DWORD		m_dwWinStyle;
	DWORD		m_dwScrWidth;
	DWORD		m_dwScrHeight;
	BOOL		m_bShowCursor;
	BOOL		m_bWindowMode;
	TCHAR		m_tszClassName[256];

	CDx* m_pDx;
	CInputManager *m_pInputManager;

	//	fps	
	//	http://skmagic.tistory.com/298
	TCHAR	m_tszFPS[256];
	//-------------------------------
	static LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);	
	//-------------------------------
	//	etc
	void UpdateFPS();

public:
	//-------------------------------
	CCore();
	~CCore();
	//-------------------------------
	//	core
	BOOL	Create(HINSTANCE hInst);
	INT		Run();
	void	CleanUp();
	HRESULT	Idle();
	LPDIRECT3DDEVICE9 GetDev();
	LPD3DXSPRITE GetSprite();
	//-------------------------------
	//	game
	virtual INT		Init()		{ return 0; }	
	virtual INT		Render()	{ return 0; }
	virtual INT		FrameMove() { return 0; }
	virtual void	Destroy()	{			}
	//-------------------------------
	//	procedure
	virtual	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	//-------------------------------

private:	
	//-------------------------------
	void RegistWinClass();
	HRESULT CreateWindows();	
	HRESULT OnRender();
	//-------------------------------
	

};	//class CCore
//========================================================
#endif	//	_DXCORE_H_
