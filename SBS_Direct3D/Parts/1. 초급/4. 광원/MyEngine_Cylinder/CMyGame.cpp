//============================================
#include "Global.h"
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
HRESULT CMyGame::InitVB()
{
	// 정점버퍼를 생성한다.
	if (FAILED(GetDev()->CreateVertexBuffer(50 * 2 * sizeof(SVtxNor)
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
	SVtxNor* pVtxNor;
	if (FAILED(m_pVB->Lock(0, 0, (void**)&pVtxNor, 0)))
		return E_FAIL;

	/*	광원 - 3)
		-	원통 설정..
	*/
	for (int cur = 0; cur < 50; cur++)
	{
		FLOAT theta = (2 * D3DX_PI*cur) / (50 - 1);
		pVtxNor[2 * cur + 0]._pos = D3DXVECTOR3(sinf(theta), -1.0f, cosf(theta));
		pVtxNor[2 * cur + 0]._nor = D3DXVECTOR3(sinf(theta), 0.0f, cosf(theta));

		pVtxNor[2 * cur + 1]._pos = D3DXVECTOR3(sinf(theta), 1.0f, cosf(theta));
		pVtxNor[2 * cur + 1]._nor = D3DXVECTOR3(sinf(theta), 0.0f, cosf(theta));
	}

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
	D3DXMatrixRotationX(&matWorld, timeGetTime() / 300.0f);	// 회전행렬	
	GetDev()->SetTransform(D3DTS_WORLD, &matWorld);		// 디바이스의 월드 행렬을 설정한다.

	//---------------------------------
	// 뷰 변환
	//---------------------------------
	D3DXMATRIX mtViw;
	D3DXVECTOR3 vEyePt(0.0f, 0.0f, -5.0f);						// 카메라의 위치
	D3DXVECTOR3 vLookAt(0.0f, 0.0f, 0.0f);						// 카메라가 보고 있는 지점
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);						// 카메라의 업 벡터
	D3DXMatrixLookAtLH(&mtViw, &vEyePt, &vLookAt, &vUpVec);		// 뷰 행렬 만들기

	GetDev()->SetTransform(D3DTS_VIEW, &mtViw);				// 디바이스의 뷰 행렬 설정

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
	GetDev()->SetTransform(D3DTS_PROJECTION, &m_mtPrj);				// 디바이스의 투영 행렬을 설정

}//	void CMyGame::SetMatrix()
//============================================
void CMyGame::SetMaterial()
{
	/*	재질	:	반사되는 빛의 성질을 결정.
		속성	:
			-	Diffuse
				-	확산광.
				-	표면의 모든 점들에 비춰지는 빛.
				-	여러 방향에서 피사체를 부드럽고 고르게 비추는 빛.

			-	Ambient
				-	주변광.
				-	최저 평균 밝기.
				-	똑같은 양으로 모든 면에서 나오는 빛.
				-	특정한 방향이 없이 주변을 덮고 있는 빛
				-	현실 세계에는 없는 조명으로 *간접광을 흉내내기 위한 것.
					*	간접광
						-	물체에 반사된 빛이 또다른 물체에 영향을 미치는 것.

			-	Specular
				-	반사광.
				-	표면에 닿으면 한 방향으로 강하게 반사하여
					특정한 각도에서만 관찰할 수 있는 빛.
				-	정반사광의 방정식 고려사항.
					-	빛의 방향.
					-	표면의 형태.
					-	관찰자의 시점.

			-	Emissive
				-	방출광.
				-	메시 표면에서 자체적으로 방출되는 빛.
				-	다른 메시에 영향을 주지는 못함.

			-	power
				-	Specular( 반사광 )의 강도를 조절.
	*/

	D3DMATERIAL9 mtrl = { 0 };
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 0.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;

	GetDev()->SetMaterial(&mtrl);

}//	void CMyGame::SetMaterial()
//============================================
/*	광원 - 5)
	-	조명 설정.
		-	조명의 위치와 방향에 따른 광원 종류.

			광원					|	위치		|	방향	|	기타
		==================================================================================
		주변광원					|	X		|	X		|	색과 강도만 존재.
		( Ambient Light )		|			|			|	위치와 상관없이 같은 강도로 비춤.
		----------------------------------------------------------------------------------
		점광원					|	O		|	O		|	위치에 따라 강도가 달라짐.
		( Point Light )			|			|			|	백열전구.
		----------------------------------------------------------------------------------
		방향성 광원				|	X		|	O		|	광원의 방향이 하나의 방향을 갖음.
		( Directional Light )	|			|			|	태양.
		----------------------------------------------------------------------------------
		정적 광원				|	O		|	O		|	특정 위치와 범위에만 비추는 조명.
		( Spot Light )			|			|			|	무대의 스포트 라이트.
		----------------------------------------------------------------------------------
	*/
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

	//	조명 방향..	
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
	GetDev()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, (2 * 50) - 2);

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