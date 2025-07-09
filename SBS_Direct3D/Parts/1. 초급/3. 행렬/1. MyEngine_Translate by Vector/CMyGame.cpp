//============================================
#include "Global.h"
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
/*	
	버텍스 버퍼 - 3)
	
		-	버텍스 생성과 초기화..
			-	간단한 삼각형을 렌더링..
*/
HRESULT CMyGame::InitVB()
{
	SVtxRHWD vertices[] =
	{
		{ 150.0f,	50.0f,	0.5f, 1.0f, 0xffff0000 },	//	x, y, z, rhw, color( 0xAARRGGBB )
		{ 250.0f,	250.0f, 0.5f, 1.0f, 0xff00ff00 },
		{ 50.0f,	250.0f, 0.5f, 1.0f, 0xff0000ff },
	};

	if (FAILED(GetDev()->CreateVertexBuffer(
		3 * sizeof(SVtxRHWD),
		0,
		D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT,		
		&m_pVB,
		NULL)))
		return E_FAIL;

	VOID* pVertices;

	if (FAILED(m_pVB->Lock
	(
		0,
		sizeof(vertices),
		(void**)&pVertices,
		0
	)))
		return E_FAIL;

	memcpy(pVertices, vertices, sizeof(vertices));

	m_pVB->Unlock();

	return S_OK;
}
//============================================
INT		CMyGame::Init()
{
	m_pInputManager = new CInputManager();

	m_pDxFont = new CDxFont();
	if (FAILED(m_pDxFont->Create(GetDev(), _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;

	InitVB();

	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render2D()
{
	//	폰트 출력..
	m_pDxFont->Draw(GetSprite(), _T("fps 테스트"), 300, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);
	m_pDxFont->Draw(GetSprite(), m_tszFPS, 0, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

	return S_OK;
}
//============================================
INT		CMyGame::Render3D()
{
	GetDev()->SetStreamSource( 0, m_pVB, 0, sizeof(SVtxRHWD) );	
	GetDev()->SetFVF( D3DFVF_CUSTOMVERTEX );
	GetDev()->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 );

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	UpdateFPS();

	if (m_pInputManager)
	{
		m_pInputManager->FrameMove();

		float speed = 0.05f;
		D3DXVECTOR3 dirLeft(-1, 0, 0);
		D3DXVECTOR3	dirRight(1, 0, 0);
		D3DXVECTOR3	dirUp(0, -1, 0);
		D3DXVECTOR3	dirDown(0, 1, 0);

		if (m_pInputManager->KeyPress(VK_RIGHT))
		{
			SVtxRHWD* pvtx;
			// Lock에서 두번째를 0으로하면
			// 데이터 전부를 가져오게 됨..
			if (FAILED(m_pVB->Lock(0, 0, (void**)&pvtx, 0)))
				return E_FAIL;

			pvtx[0]._pos += dirRight * speed;
			pvtx[1]._pos += dirRight * speed;
			pvtx[2]._pos += dirRight * speed;

			m_pVB->Unlock();
		}

		if (m_pInputManager->KeyPress(VK_LEFT))
		{
			SVtxRHWD* pvtx;
			if (FAILED(m_pVB->Lock(0, 0, (void**)&pvtx, 0)))
				return E_FAIL;

			pvtx[0]._pos += dirLeft * speed;
			pvtx[1]._pos += dirLeft * speed;
			pvtx[2]._pos += dirLeft * speed;

			m_pVB->Unlock();
		}

		if (m_pInputManager->KeyPress(VK_UP))
		{
			SVtxRHWD* pvtx;
			if (FAILED(m_pVB->Lock(0, 0, (void**)&pvtx, 0)))
				return E_FAIL;

			pvtx[0]._pos += dirUp * speed;
			pvtx[1]._pos += dirUp * speed;
			pvtx[2]._pos += dirUp * speed;

			m_pVB->Unlock();
		}

		if (m_pInputManager->KeyPress(VK_DOWN))
		{
			SVtxRHWD* pvtx;
			if (FAILED(m_pVB->Lock(0, 0, (void**)&pvtx, 0)))
				return E_FAIL;

			pvtx[0]._pos += dirDown * speed;
			pvtx[1]._pos += dirDown * speed;
			pvtx[2]._pos += dirDown * speed;

			m_pVB->Unlock();
		}

	}//	if (m_pInputManager)

	return S_OK;
}
//============================================
void	CMyGame::Destroy()
{
	SAFE_DELETE(m_pDxFont);
	SAFE_RELEASE(m_pVB);
}
//============================================
LRESULT CMyGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pInputManager)
		m_pInputManager->MsgProc(hWnd, msg, wParam, lParam);

	return CCore::MsgProc(hWnd, msg, wParam, lParam);
}
//============================================//