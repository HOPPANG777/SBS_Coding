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
		,284
		,426
		//, D3DX_DEFAULT			//	가로..
									//	-	0 이나 D3DX_DEFAULT 일 경우
									//		강제로 해당 값보다 큰 2의 지수값으로 변환.. 
		//, D3DX_DEFAULT			//	세로..
		, 1							//	밉맵 레벨( 참고 : https://ozlael.tistory.com/45 )
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE			//	필터링..
		, D3DX_FILTER_NONE			//	밉 필터링..
		, 0							//	컬러키..
		, &m_d3DImageInfo			//	텍스쳐 정보..
		, NULL
		, &m_pD3DTxtr
	)))
	{
		MessageBox(NULL, "myfamily.jpg file Could not be found", "Err", 0);
		m_pD3DTxtr = NULL;
		return -1;
	}

	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render()
{	
	RECT	rt1 = { 0, 0, (LONG)m_d3DImageInfo.Width, (LONG)m_d3DImageInfo.Height };
	
	//	https://hellowoori.tistory.com/38
	D3DXVECTOR3	vcCenter((LONG)m_d3DImageInfo.Width * 0.5f, (LONG)m_d3DImageInfo.Height * 0.5f, 0);

	D3DXVECTOR3	vcPos(m_dwScrWidth * 0.5f, m_dwScrHeight * 0.5f, 0);

	/*
		m_pD3DTxtr..
		-	텍스쳐..

		rt1..
		-	출력할 소스 영역..
		-	NULL이면 전체 영역..
						
		vcCenter..
		-	스프라이트의
			피벗( 기준점 ) 설정..
		-	NULL이면 (0,0,0),
			좌상단이 기준점..

		pPosition..
		-	스프라이트의 위치..
			ㄴ	vcCenter을 기준으로 이동..
		-	NULL이면 vcCenter을
			(0,0,0)으로 이동시킴..
	*/

	m_pD3DSprite->Draw( m_pD3DTxtr, &rt1, &vcCenter, &vcPos, D3DXCOLOR(1, 1, 1, 1));
	
	return 0;
}
//============================================
INT		CMyGame::FrameMove()	{ return 0; }
//============================================
void	CMyGame::Destroy()
{
	SAFE_RELEASE(m_pD3DTxtr);

}//	void	CMyGame::Destroy()
//============================================
/*
	[ 참고 ]

		2D Texture 크기는 2의 n승을 지켜야 하는가
		https://ordinarybk.tistory.com/entry/2D-Texture-%ED%81%AC%EA%B8%B0%EB%8A%94-2%EC%9D%98-n%EC%8A%B9%EC%9D%84-%EC%A7%80%EC%BC%9C%EC%95%BC-%ED%95%98%EB%8A%94%EA%B0%80

		텍스처의 크기가 2의 n승이 아니어도 되는겁니까?
		https://www.gpgstudy.com/forum/viewtopic.php?t=7900

		[펌]왜 이미지사이즈를 2의 승수로 만들어야 하나?
		http://egloos.zum.com/chulin28ho/v/2594532

		텍스쳐해상도를 2의 거듭제곱으로 하는 이유
		https://www.youtube.com/watch?v=T55TY-487X8&ab_channel=TA%EA%B3%B0TV
*/
//============================================