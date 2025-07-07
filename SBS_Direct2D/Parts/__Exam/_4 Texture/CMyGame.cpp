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

	return 0;
}
//============================================
INT		CMyGame::Render()
{
	D3DXVECTOR3	vcPos(m_dwScrWidth * 0.5f, m_dwScrHeight * 0.5f, 0);
	m_dxTxtrTest.Draw(GetSprite(), vcPos);

	return 0;
}
//============================================
INT		CMyGame::FrameMove()	{ return 0; }
//============================================
void	CMyGame::Destroy() { m_dxTxtrTest.Destroy(); }
//============================================