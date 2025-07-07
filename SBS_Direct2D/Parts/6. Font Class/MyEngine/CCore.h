//========================================================
#pragma once
//========================================================
#ifndef _DXCORE_H_
#define _DXCORE_H_
//========================================================
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

	static LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
	void	CleanUp();
	HRESULT	Idle();
	//-------------------------------
	//	d3d
	LPDIRECT3D9				m_pD3D;
	D3DPRESENT_PARAMETERS	m_D3DPp;
	LPDIRECT3DDEVICE9		m_pD3DDevice;
	//-------------------------------
	//	https://jsalmightys01.tistory.com/41
	LPD3DXSPRITE			m_pD3DSprite = NULL;			// 2D Sprite

public:
	//-------------------------------
	CCore();
	~CCore();
	//-------------------------------
	//	core
	BOOL	Create(HINSTANCE hInst);
	INT		Run();	
	//-------------------------------
	//	game
	virtual INT		Init()		{ return S_OK; }
	virtual INT		Render()	{ return S_OK; }
	virtual INT		FrameMove() { return S_OK; }
	virtual void	Destroy()	{			}
	//-------------------------------
	//	procedure
	virtual	LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);
	//-------------------------------


private:
	//-------------------------------
	void RegistWinClass();
	HRESULT CreateWindows();
	HRESULT CreateDX();
	HRESULT OnRender();
	//-------------------------------
	

};	//class CCore
//========================================================
#endif	//	_DXCORE_H_
