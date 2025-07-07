//============================================
#include "Global.h"
//============================================
CMyGame* g_pMyGame;
//============================================
#define MOVEOFFSET	2.25F
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
INT		CMyGame::Init()
{
	m_pDxTexture1 = new CDxTexture;
	if (FAILED(m_pDxTexture1->Create(GetDev(), "texture/A.png")))
		return -1;

	m_pDxTexture2 = new CDxTexture;
	if (FAILED(m_pDxTexture2->Create(GetDev(), "texture/B.png")))
		return -1;

	if (FAILED(m_dxFont.Create(GetDev(), _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;

	m_vec3Pos1 = D3DXVECTOR3(m_pDxTexture1->GetImageWidth() * 0.5f, m_pDxTexture1->GetImageHeight()*0.5f, 0);
	m_vec3Pos2 = D3DXVECTOR3(m_dwScrWidth * 0.5f, m_dwScrHeight * 0.5f, 0);

	m_pInputManager = new CInputManager();
	m_pInputManager->Create(m_hWnd);

	m_pCheckCollision1 = new CheckCollision();
	m_pCheckCollision1->SetRad(30.f);

	m_pCheckCollision2 = new CheckCollision();
	m_pCheckCollision2->SetRad(30.f);
	m_pCheckCollision2->SetPos(D3DXVECTOR2(m_vec3Pos2.x, m_vec3Pos2.y));

	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render()
{
	m_pDxTexture1->Draw(GetSprite(), m_vec3Pos1);
	m_pDxTexture2->Draw(GetSprite(), m_vec3Pos2);

	//	폰트 출력.
	m_dxFont.Draw(GetSprite(), _T("충돌 테스트"), 0, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	if (m_pInputManager)
	{
		m_pInputManager->FrameMove();

		D3DXVECTOR3 tmpPos = m_vec3Pos1;

		//--------------------------------------
		//	컨트롤
		if (m_pInputManager->KeyPress(VK_RIGHT))
			tmpPos.x += MOVEOFFSET;

		if (m_pInputManager->KeyPress(VK_LEFT))
			tmpPos.x -= MOVEOFFSET;

		if (m_pInputManager->KeyPress(VK_UP))
			tmpPos.y -= MOVEOFFSET;

		if (m_pInputManager->KeyPress(VK_DOWN))
			tmpPos.y += MOVEOFFSET;

		//--------------------------------------
		/*
		//	AABB.
		float halfWidth = m_pDxTexture1->GetImageWidth() * 0.5f;
		float halfHeight = m_pDxTexture1->GetImageHeight() * 0.5f;
		m_pCheckCollision1->SetRect(tmpPos.x - halfWidth, tmpPos.y - halfHeight, m_pDxTexture1->GetImageWidth(), m_pDxTexture1->GetImageHeight());

		halfWidth = m_pDxTexture2->GetImageWidth() * 0.5f;
		halfHeight = m_pDxTexture2->GetImageHeight() * 0.5f;
		m_pCheckCollision2->SetRect(m_vec3Pos2.x - halfWidth, m_vec3Pos2.y - halfHeight, m_pDxTexture2->GetImageWidth(), m_pDxTexture2->GetImageHeight());
		bool isCollision = m_pCheckCollision1->IsCollisionByAABB(m_pCheckCollision2);
		//*/
		//--------------------------------------
		//	구 충돌.
		//*
		D3DXVECTOR2 pos1 = D3DXVECTOR2(tmpPos.x, tmpPos.y);
		m_pCheckCollision1->SetPos(pos1);

		bool isCollision = m_pCheckCollision1->IsCollisionBySphere(m_pCheckCollision2);
		//*/
		//--------------------------------------
		//	충돌 결과에 따른 동작설정.
		if (!isCollision)
		{
			SetWindowText(m_hWnd, "방향키를 누르면 박스가 움직입니다.");
			m_vec3Pos1 = tmpPos;

		}
		else
			SetWindowText(m_hWnd, "충돌!!!");

	}//	if (m_pInputManager)

	return S_OK;
}
//============================================
void	CMyGame::Destroy()
{
	SAFE_DELETE(m_pDxTexture1);
	SAFE_DELETE(m_pDxTexture2);

	SAFE_DELETE(m_pCheckCollision1);
	SAFE_DELETE(m_pCheckCollision2);

	m_dxFont.Destroy();
}
//============================================
LRESULT CMyGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pInputManager)
		m_pInputManager->MsgProc(hWnd, msg, wParam, lParam);

	return CCore::MsgProc(hWnd, msg, wParam, lParam);
}
//============================================//