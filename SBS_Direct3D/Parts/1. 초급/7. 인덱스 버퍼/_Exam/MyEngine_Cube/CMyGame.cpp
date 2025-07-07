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
	SVtxD vtx[8];

	vtx[0]._pos = D3DXVECTOR3(-1, 1, 1);
	vtx[0]._color = 0xff00ff00;

	vtx[1]._pos = D3DXVECTOR3(1, 1, 1);
	vtx[1]._color = 0xff00ff00;

	vtx[2]._pos = D3DXVECTOR3(1, 1, -1);
	vtx[2]._color = 0xff00ff00;

	vtx[3]._pos = D3DXVECTOR3(-1, 1, -1);
	vtx[3]._color = 0xff00ff00;


	vtx[4]._pos = D3DXVECTOR3(-1, -1, 1);
	vtx[4]._color = 0xff00ff00;

	vtx[5]._pos = D3DXVECTOR3(1, -1, 1);
	vtx[5]._color = 0xff00ff00;

	vtx[6]._pos = D3DXVECTOR3(1, -1, -1);
	vtx[6]._color = 0xff00ff00;

	vtx[7]._pos = D3DXVECTOR3(-1, -1, -1);
	vtx[7]._color = 0xff00ff00;



	// 정점버퍼를 생성한다.
	if (FAILED(GetDev()->CreateVertexBuffer(sizeof(vtx)
		, 0
		, D3DFVF_CUSTOM
		, D3DPOOL_MANAGED
		, &m_pVB
		, NULL)))
	{
		return E_FAIL;
	}

	// 정점데이터를 채운다.
	// Lock은 현재의 독점을 유지
	void* pvtx;
	if (FAILED(m_pVB->Lock(0, sizeof(vtx), (void**)&pvtx, 0)))
		return E_FAIL;

	memcpy(pvtx, vtx, sizeof(vtx));

	m_pVB->Unlock();

	return S_OK;

}//	HRESULT CMyGame::InitVB()
//============================================
//	인덱스 버퍼 5)
//	-	인덱스 버퍼 초기화.
HRESULT CMyGame::InitIB()
{
	SIdx indices[] =
	{
		{ 0,1,2 },
		{ 0,2,3 },

		{ 4,6,5 },
		{ 4,7,6 },

		{ 0,3,7 },
		{ 0,7,4 },

		{ 1,5,6 },
		{ 1,6,2 },

		{ 3,2,6 },
		{ 3,6,7 },

		{ 0,4,5 },
		{ 0,5,1 }
	};

	if (FAILED(GetDev()->CreateIndexBuffer(
		sizeof(indices),
		0,
		D3DFMT_INDEX16,
		D3DPOOL_DEFAULT,
		&m_pIB,
		NULL
	)))
	{
		return E_FAIL;
	}

	void* pIndices;
	if (FAILED(m_pIB->Lock(
		0,
		sizeof(SIdx),
		(void**)&pIndices,
		0)))
		return E_FAIL;

	memcpy(pIndices, indices, sizeof(indices));

	m_pIB->Unlock();

	return S_OK;
}
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

	//	인덱스 버퍼 6)
	//	-	인덱스 버퍼 초기화 함수 호출.
	InitIB();

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
	// 현재 은면제거 상태 확인.
	DWORD dCullMode = 0;
	GetDev()->GetRenderState(D3DRS_CULLMODE, &dCullMode);

	// 은면제거 비활성화
	GetDev()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// 정점을 디바이스에 연결
	GetDev()->SetStreamSource(0, m_pVB, 0, sizeof(SVtxD));
	// 정점 포멧을 설정
	GetDev()->SetFVF(D3DFVF_CUSTOM);

	//	인덱스 버퍼 7)
	//	-	인덱스 버퍼를 이용한 렌더링 설정.
	GetDev()->SetIndices(m_pIB);
	// 렌더링
	GetDev()->DrawIndexedPrimitive(	D3DPT_TRIANGLELIST,	//	Type
									0,					//	BaseVertexIndex
									0,					//	MinIndex
									8,					//	NumVertices
									0,					//	StartIndex
									12					//	PrimitiveCount
									);
	/*
		Type
		-	D3DPRIMITIVETYPE 열거형의 멤버.
		-	렌더링 하는 기본도형의 종류.

		BaseVertexIndex
		-	최초의 정점 인덱스까지의 오프셋(offset).
		-	0번 인덱스로 사용할 버텍스 설정.

		MinIndex
		-	인덱스 버퍼에서 사용할 최소한의 인덱스.
		-	BaseVertexIndex와 상대적.

		NumVertices
		-	렌더링할 정점의 갯수.
		-	전체 갯수 - ( BaseVertexIndex + MinIndex )

		StartIndex
		-	인덱스 배열안에서 정점을 읽기 시작 하는 위치.

		PrimitiveCount
		-	렌더링 하는 기본도형의 수.		
	*/

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
	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pDxFont);
	//	인덱스 버퍼 7)
	//	-	인덱스 버퍼 정리.
	SAFE_RELEASE(m_pIB);
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