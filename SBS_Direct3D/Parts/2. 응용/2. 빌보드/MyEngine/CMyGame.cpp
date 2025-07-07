//============================================
#include "Global.h"
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
//	버텍스 버퍼 4)
//	-	버텍스 버퍼 초기화.
HRESULT CMyGame::InitVB()
{
	SVtxTxtr vertices[] =
	{
		{ -1,  1, 0 ,	0, 0 },		/// v0
		{  1,  1, 0 ,	1, 0 },		/// v1
		{ -1, -1, 0 ,	0, 1 },		/// v2

		{  1,  1, 0 ,	1, 0 },		/// v1
		{  1, -1, 0 ,	1, 1 },		/// v3
		{ -1, -1, 0 ,	0, 1 },		/// v2
	};

	if (FAILED(GetDev()->CreateVertexBuffer(6 * sizeof(SVtxTxtr),
		0, D3DFVF_CUSTOM,
		D3DPOOL_DEFAULT, &m_pVB, NULL)))
	{
		return E_FAIL;
	}

	VOID* pVertices;
	if (FAILED(m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		return E_FAIL;
	memcpy(pVertices, vertices, sizeof(vertices));
	m_pVB->Unlock();

	return S_OK;

}//	HRESULT CMyGame::InitVB()
//============================================
void CMyGame::ShowLog()
{
	static DWORD	nTick = 0;
	static DWORD	nTest = 0;

	/// 1초가 지났는가?
	if (GetTickCount() - nTick > 1000)
	{
		nTick = GetTickCount();

		g_pLog->Log("Test : %d", ++nTest);

		return;
	}	
}
//============================================
INT		CMyGame::Init()
{
	m_pDxFont = new CDxFont();
	if (FAILED(m_pDxFont->Create(GetDev(), _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;
	InitVB();

	m_pGrid = new CDxGrid();
	m_pGrid->Create(GetDev());

	m_pWater = new CDxWater;
	m_pWater->Create(GetDev(), 64, 64, 100, "texture/water1.bmp", "texture/water2.bmp");

	m_txtrBillboard[0].Create(GetDev(), "texture/tree01S.dds");
	m_txtrBillboard[1].Create(GetDev(), "texture/tree02S.dds");
	m_txtrBillboard[2].Create(GetDev(), "texture/tree35S.dds");
	m_txtrBillboard[3].Create(GetDev(), "texture/tex.jpg");


	g_pLog = new CLog(ZF_LOG_TARGET_WINDOW);

	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render2D()
{
	//	폰트 출력.
	m_pDxFont->Draw(GetSprite(), _T("fps 테스트"), 300, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);
	m_pDxFont->Draw(GetSprite(), m_tszFPS, 0, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

	return S_OK;
}
//============================================
void CMyGame::DrawBillBoard()
{	
	// 알파채널을 사용해서 투명텍스처 효과를 낸다
	GetDev()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GetDev()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GetDev()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	GetDev()->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	GetDev()->SetRenderState(D3DRS_ALPHAREF, 0x08);
	GetDev()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	D3DXMATRIXA16	matBillboard;
	D3DXMatrixIdentity(&matBillboard);

	if ( m_bisBillboard )
	{	
		/*	Y축 빌보드.
		matBillboard = *GetCam()->GetBillAxisYMatrix();	//*/

		/*	전체 화면 빌보드.
		matBillboard = *GetCam()->GetBillMatrix();		//*/

	}//	if (m_bisBillboard)

	// 빌보드의 좌표를 바꿔가며 찍는다
	for (int z = 0; z <= 40; z += 5)
	{
		for (int x = 0; x <= 40; x += 5)
		{
			matBillboard._41 = x - 20;
			matBillboard._42 = 1.f;
			matBillboard._43 = z - 20;

			GetDev()->SetFVF(D3DFVF_CUSTOM);
			GetDev()->SetTexture(0, m_txtrBillboard[(x + z) % 4].GetTexture());
			GetDev()->SetTransform(D3DTS_WORLD, &matBillboard);			
			GetDev()->SetStreamSource(0, m_pVB, 0, sizeof(SVtxTxtr));
			GetDev()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
		}
	}
	GetDev()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	GetDev()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);

}//	void CMyGame::DrawBillBoard()
//============================================
INT	CMyGame::Render3D()
{
	//	그리드 렌더링.		
	m_pGrid->Render();
	
	//	물 랜더링.
	m_pWater->Draw();

	//	빌보드 그리기.
	DrawBillBoard();

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	UpdateFPS();

	ShowLog();

	m_pGrid->FrameMove();

	if (GetInput())
	{
		GetInput()->FrameMove();

		bool isForward = GetInput()->KeyPress('W');
		bool isBack = GetInput()->KeyPress('S');
		bool isLeft = GetInput()->KeyPress('A');
		bool isRight = GetInput()->KeyPress('D');
		bool isUp = GetInput()->KeyPress('Q');
		bool isDown = GetInput()->KeyPress('Z');
		bool isMouseRBttnPress = GetInput()->MouseBtnPress(1);
		bool isBoost = GetInput()->KeyPress(VK_LSHIFT);
		D3DXVECTOR3 mouseEps = GetInput()->GetMouseEps();

		GetCam()->FrameMove(isForward, isBack, isLeft, isRight, isUp, isDown, isMouseRBttnPress, mouseEps, isBoost);

		bool isBillBoard = GetInput()->KeyUp('B') || GetInput()->KeyUp('b');
		if (isBillBoard)
			m_bisBillboard = !m_bisBillboard;

	}//	if (m_pInputManager)

	return S_OK;
}
//============================================
void	CMyGame::Destroy()
{
	for (int i = 0; i < 4; ++i)
		m_txtrBillboard[i].Destroy();

	SAFE_DELETE(g_pLog);
	SAFE_DELETE( m_pWater );
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pDxFont);
	//	인덱스 버퍼 7)
	//	-	인덱스 버퍼 정리.	
	SAFE_RELEASE(m_pVB);
}
//============================================
LRESULT CMyGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (GetInput())
		GetInput()->MsgProc(hWnd, msg, wParam, lParam);

	return CCore::MsgProc(hWnd, msg, wParam, lParam);
}
//============================================//