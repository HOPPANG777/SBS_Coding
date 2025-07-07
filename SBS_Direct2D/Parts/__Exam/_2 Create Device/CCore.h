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
		//	win..
		HINSTANCE	m_hInst;
		HWND		m_hWnd;
		DWORD		m_dwWinStyle;
		DWORD		m_dwScrWidth;
		DWORD		m_dwScrHeight;
		BOOL		m_bShowCursor;
		BOOL		m_bWindowMode;
		TCHAR		m_tszClassName[256];

		//	dx..
		CDx* m_pDx;

		static LRESULT WINAPI WndProc(HWND, UINT, WPARAM, LPARAM);
		void	CleanUp();
		HRESULT	Idle();	
		//-------------------------------

	public:
		//-------------------------------
		CCore();
		~CCore();
		//-------------------------------
		//	core..
		BOOL	Create(HINSTANCE hInst);
		INT		Run();

	protected:
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
