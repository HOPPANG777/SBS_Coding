//============================================
#include "Global.h"
//============================================
CMyGame* g_pMyGame;
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
INT		CMyGame::Init()
{
	if (FAILED(m_dxTxtrTest.Create(GetDev(), _T("texture/myfamily.jpg"))))
		return -1;

	m_pDxTxtrAnim = new CDxTextureAnim(30, 30);
	if (FAILED(m_pDxTxtrAnim->Create(GetDev(), _T("texture/animate.bmp"), 0xFF000000)))
	{
		SAFE_DELETE(m_pDxTxtrAnim);
		return -1;
	}
	m_pDxTxtrAnim->SetImageCenter( D3DXVECTOR3(16, 16, 0) );

	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render()
{
	m_dxTxtrTest.Draw(GetSprite());
	m_pDxTxtrAnim->Draw(GetSprite());

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	D3DXVECTOR3	vcPos(m_dwScrWidth * 0.5f, m_dwScrHeight * 0.5f, 0);
	m_dxTxtrTest.SetPos(vcPos);

	DWORD dwTime = timeGetTime();
	m_pDxTxtrAnim->OnUpdateFrame(dwTime);	

	m_pDxTxtrAnim->SetPos2D(cosf(D3DX_PI * dwTime * 0.0001f), sinf(D3DX_PI * dwTime * 0.0003f));
	D3DXVECTOR3 tmp = m_pDxTxtrAnim->GetPos();
	tmp *= 100.0f;
	tmp += D3DXVECTOR3(300, 300, 0);
	m_pDxTxtrAnim->SetPos2D(tmp.x, tmp.y);

	return 0;

}//	INT		CMyGame::FrameMove()
//============================================
void	CMyGame::Destroy() { SAFE_DELETE(m_pDxTxtrAnim); }
//============================================