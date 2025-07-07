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
	//	텍스쳐.
	if (FAILED(m_dxTxtrTest.Create(m_pD3DDevice, "texture/myfamily.jpg")))
		return -1;

	//	텍스쳐.(에니메이션.)
	m_pDxTxtrAnim = new CDxTextureAnim(30, 30);
	if (FAILED(m_pDxTxtrAnim->Create(m_pD3DDevice, "texture/animate.bmp", 0xFF000000)))
		return -1;
	m_pDxTxtrAnim->SetPivot(D3DXVECTOR3(16, 16, 0));

	//	DX 폰트..
	//	-	생성..
	if (FAILED(D3DXCreateFont(m_pD3DDevice
		, 30				//	높이
		, 0					//	가로
		, FW_NORMAL			//	두께. FW_BOLD, FW_LIGHT등이 주로 사용됨.
		, 1					//	밉맵레벨, 사용하지 않음. 0은 생성.
		, 0					//	이탤릭체.
		, DEFAULT_CHARSET		//	캐릭터 셋.문자 집합.
		, OUT_DEFAULT_PRECIS	//	OutputPrecision( 정밀성 ), 높을수록 출력속도 느림.
		, DEFAULT_QUALITY		//	퀄리티
		, DEFAULT_PITCH | FF_DONTCARE			//	PitchAndFamily, 기본 간격 및 글꼴 집합.
		, _T("Arial")			//	폰트명, _T("궁서체"), _T("굴림체")등이 주로 사용됨.
		, &m_pDxFont)))			//	폰트 객체
		return -1;

	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render()
{
	//	텍스쳐.
	D3DXVECTOR3	vcPos(m_dwScrWidth * 0.5f, m_dwScrHeight * 0.5f, 0);
	m_dxTxtrTest.Draw(m_pD3DSprite, vcPos);
	
	//	텍스쳐.(에니메이션.)
	m_pDxTxtrAnim->Draw(m_pD3DSprite);

	//	폰트.
	RECT	rc;
	//	출력 영역 설정.
	SetRect(&rc, 0, 0, 300, 50);

	//	DX 폰트..
	//	-	폰트 그리기..
	m_pDxFont->DrawText(
		m_pD3DSprite,				//	스프라이트
		_T("우리 가족 입니다 ^^"),	//	메시지
		-1,							//	메시지 길이
									//	-	-1 이면 텍스트가 널문자 만날 때까지만 렌더링.
		&rc,						//	출력 영역
		DT_LEFT,					//	포맷
		D3DXCOLOR(1, 1, 0, 1)		//	색
	);

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	DWORD dwTime = timeGetTime();
	m_pDxTxtrAnim->OnUpdateFrame(dwTime);

	m_pDxTxtrAnim->SetPos2D(cosf(D3DX_PI * dwTime * 0.0001f), sinf(D3DX_PI * dwTime * 0.0002f));
	D3DXVECTOR3 tmp = m_pDxTxtrAnim->GetPos();
	tmp *= 100.0f;
	tmp += D3DXVECTOR3(400, 300, 0);
	m_pDxTxtrAnim->SetPos2D(tmp.x, tmp.y);

	return S_OK;

}//	INT		CMyGame::FrameMove()
//============================================
void	CMyGame::Destroy()
{
	m_dxTxtrTest.Destroy();
	m_pDxTxtrAnim->Destroy();
	//	DX 폰트..
	//	-	제거..
	SAFE_RELEASE(m_pDxFont);

	delete m_pDxTxtrAnim;

}//	void	CMyGame::Destroy()
//============================================