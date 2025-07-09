//============================================
#include "Global.h"
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
//	텍스쳐 - 3 )
//	-	텍스쳐 로딩..
HRESULT CMyGame::InitTexture()
{
	m_pTex = new CDxTexture();
	m_pTex->Create(GetDev(), "texture/myfamily.jpg",false);

	return S_OK;
}
//============================================
HRESULT CMyGame::InitVB()
{
	//	텍스쳐 - 4 )
	//	-	정점 설정시 텍스처 좌표 설정..
	//	-	참고 :	https://commen.tistory.com/108
	//				https://blog.naver.com/sipack7297/220424401873
	//				https://ko.wikipedia.org/wiki/UV_%EB%A7%A4%ED%95%91

	SVtxTxtr vtx[4];

	vtx[0]._pos = D3DXVECTOR3(-1, -1, 0);
	vtx[0]._u = 0.0f;
	vtx[0]._v = 1.0f;

	vtx[1]._pos = D3DXVECTOR3(-1, 1, 0);
	vtx[1]._u = 0.0f;
	vtx[1]._v = 0.0f;

	vtx[2]._pos = D3DXVECTOR3(1, -1, 0);
	vtx[2]._u = 1.0f;
	vtx[2]._v = 1.0f;

	vtx[3]._pos = D3DXVECTOR3(1, 1, 0);
	vtx[3]._u = 1.0f;
	vtx[3]._v = 0.0f;

	// 정점버퍼를 생성..
	if (FAILED(GetDev()->CreateVertexBuffer(4 * sizeof(SVtxTxtr)
		, 0
		, D3DFVF_CUSTOM
		, D3DPOOL_MANAGED
		, &m_pVB
		, NULL)))
	{
		return E_FAIL;
	}

	// 정점데이터를 채운다..
	// Lock은 현재의 독점을 유지..
	void* pvtx;
	if (FAILED(m_pVB->Lock(0, sizeof(vtx), (void**)&pvtx, 0)))
		return E_FAIL;

	memcpy(pvtx, vtx, sizeof(vtx));

	m_pVB->Unlock();

	return S_OK;
}
//============================================
void CMyGame::SetMatrix()
{
	//---------------------------------
	// 월드 변환..
	//---------------------------------
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationY(&matWorld, timeGetTime() / 500.0f);	// 회전행렬..
	GetDev()->SetTransform(D3DTS_WORLD, &matWorld);			// 디바이스의 월드 행렬을 설정한다..

}//	void CMyGame::SetMatrix()
//============================================
INT		CMyGame::Init()
{
	m_pDxFont = new CDxFont();
	if (FAILED(m_pDxFont->Create(GetDev(), _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;

	InitVB();

	//	텍스쳐 - 5 )
	//	-	텍스쳐 버퍼 생성..
	InitTexture();

	m_pGrid = new CDxGrid();
	m_pGrid->Create(GetDev());

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
	//	그리드 렌더링..
	m_pGrid->FrameMove();
	m_pGrid->Render();


	//	월드 행렬 설정..
	SetMatrix();
	
	// 현재 은면제거 상태 확인..
	DWORD dCullMode = 0;
	GetDev()->GetRenderState(D3DRS_CULLMODE, &dCullMode);

	// 은면제거 비활성화..
	GetDev()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	//	텍스쳐 - 6 )
	//	-	텍스쳐 지정..
	GetDev()->SetTexture(0, m_pTex->GetTexture());

	// 정점을 디바이스에 연결..
	GetDev()->SetStreamSource(0, m_pVB, 0, sizeof(SVtxTxtr));

	// 정점 포멧을 설정..
	GetDev()->SetFVF(D3DFVF_CUSTOM);

	// 렌더링..
	GetDev()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	// 은면 제거 상태 복구..
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
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pTex);
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