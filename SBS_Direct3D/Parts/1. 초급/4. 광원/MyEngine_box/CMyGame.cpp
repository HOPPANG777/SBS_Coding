//============================================
#include "Global.h"
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
HRESULT CMyGame::InitVB()
{
	SVtxNor vtx[4];

	vtx[0]._pos = D3DXVECTOR3(-1, -1, 0);
	vtx[0]._nor = D3DXVECTOR3(0, 0, -1);

	vtx[1]._pos = D3DXVECTOR3(-1, 1, 0);
	vtx[1]._nor = D3DXVECTOR3(0, 0, -1);

	vtx[2]._pos = D3DXVECTOR3(1, -1, 0);
	vtx[2]._nor = D3DXVECTOR3(0, 0, -1);

	vtx[3]._pos = D3DXVECTOR3(1, 1, 0);
	vtx[3]._nor = D3DXVECTOR3(0, 0, -1);

	// 정점버퍼를 생성한다.
	if (FAILED(GetDev()->CreateVertexBuffer(4 * sizeof(SVtxNor)
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

	//---------------------------------
	// 뷰 변환
	//---------------------------------
	D3DXMATRIX mtViw;
	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -5.0f);						// 카메라의 위치
	D3DXVECTOR3 vLookAt(0.0f, 0.0f, 0.0f);						// 카메라가 보고 있는 지점
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);						// 카메라의 업 벡터
	D3DXMatrixLookAtLH(&mtViw, &vEyePt, &vLookAt, &vUpVec);		// 뷰 행렬 만들기

	GetDev()->SetTransform(D3DTS_VIEW, &mtViw);					// 디바이스의 뷰 행렬 설정

	//---------------------------------
	// 투영 변환
	//---------------------------------
	D3DXMATRIX m_mtPrj;
	FLOAT	fScreenW = (FLOAT)800;
	FLOAT	fScreenH = (FLOAT)600;
	FLOAT	fFOV = D3DX_PI / 4.0f;	//	fov가 커지면
									//	-	화면에 표현되는 오브젝트수 증가( 어안렌즈, 물고기 눈 )
									//	-	어지러움 정도가 심해짐.

									//	fov가 작으면
									//	-	화면에 표현되는 오브젝트수 줄어듬.
									//	-	어지러움 정도가 적어짐.

	FLOAT	fAspect = fScreenW / fScreenH;
	FLOAT	fNear = 1.f;
	FLOAT	fFar = 5000.f;

	D3DXMatrixPerspectiveFovLH(&m_mtPrj, fFOV, fAspect, fNear, fFar);	// 투영 행렬 만들기
	GetDev()->SetTransform(D3DTS_PROJECTION, &m_mtPrj);					// 디바이스의 투영 행렬을 설정

}//	void CMyGame::SetMatrix()
//============================================
//	광원 - 3)
//	-	재질 설정..
void CMyGame::SetMaterial()
{
	D3DMATERIAL9 mtrl = { 0 };
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;

	GetDev()->SetMaterial(&mtrl);

}//	void CMyGame::SetMaterial()
//============================================
//	광원 - 4)
//	-	조명 설정..
void CMyGame::SetLight()
{
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;	
	memset(&light, 0, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;	//	조명 종류.
	light.Diffuse.r = 1.0f;				//	조명 색상.
	light.Diffuse.g = 0.0f;
	light.Diffuse.b = 0.0f;

	//vecDir = D3DXVECTOR3(cosf(timeGetTime() / 500.f), 1.0f, sinf(timeGetTime() / 500.f));
	vecDir = D3DXVECTOR3(0.0f, 0.f, -1.f);

	//	조명 방향.	
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	light.Range = 1000.0f;	// 조명 유효 범위.

	GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);		// 광원설정 On.

	//	디바이스에 조명 설정.
	GetDev()->SetLight(0, &light);

	//	조명 활성화.
	GetDev()->LightEnable(0, TRUE);

	// 주변 광원 설정.
	GetDev()->SetRenderState(D3DRS_AMBIENT, 0x11111111);

}//	void CMyGame::SetLight()
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
	//	폰트 출력.
	m_pDxFont->Draw(GetSprite(), _T("fps 테스트"), 300, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);
	m_pDxFont->Draw(GetSprite(), m_tszFPS, 0, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

	return S_OK;
}
//============================================
INT		CMyGame::Render3D()
{
	// 현재 은면제거 상태 확인.
	DWORD dCullMode = 0;
	GetDev()->GetRenderState(D3DRS_CULLMODE, &dCullMode);

	// 은면제거 비활성화
	GetDev()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);


	// 정점을 디바이스에 연결
	GetDev()->SetStreamSource(0, m_pVB, 0, sizeof(SVtxNor));
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
	if (m_pInputManager)
	{
		m_pInputManager->FrameMove();

		SetMatrix();

		//	광원 - 5)
		//	재질 및 조명 적용..
		SetMaterial();
		SetLight();

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