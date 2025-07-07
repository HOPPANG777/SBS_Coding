//============================================
#include "Global.h"
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
//	인덱스 버퍼 4)
//	-	버텍스 버퍼 초기화.
HRESULT CMyGame::InitVB()
{
	SVtxDTxtr vertices[] =
	{
		{ -1,  1, 0 ,0xffffffff, 0, 0 },		/// v0
		{  1,  1, 0 ,0xffffffff, 1, 0 },		/// v1
		{ -1, -1, 0 ,0xffffffff, 0, 1 },		/// v2

		{  1,  1, 0 ,0xffffffff, 1, 0 },		/// v1
		{  1, -1, 0 ,0xffffffff, 1, 1 },		/// v3
		{ -1, -1, 0 ,0xffffffff, 0, 1 },		/// v2
	};

	if (FAILED(GetDev()->CreateVertexBuffer(6 * sizeof(SVtxDTxtr),
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
void CMyGame::SetLights()
{
	// 광원설정 off.
	GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	// 환경광원(ambient light)의 값 설정
	GetDev()->SetRenderState(D3DRS_AMBIENT, 0xFFFFFFFF);
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

	g_pLog = new CLog(ZF_LOG_TARGET_WINDOW);

	m_pTxtrDiffuse.Create(GetDev(), "texture/env2.bmp");
	m_pTxtrNormal.Create(GetDev(), "texture/normal.bmp");


	/// 컬링기능을 끈다.
	GetDev()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	/// Z버퍼기능을 켠다.
	GetDev()->SetRenderState(D3DRS_ZENABLE, TRUE);

	/// 정점에 색깔값이 있으므로, 광원기능을 끈다.
	GetDev()->SetRenderState(D3DRS_LIGHTING, FALSE);

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
void CMyGame::BuildLight()
{
	POINT pt;
	// 커서의 스크린 좌표를 얻는다.
	GetCursorPos(&pt);
	// 스크린 좌표를 클라이언트 좌표계로 바꾼다.
	ScreenToClient(GetHwnd(), &pt);

	m_vLight.x = -(((2.0f * pt.x) / GetScrWidth()) - 1);
	m_vLight.y = -(((2.0f * pt.y) / GetScrHeight()) - 1);
	m_vLight.z = 0.0f;

	//	반지름이 1인 구( Sphere )안에서 조명이 움직이도록 설정..
	//	-	조명 벡터의 길이를 1로 조정.
	if (D3DXVec3Length(&m_vLight) > 1.0f)
		//	-	마우스가 클라이언트 영역을 벗어나는 경우.
		D3DXVec3Normalize(&m_vLight, &m_vLight);
	else
		//	-	마우스가 클라이언트 영역 안에 있는 경우.
		m_vLight.z = sqrtf(1.0f - m_vLight.x * m_vLight.x - m_vLight.y * m_vLight.y);
}
//============================================
DWORD CMyGame::VectortoRGBA(D3DXVECTOR3* v, FLOAT fHeight)
{
	DWORD r = (DWORD)(127.0f * v->x + 128.0f);
	DWORD g = (DWORD)(127.0f * v->y + 128.0f);
	DWORD b = (DWORD)(127.0f * v->z + 128.0f);
	DWORD a = (DWORD)(255.0f * fHeight);

	return((a << 24L) + (r << 16L) + (g << 8L) + (b << 0L));
}
//============================================
void CMyGame::DrawNormalMap()
{
	//	0번 텍스쳐 스테이지에 텍스쳐 고정(법선맵)
	GetDev()->SetTexture(0, m_pTxtrNormal.GetTexture());
	//	1번 텍스쳐 스테이지에 텍스쳐 고정(디퓨즈맵)
	GetDev()->SetTexture(1, m_pTxtrDiffuse.GetTexture());

	//	0번 텍스처 스테이지의 확대 필터
	GetDev()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	//	1번 텍스처 스테이지의 확대 필터
	GetDev()->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//	0번 텍스처 : 0번 텍스처 인덱스 사용
	GetDev()->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	//	1번 텍스처 : 0번 텍스처 인덱스 사용
	GetDev()->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);

	//	벡터를 RGB로 변환..
	DWORD dwFactor = VectortoRGBA(&m_vLight, 0.0f);
	//	RGB로 변환된 벡터를 TextureFactor값으로 등록..
	GetDev()->SetRenderState(D3DRS_TEXTUREFACTOR, dwFactor);

	//	내적 연산..
	GetDev()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DOTPRODUCT3);
	//	텍스처의 RGB..
	GetDev()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//	TextureFactor에 등록된 값( 광원벡터 )..
	GetDev()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);

	//	벽면맵 텍스처와 법선맵을 섞어서 출력
	GetDev()->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MULTIPLYADD);
	//	텍스처 RGB..
	GetDev()->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//	0 스테이지의 연산 결과..
	GetDev()->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);
	//	arg1에 등록된 값으로 알파 연산.
	//GetDev()->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	//	텍스처의 알파값을 arg1으로 등록.
	//GetDev()->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);

	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	GetDev()->SetTransform(D3DTS_WORLD, &mat);

	GetDev()->SetFVF(D3DFVF_CUSTOM);
	GetDev()->SetStreamSource(0, m_pVB, 0, sizeof(SVtxDTxtr));
	GetDev()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
}
//============================================
INT	CMyGame::Render3D()
{
	//	그리드 렌더링.	
	m_pGrid->FrameMove();
	m_pGrid->Render();
	
	DrawNormalMap();

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	UpdateFPS();

	BuildLight();

	ShowLog();

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


	}//	if (m_pInputManager)

	return S_OK;
}
//============================================
void	CMyGame::Destroy()
{
	SAFE_DELETE(g_pLog);
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pDxFont);
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