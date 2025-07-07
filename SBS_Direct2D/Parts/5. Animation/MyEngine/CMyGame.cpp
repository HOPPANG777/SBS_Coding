//============================================
#include "Global.h"
//============================================
CMyGame* g_pMyGame;
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
INT		CMyGame::Init()
{ 
	if (FAILED(D3DXCreateTextureFromFileEx(
		m_pD3DDevice				//	디바이스 포인터..
		, "texture/myfamily.jpg"	//	텍스쳐 경로..
		
		, D3DX_DEFAULT				//	가로..
									//	ㄴ	0 이나 D3DX_DEFAULT 일 경우,
									//		텍스쳐 사이즈를 얻어옴.
		, D3DX_DEFAULT				//	세로..
		, 1							//	밉맵 레벨 ( 참고 : https://ozlael.tistory.com/45 )
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE			//	필터링..
		, D3DX_FILTER_NONE			//	밉 필터링..
		, 0							//	컬러키..
		, &m_tInfoBG.m_imageInfo	//	텍스쳐 정보..
		, NULL
		, &m_tInfoBG.m_d3dTxtr
	)))
	{
		MessageBox(NULL, "myfamily.jpg file Could not be found", "Err", 0);
		m_tInfoBG.m_d3dTxtr = NULL;
		return -1;
	}
	
	SetRect(&m_tInfoBG.m_rcImage, 0, 0, m_tInfoBG.m_imageInfo.Width, m_tInfoBG.m_imageInfo.Height);


	if (FAILED(D3DXCreateTextureFromFileEx(
		m_pD3DDevice
		, "Texture/animate.bmp"

		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 1
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE
		, D3DX_FILTER_NONE
		, 0xFF000000				//	컬러키..
		, &m_tInfoAni.m_imageInfo
		, NULL
		, &m_tInfoAni.m_d3dTxtr
	)))
	{
		MessageBox(NULL, "animate.bmp file Could not be found", "Err", 0);
		m_tInfoAni.m_d3dTxtr = NULL;
		return -1;
	}

	SetRect(&m_tInfoAni.m_rcImage, 0, 0, 0, 32);

	//	timeGetTime()
	//	-	운영체제가 시작된 후 경과된 시간..
	//	-	1/1000 초 단위..
	m_dwBeginTime = timeGetTime();

	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::FrameMove()
{
	m_dwEndTime = timeGetTime();

	if ((m_dwEndTime - m_dwBeginTime) > FRAME_REFRESH_TIME)
	{
		m_tInfoAni.m_rcImage.left += 32;

		if (m_tInfoAni.m_rcImage.left + 32 >= 960)
			m_tInfoAni.m_rcImage.left = 0;

		m_tInfoAni.m_rcImage.right = m_tInfoAni.m_rcImage.left + 32;

		m_dwBeginTime = m_dwEndTime;
	
	}//	if ((m_dwEndTime - m_dwBeginTime) > FRAME_REFRESH_TIME)

	m_vecAniPos = D3DXVECTOR3( cosf(D3DX_PI*m_dwBeginTime*0.0001f), sinf(D3DX_PI*m_dwBeginTime*0.0003f), 0.0F );

	m_vecAniPos *= 100.0f;

	m_vecAniPos += D3DXVECTOR3(300, 300, 0.F);
	
	return 0;

}//	INT		CMyGame::FrameMove()
//============================================
INT		CMyGame::Render()
{
	D3DXVECTOR3 center = D3DXVECTOR3(
							m_tInfoBG.m_imageInfo.Width * 0.5f,
							m_tInfoBG.m_imageInfo.Height * 0.5f,
							0 );

	D3DXVECTOR3 pos = D3DXVECTOR3(
							m_dwScrWidth * 0.5f,
							m_dwScrHeight * 0.5f,
							0);

	m_pD3DSprite->Draw(
				m_tInfoBG.m_d3dTxtr,
				&m_tInfoBG.m_rcImage,
				&center,
				&pos,
				D3DXCOLOR(1, 1, 1, 1));

	m_pD3DSprite->Draw(
				m_tInfoAni.m_d3dTxtr,
				&m_tInfoAni.m_rcImage,
				NULL,
				&m_vecAniPos,
				D3DXCOLOR(1, 1, 1, 1));

	return 0;

}//	INT		CMyGame::Render()
//============================================
void	CMyGame::Destroy()
{
	SAFE_RELEASE(m_tInfoBG.m_d3dTxtr);
	SAFE_RELEASE(m_tInfoAni.m_d3dTxtr);

}//	void	CMyGame::Destroy()
//============================================