//============================================
#include "Global.h"
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
//	텍스쳐 생성.
HRESULT CMyGame::InitTexture()
{
	m_pTex = new CDxTexture();
	m_pTex->Create(GetDev(), "texture/myfamily.jpg",false);

	return S_OK;
}
//============================================
HRESULT CMyGame::InitVB()
{
	SVtxDTxtr vtx[4];

	vtx[0]._pos = D3DXVECTOR3(-1, -1, 0);
	vtx[0]._color = 0xFFFF0000;
	vtx[0]._u = 0.0f;
	vtx[0]._v = 1.0f;

	vtx[1]._pos = D3DXVECTOR3(-1, 1, 0);
	vtx[1]._color = 0xFF0000FF;
	vtx[1]._u = 0.0f;
	vtx[1]._v = 0.0f;

	vtx[2]._pos = D3DXVECTOR3(1, -1, 0);
	vtx[2]._color = 0xFF00FF00;
	vtx[2]._u = 1.0f;
	vtx[2]._v = 1.0f;

	vtx[3]._pos = D3DXVECTOR3(1, 1, 0);
	vtx[3]._color = 0xFF000000;
	vtx[3]._u = 1.0f;
	vtx[3]._v = 0.0f;

	// 정점버퍼를 생성한다.
	if (FAILED(GetDev()->CreateVertexBuffer(4 * sizeof(SVtxDTxtr)
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
void CMyGame::SetMaterial()
{
	D3DMATERIAL9 mtrl = { 0 };
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;

	GetDev()->SetMaterial(&mtrl);

}//	void CMyGame::SetMaterial()
//============================================
void CMyGame::SetLight()
{
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	memset(&light, 0, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;	//	조명 종류.
	light.Diffuse.r = 1.0f;				//	조명 색상.
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 1.0f;

	vecDir = D3DXVECTOR3(cosf(timeGetTime() / 500.f), 1.0f, sinf(timeGetTime() / 500.f));

	//	조명 방향.	
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	light.Range = 1000.0f;	// 조명 유효 범위.

	//	디바이스에 조명 설정.
	GetDev()->SetLight(0, &light);

	//	조명 활성화.
	GetDev()->LightEnable(0, TRUE);

	// 주변 광원 설정.
	GetDev()->SetRenderState(D3DRS_AMBIENT, 0x00004444);

}//	void CMyGame::SetLight()
//============================================
INT		CMyGame::Init()
{
	m_pDxFont = new CDxFont();
	if (FAILED(m_pDxFont->Create(GetDev(), _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;

	InitVB();

	/*	텍스쳐 - 2)
		-	텍스쳐 버퍼 생성. */
	InitTexture();

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

	/*	텍스쳐 - 3-1)
		-	텍스쳐 지정. */
	GetDev()->SetTexture(0, m_pTex->GetTexture());

	/*	텍스쳐 - 3-2)
		-	텍스쳐 스테이지 지정.

		-	주요 스테이지 설정 타입.

			연산 타입				|	설명
			---------------------------------------------------------------
			D3DTSS_COLOROP			|	텍스처 색깔 혼합 방식 설정.
			D3DTSS_COLORARG1		|	첫번째 색상 인자값 설정
			D3DTSS_COLORARG2		|	두번째 색상 인자값 설정
			D3DTSS_ALPHAOP			|	텍스처 알파값 혼합 방식 설정.
			D3DTSS_ALPHAARG1		|	첫번째 알파 인자값 설정
			D3DTSS_ALPHAARG2		|	두번째 알파 인자값 설정


			전달 값					|	설명
			---------------------------------------------------------------
			D3DTOP_MODULATE			|	요소들을 전부 곱함.
			D3DTA_TEXTURE			|	텍스처의 데이터.
			D3DTA_DIFFUSE			|	디퓨즈 값.
			D3DTOP_DISABLE			|	해당 텍스처 스테이지 및 인덱스가 더 높은 모든 단계의 처리 비활성화.
	*/
	GetDev()->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);	//	MODULATE연산으로 색깔을 섞음
	GetDev()->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);	//	첫번째 섞을색은 텍스쳐 색
	GetDev()->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);	//	두번째 섞을색은 정점 색

	GetDev()->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);	//	alpha연산은 사용하지 않음

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