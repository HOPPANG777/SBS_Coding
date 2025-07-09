//============================================
#include "Global.h"
//============================================
#define TRANS_RATE 0.001F
#define SCALE_RATE 0.001F
//============================================
CMyGame::CMyGame()
{
	_scale = 1.0f;
	_rotY = 0.0f;
	_pos = D3DXVECTOR3(0, 0, 0);
}
//============================================
CMyGame::~CMyGame()	{}
//============================================
HRESULT CMyGame::InitVB()
{
	/*	
		행렬 - 3)

			-	정점 초기화..
	*/

	// 세 정점을 선언과 동시에 정의..
	SVtxD vtx[3];

	vtx[0] = SVtxD( -1.0f, -1.0f, 0.0f, 0xffff0000 );
	vtx[1] = SVtxD( 1.0f, -1.0f, 0.0f, 0xff0000ff );
	vtx[2] = SVtxD( 0.0f, 1.0f, 0.0f, 0xff00ff00 );

	// 정점버퍼를 생성..
	if (FAILED(GetDev()->CreateVertexBuffer(3 * sizeof(SVtxD)
		, 0
		, D3DFVF_CUSTOM
		, D3DPOOL_MANAGED
		, &m_pVB
		, NULL)))
		return E_FAIL;

	// 정점데이터를 채운다.
	// Lock은 현재의 독점을 유지..
	void* pvtx;
	if (FAILED(m_pVB->Lock(0, sizeof(vtx), (void**)&pvtx, 0)))
		return E_FAIL;

	memcpy(pvtx, vtx, sizeof(vtx));

	m_pVB->Unlock();

	return S_OK;

}//	HRESULT CMyGame::InitVB()
//============================================
INT CMyGame::Init()
{
	m_pInputManager = new CInputManager();

	m_pDxFont = new CDxFont();
	if (FAILED(m_pDxFont->Create(GetDev(), _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;

	InitVB();

	return 0;

}//	INT CMyGame::Init()
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
	/*	
		행렬 - 4)
		
			-	정점 그리기..
	*/

	//	회전하는 동작을 연출하기 위해
	//	컬링 기능을 끔..
	//		D3DCULL_CW				:	시계 방향을 컬링..
	//		D3DCULL_CCW( 디폴트 )	:	시계 반대 방향을 컬링..
	GetDev()->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	//	노멀 벡터 정보가 없으므로
	//	어둡게 나옴..
	//	-	라이팅 off..
	//	-	노멀 벡터가 있어야 연산이 된다..( D3DFVF_NORMAL )
	GetDev()->SetRenderState( D3DRS_LIGHTING, FALSE );

	// 정점을 디바이스에 연결..
	GetDev()->SetStreamSource(0, m_pVB, 0, sizeof(SVtxD));

	// 정점 포멧을 설정..
	GetDev()->SetFVF( D3DFVF_CUSTOM );

	// 렌더링..
	GetDev()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT CMyGame::FrameMove()
{
	UpdateFPS();
	
	if (m_pInputManager)
	{
		m_pInputManager->FrameMove();

#if 0
		D3DXVECTOR3 dirLeft(-0.01f, 0, 0);
		D3DXVECTOR3	dirRight(0.01f, 0, 0);
		D3DXVECTOR3	dirUp(0, -0.01f, 0);
		D3DXVECTOR3	dirDown(0, 0.01f, 0);

		if (m_pInputManager->KeyPress(VK_RIGHT))
		{
			SVtxD* pvtx;
			// Lock에서 두번째를 0으로하면
			// 데이터 전부를 가져오게 됨..
			if (FAILED(m_pVB->Lock(0, 0, (void**)&pvtx, 0)))
				return E_FAIL;

			pvtx[0]._pos += dirRight;
			pvtx[1]._pos += dirRight;
			pvtx[2]._pos += dirRight;

			m_pVB->Unlock();
		}

		if (m_pInputManager->KeyPress(VK_LEFT))
		{
			SVtxD* pvtx;
			if (FAILED(m_pVB->Lock(0, 0, (void**)&pvtx, 0)))
				return E_FAIL;

			pvtx[0]._pos += dirLeft;
			pvtx[1]._pos += dirLeft;
			pvtx[2]._pos += dirLeft;

			m_pVB->Unlock();
		}

		if (m_pInputManager->KeyPress(VK_UP))
		{
			SVtxD* pvtx;
			if (FAILED(m_pVB->Lock(0, 0, (void**)&pvtx, 0)))
				return E_FAIL;

			pvtx[0]._pos += dirUp;
			pvtx[1]._pos += dirUp;
			pvtx[2]._pos += dirUp;

			m_pVB->Unlock();
		}

		if (m_pInputManager->KeyPress(VK_DOWN))
		{
			SVtxD* pvtx;
			if (FAILED(m_pVB->Lock(0, 0, (void**)&pvtx, 0)))
				return E_FAIL;

			pvtx[0]._pos += dirDown;
			pvtx[1]._pos += dirDown;
			pvtx[2]._pos += dirDown;

			m_pVB->Unlock();
		}


#else
		/*
			행렬 - 5)
			[ 참고 : https://blog.naver.com/whdgkks12347/221347100241
				 	 https://blog.naver.com/dhygns/60191337515 ]

				-	행렬 변환 적용..
				-	3*3 행렬을 고려했으나
					이동에 대한 처리로 인해
					4*4 행렬로 연산..
		*/
		//---------------------------------
		//	월드 변환..
		//---------------------------------
		//	스케일 변환..
		static bool isScale = false;
		if (m_pInputManager->KeyPress('q') || m_pInputManager->KeyPress('Q'))
		{
			if (_scale <= 5.0f)
			{
				_scale += 1.f * GetElapsedTime() * SCALE_RATE;
				isScale = true;
			}
		}
		else if (m_pInputManager->KeyPress('e') || m_pInputManager->KeyPress('E'))
		{
			if (_scale >= 0.05f)
			{
				_scale -= 1.f * GetElapsedTime() * SCALE_RATE;
				isScale = true;
			}
		}

		D3DXVECTOR3	vcS(_scale, _scale, _scale);
		D3DXMATRIX	mtScl;	// 스케일 행렬..
		D3DXMatrixScaling(&mtScl, vcS.x, vcS.y, vcS.z);
		/*
			정점을 x,y,z축으로 
			Sx,Sy,Sz 만큼 확대/축소..
			
			x' = x * Sx
			y' = y * Sy
			z' = z * Sz
											|	Sx	0	0	0	|
											|	0	Sy	0	0	|
			[x' y' z' 1] = [x y z 1]	*	|	0	0	Sz	0	|
											|	0	0	0	1	|
		*/
		/*
		if (isScale)
		{
			ShowLog("-------------스케일 행렬---------------------\n");
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
					ShowLog("%7.1f", mtScl(i, j));
				ShowLog("\n");
			}			
		}
		//*/


		//	Quiz )	회전 변환..
		//	-	"1", "2" 를 누르면
		//		Y 축으로 회전되도록 합니다..

		static bool isRotate = false;
		D3DXMATRIX mtRot;	// 회전 행렬..
		//	단위 행렬..
		//	-	주대각선의 원소가 모두 1이며
		//		나머지 원소는 모두 0인 정사각 행렬..
		D3DXMatrixIdentity( &mtRot );
		

		/*
			--------------
			x축 회전 행렬..
			--------------
												|	1	0		0		0	|
												|	0	cos@	sin@	0	|
				[x' y' z' 1] = [x y z 1]	*	|	0	-sin@	cos@	0	|
												|	0	0		0		1	|


			---------------
			y축 회전 행렬..
			---------------
												|	cos@	0	-sin@	0	|
												|	0		1	0		0	|
				[x' y' z' 1] = [x y z 1]	*	|	sin@	0	cos@	0	|
												|	0		0	0		1	|

			---------------
			z축 회전 행렬..
			---------------
												|	cos@	sin@	0	0	|
												|	-sin@	cos@	0	0	|
				[x' y' z' 1] = [x y z 1]	*	|	0		0		1	0	|
												|	0		0		0	1	|
		*/

		D3DXMATRIX mtTrn;	// 이동 행렬..
		static bool isTrans = false;
		if (m_pInputManager->KeyPress(VK_RIGHT))
		{
			_pos.x += GetElapsedTime() * TRANS_RATE;
			isTrans = true;
		}
		else if (m_pInputManager->KeyPress(VK_LEFT))
		{
			_pos.x -= GetElapsedTime() * TRANS_RATE;
			isTrans = true;
		}

		if (m_pInputManager->KeyPress(VK_UP))
		{
			_pos.y += GetElapsedTime() * TRANS_RATE;
			isTrans = true;
		}			
		else if (m_pInputManager->KeyPress(VK_DOWN))
		{
			_pos.y -= GetElapsedTime() * TRANS_RATE;
			isTrans = true;
		}	

		D3DXMatrixTranslation(&mtTrn, _pos.x, _pos.y, _pos.z);
		/*
			정점을 x,y,z축을 Tx,Ty,Tz 만큼 이동..

			x' = x + Tx
			y' = y + Ty
			z' = z + Tz
																|	1	0	0	0	|
																|	0	1	0	0	|
				[x + Tx, y' + Ty, z' + Tz,  1] = [x y z 1]	*	|	0	0	1	0	|
																|	Tx	Ty	Tz	1	|
		*/
		/*
		if (isTrans)
		{
			ShowLog("-------------이동 행렬---------------------\n");
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
					ShowLog("%7.1f", mtTrn(i, j));
				ShowLog("\n");
			}			
		}
		//*/


		//	최종 월드 행렬..
		//	-	연산 순서 중요!!!
		D3DXMATRIX mtWld;
		mtWld = mtScl * mtRot * mtTrn;
		//mtWld = mtScl * mtTrn * mtRot ;
		/*
		if (isScale || isRotate || isTrans)
		{
			ShowLog("************* 최종 월드 행렬 *************\n");
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
					ShowLog("%7.1f", mtWld(i, j));
				ShowLog("\n");
			}
		}
		//*/

		GetDev()->SetTransform(D3DTS_WORLD, &mtWld);	// 디바이스에 월드 행렬 설정..
		isScale = false;
		isRotate = false;
		isTrans = false;
		//---------------------------------
#endif
		//---------------------------------
		// 뷰 변환
		//---------------------------------		
		D3DXMATRIX mtViw;
		D3DXVECTOR3 vEyePt(0.0f, 0.0f, -5.0f);					// 카메라의 위치..
		D3DXVECTOR3 vLookAt(0.0f, 0.0f, 0.0f);					// 카메라가 보고 있는 지점..
		D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);					// 카메라의 업 벡터..
		D3DXMatrixLookAtLH(&mtViw, &vEyePt, &vLookAt, &vUpVec);	// 뷰 행렬 만들기..

		GetDev()->SetTransform(D3DTS_VIEW, &mtViw);				// 디바이스에 뷰 행렬 설정..



		//---------------------------------
		// 투영 변환..
		//---------------------------------
		D3DXMATRIX m_mtPrj;
		FLOAT	fScreenW = (FLOAT)800;
		FLOAT	fScreenH = (FLOAT)600;
		FLOAT	fFOV = D3DX_PI / 4.0f;	//	시야각( Field Of View )
										//	-	fov가 커지면..
										//		-	화면에 표현되는 오브젝트수 증가..
										//			예)	어안렌즈, 물고기 눈 등..
										//		-	오브젝트 크기는 줄어듬..
										//		-	어지러움 정도가 심해짐..

										//	-	fov가 작으면..
										//		-	화면에 표현되는 오브젝트수 줄어듬..
										//		-	오브젝트 크기는 커짐..
										//		-	어지러움 정도가 적어짐..

		FLOAT	fAspect = fScreenW / fScreenH;	//	종횡비..
		FLOAT	fNear = 1.f;					//	근접 클리핑 영역 거리..
		FLOAT	fFar = 5000.f;					//	원거리 클리핑 영역 거리..

		D3DXMatrixPerspectiveFovLH(&m_mtPrj, fFOV, fAspect, fNear, fFar);	// 투영 행렬 만들기..
		GetDev()->SetTransform( D3DTS_PROJECTION, &m_mtPrj );					// 디바이스에 투영 행렬을 설정..

	}//	if (m_pInputManager)

	return S_OK;

}//	INT CMyGame::FrameMove()
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