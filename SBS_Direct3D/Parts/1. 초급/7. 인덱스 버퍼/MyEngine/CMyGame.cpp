//============================================
#include "Global.h"
//============================================
#define USE_IDXBUFFER
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
//	인덱스 버퍼 4)
//	-	버텍스 버퍼 초기화.
HRESULT CMyGame::InitVB()
{
#ifndef USE_IDXBUFFER
	SVtxD vtx[6];

	vtx[0]._pos = D3DXVECTOR3(-1, 1, 0);
	vtx[0]._color = 0xff00ff00;

	vtx[1]._pos = D3DXVECTOR3(1, 1, 0);
	vtx[1]._color = 0xff00ff00;

	vtx[2]._pos = D3DXVECTOR3(-1, -1, 0);
	vtx[2]._color = 0xff00ff00;

	vtx[3]._pos = D3DXVECTOR3(1, 1, 0);
	vtx[3]._color = 0xff0000ff;

	vtx[4]._pos = D3DXVECTOR3(1, -1, 0);
	vtx[4]._color = 0xff0000ff;

	vtx[5]._pos = D3DXVECTOR3(-1, -1, 0);
	vtx[5]._color = 0xff0000ff;

	// 정점버퍼를 생성한다.
	if (FAILED(GetDev()->CreateVertexBuffer(6 * sizeof(SVtxD)
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
#else
	SVtxD vtx[4];

	vtx[0]._pos = D3DXVECTOR3(-1, 1, 0);
	vtx[0]._color = 0xff00ff00;

	vtx[1]._pos = D3DXVECTOR3(1, 1, 0);
	vtx[1]._color = 0xff00ff00;

	vtx[2]._pos = D3DXVECTOR3(-1, -1, 0);
	vtx[2]._color = 0xff00ff00;

	vtx[3]._pos = D3DXVECTOR3(1, -1, 0);
	vtx[3]._color = 0xff0000ff;

	// 정점버퍼를 생성한다.
	if (FAILED(GetDev()->CreateVertexBuffer(4 * sizeof(SVtxD)
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

#endif
}//	HRESULT CMyGame::InitVB()
//============================================
//	인덱스 버퍼 5)
//	-	인덱스 버퍼 초기화.
HRESULT CMyGame::InitIB()
{
	SIdx indices[] =
	{
		{ 0,1,2 },{ 1,3,2 }
	};

	if (FAILED(GetDev()->CreateIndexBuffer(
		2 * sizeof(SIdx),		//	인덱스 버퍼 크기..
		0,						//	인덱스 버퍼 생성 방식.. 기본값은 0..
		D3DFMT_INDEX16,			//	인덱스 포맷, 각 인덱스의 크기..
		D3DPOOL_DEFAULT,		//	리소스 버퍼를 보관 유지하는 방식..
		&m_pIB,					//	생성 된 인덱스 버퍼 리소스..
		NULL					//	핸들값, 일종의 예약 데이터..NULL로 설정..
	)))
	{
		return E_FAIL;
	}

	void* pIndices;
	if (FAILED(m_pIB->Lock(
		0,					//	독점하려는 인덱스 정보 시작 옵셋..
		sizeof(SIdx),		//	독점하려는 인덱스 정보 사이즈..	
							//	-	인덱스 버퍼 전체를 독점하려면
							//		시작점과 사이즈를 모두 0으로 지정..
		(void**)&pIndices,	//	인덱스 버퍼의 포인터를 반환 받을 포인터..
		0)))				//	독점 방식 설정 옵션, 기본값은 0..
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


#ifndef USE_IDXBUFFER
	// 렌더링
	GetDev()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);
#else
	//	인덱스 버퍼 7)
	//	-	인덱스 버퍼를 이용한 렌더링 설정.
	GetDev()->SetIndices(m_pIB);
	// 렌더링
	GetDev()->DrawIndexedPrimitive(
		D3DPT_TRIANGLELIST,	//	그리기 방식..
		0,	//	인덱스의 시작지점으로부터 우리가 그리고자 하는
			//	정점이 시작되는 부분까지의 오프셋..
		0,	//	참조할 최소 인덱스 갯수..
			//	-	보통 0으로 설정..
			//	-	전체를 다그려주기 때문..
		6,	//	버텍스 사용횟수..
			//	-	버텍스는 총 4개이지만
			//		인덱스 버퍼로 인해 6번 사용됨..
		0,	//	읽기 시작할 인덱스 번호..
		2	//	그리고자 하는 폴리곤 갯수..
	);
#endif

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
	//	인덱스 버퍼 8)
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