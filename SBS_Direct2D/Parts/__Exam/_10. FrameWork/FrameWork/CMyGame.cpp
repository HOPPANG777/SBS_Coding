//============================================
#include "Global.h"
//============================================
CMyGame* g_pMyGame;
//============================================
CMyGame::CMyGame() { }
//============================================
CMyGame::~CMyGame()	{}
//============================================
INT		CMyGame::Init() { return 0; }
//============================================
INT		CMyGame::Render() { return 0; }
//============================================
INT		CMyGame::FrameMove() { return 0; }
//============================================
void	CMyGame::Destroy() { }
//============================================
LRESULT CMyGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) { return CDxCore::MsgProc(hWnd, msg, wParam, lParam); }
//============================================
HRESULT	CMyGame::OnResetDevice() { return S_OK; }
//============================================
HRESULT	CMyGame::OnLostDevice() { return S_OK; }
//============================================