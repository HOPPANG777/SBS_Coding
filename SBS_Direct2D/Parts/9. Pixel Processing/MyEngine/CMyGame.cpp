//============================================
#include "Global.h"
//============================================
CMyGame* g_pMyGame;
//============================================
#define MOVEOFFSET 0.25f
//============================================
CMyGame::CMyGame()
{
	ZeroMemory(m_tszMessage, sizeof(m_tszMessage));

}//	CMyGame::CMyGame()
//============================================
CMyGame::~CMyGame()	{}
//============================================
INT		CMyGame::Init()
{
	m_pDxTexture1 = new CDxTexture;
	if (FAILED(m_pDxTexture1->Create(m_pD3DDevice, "texture/myfamily.jpg", 0xFF000000, D3DFMT_A8R8G8B8)))
		return -1;
	
	m_pDxTexture1->SetEffect_ColorShift(0.5f, 0.5f, 0.5f);
	
	//m_pDxTexture1->SetEffect_Mono();
	
	//m_pDxTexture1->SetEffect_InverseColor();
	
	//m_pDxTexture1->SetEffect_Gamma();
	//m_pDxTexture1->SetEffect_Gamma(0.1f, 0.1f, 0.1f);
	//m_pDxTexture1->SetEffect_Gamma(0.5f, 0.5f, 1.f);
	 
	//m_pDxTexture1->SetEffect_BitPlannerSlicing(3);

	m_pDxTexture2 = new CDxTexture;
	if (FAILED(m_pDxTexture2->Create(m_pD3DDevice, "texture/myfamily.jpg", 0xFF000000, D3DFMT_A1R5G5B5)))
		return -1;
	
		
	if (FAILED(m_dxFont.Create(m_pD3DDevice, _T("궁서체"), 20, FW_BOLD)))	
		return E_FAIL;
	
	m_vec3Pos1 = D3DXVECTOR2(150, 30);
	m_vec3Pos2 = D3DXVECTOR2(450, 30);

	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render()
{
	m_pDxSpriteManager->Begin();
	
	RECT	rc;

	m_pDxTexture1->GetImageRect(&rc);
	m_pDxSpriteManager->Draw(m_pDxTexture1->GetTexture(), &rc, NULL, NULL, 0, &m_vec3Pos1, D3DXCOLOR(1, 1, 1, 1));

	m_pDxTexture2->GetImageRect(&rc);
	m_pDxSpriteManager->Draw(m_pDxTexture2->GetTexture(), &rc, NULL, NULL, 0, &m_vec3Pos2, D3DXCOLOR(1, 1, 1, 1));

	sprintf(m_tszMessage, _T("%d 바이트"), m_pDxTexture1->GetBytePerPixel());
	m_dxFont.Draw(m_pDxSpriteManager->GetSprite(), m_tszMessage, m_vec3Pos1.x, m_vec3Pos1.y + 450, 300, 50, D3DXCOLOR(1.f, 1.f, 0.f, 1.f), DT_LEFT);

	sprintf(m_tszMessage, _T("%d 바이트"), m_pDxTexture2->GetBytePerPixel());
	m_dxFont.Draw(m_pDxSpriteManager->GetSprite(), m_tszMessage, m_vec3Pos2.x, m_vec3Pos2.y + 450, 300, 50, D3DXCOLOR(1.f, 1.f, 0.f, 1.f), DT_LEFT);

	m_pDxSpriteManager->End();
	
	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	if (m_pInputManager)
		m_pInputManager->FrameMove();

	return 0;

}//	INT		CMyGame::FrameMove()
//============================================
void	CMyGame::Destroy()
{
	SAFE_DELETE(m_pDxTexture1);
	SAFE_DELETE(m_pDxTexture2);

	m_dxFont.Destroy();
}
//============================================
LRESULT CMyGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pInputManager)
		m_pInputManager->MsgProc(hWnd, msg, wParam, lParam);

	return CDxCore::MsgProc(hWnd, msg, wParam, lParam);
}
//============================================
/*
	Q)	FPS를 측정하도록 합니다..
		
		팁 )	FPS = Frame Per Seconds..
				
				원리)	1초동안 몇프레임이 호출되었는가??
						->	1초 동안 FrameMove()함수가 몇회 호출되었는가??
				
				방식)	FrameMove()함수 내부에서 함수가 호출될때마다 
						카운트 변수를 이용하여 호출횟수를 카운트 한다..

						FrameMove()함수 내부에서 시간을 측정하여
						1초가 지날때마다 호출횟수를 현재 시간으로 
						나누면 FPS가 됨..

						timeGetTime()함수처럼 시간정보를 관리하는 함수 사용...
*/
//============================================