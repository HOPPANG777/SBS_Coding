//============================================
#include "Global.h"
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
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
D3DMATERIAL9 CMyGame::InitMtrl(D3DXCOLOR a, D3DXCOLOR d, D3DXCOLOR s, D3DXCOLOR e, float p)
{
	D3DMATERIAL9 mtrl;
	mtrl.Ambient = a;
	mtrl.Diffuse = d;
	mtrl.Specular = s;
	mtrl.Emissive = e;
	mtrl.Power = p;
	return mtrl;
}
//============================================
D3DLIGHT9 CMyGame::InitDirectionalLight(D3DXVECTOR3* direction,
										D3DXCOLOR* color)
{
	D3DLIGHT9 light;
	::ZeroMemory(&light, sizeof(light));

	light.Type = D3DLIGHT_DIRECTIONAL;
	light.Ambient = *color * 0.4f;
	light.Diffuse = *color;
	light.Specular = *color * 0.6f;
	light.Direction = *direction;

	return light;
}
void CMyGame::SetLights()
{
	D3DXVECTOR3 dir(0.707f, -0.0f, 0.707f);
	D3DXCOLOR col(1.0f, 1.0f, 1.0f, 1.0f);
	D3DLIGHT9 light = InitDirectionalLight(&dir, &col);

	GetDev()->SetLight(0, &light);
	GetDev()->LightEnable(0, true);
	GetDev()->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	GetDev()->SetRenderState(D3DRS_SPECULARENABLE, false);
}
//============================================
INT		CMyGame::Init()
{
	m_pDxFont = new CDxFont();
	if (FAILED(m_pDxFont->Create(GetDev(), _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;

	m_pGrid = new CDxGrid();
	m_pGrid->Create(GetDev());

	g_pLog = new CLog(ZF_LOG_TARGET_WINDOW);

	//	찻주전자 메쉬를 생성.
	D3DXCreateTeapot(GetDev(), &m_pTeapot, 0);

	BYTE* v = 0;
	m_pTeapot->LockVertexBuffer(0, (void**)&v);

	//	메쉬의 경계구 정보 계산.
	D3DXComputeBoundingSphere(
		(D3DXVECTOR3*)v,
		m_pTeapot->GetNumVertices(),
		D3DXGetFVFVertexSize(m_pTeapot->GetFVF()),
		&m_boundSphere._center,
		&m_boundSphere._radius);

	m_pTeapot->UnlockVertexBuffer();

	//	구 메쉬 생성.
	D3DXCreateSphere(GetDev(), m_boundSphere._radius, 20, 20, &m_pSphere, 0);

	// Set light.
	SetLights();
	
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
INT	CMyGame::Render3D()
{
	//	그리드 렌더링.	
	m_pGrid->FrameMove();
	m_pGrid->Render();

	static float r = 0.0f;
	static float v = 1.0f;
	static float angle = 0.0f;

	D3DXMatrixTranslation( &m_matWorld, cosf( angle ) * r, sinf( angle ) * r, 10.0f );

	//	경계구를 주전자의 위치에 매칭.
	m_boundSphere._center = D3DXVECTOR3( cosf( angle ) * r, sinf( angle ) * r, 10.0f );

	float timeDelta = GetElapsedTime() * 0.001f;
	r += v * timeDelta;

	if (r >= 8.0f)
		v = -v; // reverse direction

	if (r <= 0.0f)
		v = -v; // reverse direction

	angle += 1.0f * D3DX_PI * timeDelta;
	if (angle >= D3DX_PI * 2.0f)
		angle = 0.0f;
	
	//	주전자 그리기.
	GetDev()->SetTransform(D3DTS_WORLD, &m_matWorld);
	GetDev()->SetMaterial(&YELLOW_MTRL);
	m_pTeapot->DrawSubset(0);

	
	//	경계구 그리기
	//	-	알파 블렌딩을 이용하여 반투명 처리.	
	//	-	[ 참고 : https://showmiso.tistory.com/139 ]
	GetDev()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	GetDev()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GetDev()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	D3DMATERIAL9 blue = BLUE_MTRL;
	//	투명값	50%
	blue.Diffuse.a = 0.5f;
	GetDev()->SetMaterial(&blue);
	m_pSphere->DrawSubset(0);

	//	알파 블렌딩 off.
	GetDev()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	UpdateFPS();

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
}
//============================================
/*
	[ 1. 뷰포트 좌표 -> 투영좌표 변환. ]
	-	
	-	참고 :	https://dlgnlfus.tistory.com/135 -> 뷰포트 변환
				https://dlgnlfus.tistory.com/135 -> 가상 카메라

	-	뷰포트 변환 행렬
		|	w/2			0			0				0	|
		|	0			-h/2		0				0	|
		|	0			0			MaxZ - MinZ		0	|
		|	x + w/2		y + h/2		MinZ			0	|

		1)	투영창의 좌표 P = ( Px, Py, Pz )는
			뷰포트 변환후 스크린 좌표 S = ( Sx, Sy )가 됨.
			->	P * 뷰포트 변환 행렬 = S
				P = S * 뷰포트 변환 행렬의 역행렬.
				
				->	Px = ( (2x / 뷰포트 너비) - 1 ) (1/m00)
					=	(2Sx - 2X - Width ) / Width
					Py = ( (-2y / 뷰포트 높이) + 1 ) (1/m11)
					=	(-2Sy + 2Y + Height ) / Height
					Pz = 1
					-	Dx 는 평면 z = 1에
						투영창이 일치하도록
						정의하고 있음..

					-	X,Y 는
						뷰포트 시작 위치..

					뷰포트의 시작위치는 대부분 0이므로
					Px = ( (2Sx) / ViewPort Width ) - 1
					Py = ( (-2Sy) / ViewPort Height ) - 1
					Pz = 1

		2)	투영행렬은 다른 시점을 시뮬레이션 하기 위해
			투영창의 포인트 배율을 변경..
			변경되기 이전의 원래 포인트 값은
			배율 연산의 역을 통해 포인트 변환..
			투영 행렬을 P라고 가정할때,
			변환행렬의 P00, P11이
			포인트 x,y좌표의 배율을 변경하므로
			아래와 같이 적용한다.

			->	Px = ( ( (2 * Sx) / ViewPort Width ) - 1 ) * ( 1 / P00 )
				Py = ( ( (-2 * Sy) / ViewPort Height ) - 1 ) * ( 1 / P11 )
				Pz = 1
*/

//	스크린 좌표 -> 투영 좌표.
//============================================
Ray CMyGame::CalculatePickingRay(int x, int y)
{
	float px = 0.0f;
	float py = 0.0f;

	//	뷰포트 정보 얻기.
	D3DVIEWPORT9 vp;
	GetDev()->GetViewport(&vp);

	//	투영행렬 얻기.
	D3DXMATRIX proj;
	GetDev()->GetTransform(D3DTS_PROJECTION, &proj);

	px = (((2.0f*x) / vp.Width) - 1.0f) / proj(0, 0);
	py = (((-2.0f*y) / vp.Height) + 1.0f) / proj(1, 1);

	Ray ray;	
	ray._origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	광선 원점 = 뷰스페이스의 원점.
	ray._direction = D3DXVECTOR3(px, py, 1.0f);		//	광선 방향.

	return ray;
}
//============================================
//	참고 : https://skmagic.tistory.com/3
/*
	[ 2. 광선 변환. ]
	-	최종적으로 광선을 월드 변환할때 사용.
*/
//============================================
void CMyGame::TransformRay(Ray* ray, D3DXMATRIX* T)
{
	// 좌표변환.
	//	-	광선의 원점을 변환, w = 1.
	D3DXVec3TransformCoord(
		&ray->_origin,
		&ray->_origin,
		T);

	// 벡터변환.
	//	-	광선의 방향을 변환, w = 0.
	D3DXVec3TransformNormal(
		&ray->_direction,
		&ray->_direction,
		T);

	// 광선의 방향을 정규화.
	D3DXVec3Normalize(&ray->_direction, &ray->_direction);
}
//============================================
bool CMyGame::RaySphereIntTest(Ray* ray, BoundingSphere* sphere)
{
	//	경계구의 중심 -> 원점 방향의 방향 벡터 계산.
	D3DXVECTOR3 v = ray->_origin - sphere->_center;

	//	참고 : [ 광선 - 물체 교차.png ]
	/*
		광선의 성분 P좌표와
		구의 중심점 사이의 거리가
		반지름과 같다면
		충돌한 것으로 판정.

		->	|| p - c || - r = 0
			
			광선 p(t) = p0 + tu가
			구체와 교체하는지
			확인하려면

			1)	|| p(t) - c || - r = 0
				|| (p0 + tu) - c || - r = 0
				=	At^2 + Bt + C
				
					A : u * u
					B : 2( u * (p0-c) )
					C : ( p0 - c ) * ( p0 - c ) - r2

			2)	이때 u를 정규화하면  A = 1.
				=	t^2 + Bt + C

				t에 대하여 2개의 해를 얻을수 있다.
				t0 = (-B + sqrtf(B^2 -4C) / 2)
				t1 = (-B - sqrtf(B^2 -4C) / 2)

			3)	t0, t1의 값으로 충돌상태를 파악가능.
				
				1)	t0, t1 < 0
					-	광선이 구체와 교차하지 않음.
				
				2)	t0, t1의 부호가 서로 다른경우.
					-	광선이 구체 내부에 있음.
					-	양수의 해가 단일 교차점을 제공.

				3)	t0, t1 > 0
					-	광선이 구체를 2번 교차함.

				4)	t0 == t1
					-	광선이 구체와 접촉.
				
	*/
	float b = 2.0f * D3DXVec3Dot(&ray->_direction, &v);
	float c = D3DXVec3Dot(&v, &v) - (sphere->_radius * sphere->_radius);

	// 판별식 체크.
	float discriminant = (b * b) - (4.0f * c);

	// 허수인지 체크.
	if (discriminant < 0.0f)
		return false;

	//	제곱근 구하기.
	discriminant = sqrtf(discriminant);

	float s0 = (-b + discriminant) / 2.0f;
	float s1 = (-b - discriminant) / 2.0f;

	// 두 값 모두 0보다 작으면 교차하지 않음.
	if (s0 >= 0.0f || s1 >= 0.0f)
		return true;

	return false;
}
//============================================
LRESULT CMyGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (GetInput())
		GetInput()->MsgProc(hWnd, msg, wParam, lParam);

	switch (msg)
	{
	case WM_LBUTTONDOWN:

		//	스크린 좌표의 마우스 좌표를 투영좌표로 변환.
		Ray ray = CalculatePickingRay(LOWORD(lParam), HIWORD(lParam));

		//	카메라 변환 행렬을 얻음.
		D3DXMATRIX view;
		GetDev()->GetTransform(D3DTS_VIEW, &view);

		//	카메라 행렬을 역행렬로 계산하면 월드 변환 행렬이 됨.
		D3DXMATRIX viewInverse;
		D3DXMatrixInverse(&viewInverse, 0, &view);

		//	월드 행렬로 광선을 변환.
		TransformRay(&ray, &viewInverse);

		//	충돌 체크.
		if (RaySphereIntTest(&ray, &m_boundSphere))
			MessageBox(0, "Hit!", "HIT", 0);

		break;

	}//	switch (msg)

	return CCore::MsgProc(hWnd, msg, wParam, lParam);
}
//============================================//