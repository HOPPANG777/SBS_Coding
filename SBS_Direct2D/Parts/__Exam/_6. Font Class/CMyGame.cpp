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
	//	텍스쳐.
	if (FAILED(m_dxTxtrTest.Create(GetDev(), "texture/myfamily.jpg")))
		return -1;
	//	텍스쳐.(애니메이션)
	m_pDxTxtrAnim = new CDxTextureAnim(30, 10);
	if (FAILED(m_pDxTxtrAnim->Create(GetDev(), "texture/animate.bmp", 0xFF000000)))
		return -1;
	m_pDxTxtrAnim->SetCenter(D3DXVECTOR3(16, 16, 0));

	//	폰트.
	m_pDxFont = new CDxFont();
	if (FAILED(m_pDxFont->Create(GetDev(), _T("굴림체"), 20, FW_LIGHT)))
	//if (FAILED(m_pDxFont->Create(GetDev(), _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;

	m_pDxFont->SetPos(0, 0);
	m_pDxFont->SetSize(200, 50);
	m_pDxFont->UpdateDrawArea();
	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render()
{
	//	텍스쳐.	
	m_dxTxtrTest.Draw(GetSprite());

	//	텍스쳐.(애니메이션.)
	m_pDxTxtrAnim->Draw(GetSprite());

	//	폰트.
	m_pDxFont->Draw(GetSprite(), _T("우리 가족 입니다 ^^"));

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	D3DXVECTOR3	vcPos(m_dwScrWidth * 0.5f, m_dwScrHeight * 0.5f, 0);
	m_dxTxtrTest.SetPos(vcPos);

	//	애니메이션 텍스쳐.
	DWORD dwTime = timeGetTime();
	m_pDxTxtrAnim->OnUpdateFrame(GetElapsedTime());

	m_pDxTxtrAnim->SetPos2D(cosf(D3DX_PI * dwTime * 0.0001f), sinf(D3DX_PI * dwTime * 0.0003f));
	D3DXVECTOR3 tmp = m_pDxTxtrAnim->GetPos();
	tmp *= 100.0f;
	tmp += D3DXVECTOR3(400, 300, 0);
	m_pDxTxtrAnim->SetPos2D(tmp.x, tmp.y);

	//	폰트 이동.
	D3DXVECTOR3 tmpPos = m_pDxFont->GetPos();	
	int tmpRange = tmpPos.x + m_pDxFont->GetTextWidth(GetSprite(), _T("우리 가족 입니다 ^^"));
	
	if (_isForward)
	{
		tmpPos.x += 1;

		if (tmpRange > m_dwScrWidth)
			_isForward = !_isForward;
	}
	else
	{
		tmpPos.x -= 1;

		if (tmpPos.x < 0)
			_isForward = !_isForward;
	}

	m_pDxFont->SetPos(tmpPos.x, tmpPos.y);
	m_pDxFont->UpdateDrawArea();


	return S_OK;
}
//============================================
void	CMyGame::Destroy()
{
	SAFE_DELETE( m_pDxTxtrAnim );
	SAFE_DELETE( m_pDxFont );
}
//============================================