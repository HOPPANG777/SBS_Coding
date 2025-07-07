//============================================
#include "Global.h"
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
//	버텍스 버퍼 초기화.
HRESULT CMyGame::InitVB()
{
	SVtxDTxtr vertices[] =
	{
		{ -1,  1, 0 , 0xffffffff, 0, 0 },		/// v0
		{  1,  1, 0 , 0xffffffff, 1, 0 },		/// v1
		{ -1, -1, 0 , 0xffffffff, 0, 1 },		/// v2
		{  1, -1, 0 , 0xffffffff, 1, 1 },		/// v3
	};

	if (FAILED(GetDev()->CreateVertexBuffer(4 * sizeof(SVtxDTxtr),
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
void CMyGame::SetMatrix()
{
	//---------------------------------
	// 월드 변환
	//---------------------------------
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationY(&matWorld, timeGetTime() / 500.0f);	// 회전행렬
	GetDev()->SetTransform(D3DTS_WORLD, &matWorld);			// 디바이스의 월드 행렬을 설정한다.

}//	void CMyGame::SetMatrix()
//============================================
INT		CMyGame::Init()
{
	m_pDxFont = new CDxFont();
	if (FAILED(m_pDxFont->Create(GetDev(), _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;

	InitVB();

	if (FAILED(_tex1.Create(GetDev(), "texture/env2.bmp")))
		return E_FAIL;

	if (FAILED(_tex2.Create(GetDev(), "texture/spotlite.bmp")))
		return E_FAIL;

	m_pGrid = new CDxGrid();
	m_pGrid->Create(GetDev());

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
INT		CMyGame::Render3D()
{
	//	그리드 렌더링.
	m_pGrid->FrameMove();
	m_pGrid->Render();


	//	월드 행렬 설정.
	SetMatrix();

	// 0번 텍스쳐 스테이지에 텍스쳐 고정(벽면)
	GetDev()->SetTexture(0, _tex1.GetTexture());
	// 1번 텍스쳐 스테이지에 텍스쳐 고정(라이트맵)
	GetDev()->SetTexture(1, _tex2.GetTexture());

	// 0번 텍스처 스테이지 : 0번 텍스처 인덱스 사용
	GetDev()->SetTextureStageState(0, D3DTSS_TEXCOORDINDEX, 0);
	// 1번 텍스처 스테이지 : 0번 텍스처 인덱스 사용
	GetDev()->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0);
	// 0번 텍스처 스테이지의 확대 필터
	GetDev()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	/*
		텍스처 필터링 방식.
		-	D3DTEXF_POINT			:	근접점 샘플링.
			D3DTEXF_LINEAR			:	선형 필터링.
			D3DTEXF_ANISOTROPIC		:	이방성 필터링.
	*/
	// 1번 텍스처 스테이지의 확대 필터
	GetDev()->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//	D3DTSS_COLOROP
	//	-	해당 스테이지의 컬러값 처리방식 설정.
	//	D3DTOP_SELECTARG1
	//	-	첫번째 색상 인자값으로 선택.
	//	0번 스테이지의 첫번째 색상 인자값 선택.
	GetDev()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);

	//	D3DTSS_COLORARG1
	//	-	첫번째 색상 인자값 설정.
	//	D3DTA_TEXTURE
	//	-	텍스쳐 데이터 설정.	
	//	0번 스테이지의 첫번째 색상 인자값을 텍스처 데이터로 설정.
	GetDev()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

	//	MODULATE연산으로 색깔을 섞음
	GetDev()->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
	//	1번 스테이지의 첫번째 색상 인자값을 텍스처 데이터로 설정.
	GetDev()->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	//	두번째 색상 인자값을 이전 스테이지의 연산 결과.
	GetDev()->SetTextureStageState(1, D3DTSS_COLORARG2, D3DTA_CURRENT);

	// 현재 은면제거 상태 확인.
	DWORD dCullMode = 0;
	GetDev()->GetRenderState(D3DRS_CULLMODE, &dCullMode);

	// 은면제거 비활성화
	GetDev()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 정점을 디바이스에 연결
	GetDev()->SetStreamSource(0, m_pVB, 0, sizeof(SVtxDTxtr));
	// 정점 포멧을 설정
	GetDev()->SetFVF(D3DFVF_CUSTOM);

	// 렌더링
	GetDev()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// 은면 제거 상태 복구.
	GetDev()->SetRenderState(D3DRS_CULLMODE, dCullMode);

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	UpdateFPS();

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
		D3DXVECTOR3 mouseEps = GetInput()->GetMouseEps();

		GetCam()->FrameMove(isForward, isBack, isLeft, isRight, isUp, isDown, isMouseRBttnPress, mouseEps );

	}//	if (m_pInputManager)

	return S_OK;
}
//============================================
void	CMyGame::Destroy()
{
	_tex1.Destroy();
	_tex2.Destroy();
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