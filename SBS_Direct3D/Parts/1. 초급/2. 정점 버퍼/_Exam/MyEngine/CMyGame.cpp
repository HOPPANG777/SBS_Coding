//============================================
#include "Global.h"
//============================================
CMyGame::CMyGame() {}
//============================================
CMyGame::~CMyGame() {}
//============================================
/*	버텍스 버퍼 - 3)
	-	버텍스 생성과 초기화..
		-	간단한 삼각형을 렌더링..
*/
HRESULT CMyGame::InitVB()
{
	//	버텍스 정보 설정..
	//	-	3개의 버텍스 정보를 설정..
	//	-	FVF의 구성과 동일할 것..
	//	-	정점의 순서는 시계방향( Clock Wise )으로 함..
	//		-	D3D는 기본적으로 시계방향의 순서로
	//			버텍스가 설정된 폴리곤을 앞면으로 인식..
	//		-	반시계 방향( Counter Clock Wise )은
	//			뒷면으로 인식하여 렌더링 하지 않음..

	CUSTOMVERTEX vertices[] =
	{
		{ 50.f,		50.0f,	0.5f, 1.0f, 0xffff0000 },	//	x, y, z, rhw, color( 0xAARRGGBB )
		{ 250.0f,	250.0f, 0.5f, 1.0f, 0xff00ff00 },
		{ 50.0f,	250.0f, 0.5f, 1.0f, 0xff0000ff },

		{ 50.f,		50.0f,	0.5f, 1.0f, 0xffff0000 },	//	x, y, z, rhw, color( 0xAARRGGBB )
		{ 250.0f,	50.0f, 0.5f, 1.0f, 0xff0000ff },
		{ 250.0f,	250.0f, 0.5f, 1.0f, 0xff00ff00 },
	};

	/*	버텍스 버퍼 생성..
		-	3개의 버텍스 데이터를
			관리할 메모리 할당..
		-	FVF를 지정하여
			데이터의 형식을 설정..
	*/
	if (FAILED(GetDev()->CreateVertexBuffer(
		6 * sizeof(CUSTOMVERTEX),	//	생성할 정점버퍼의 크기..
		0,							//	리소스 사용방법 설정..
									//	-	주요 옵션..
									//		-	0					:	부가 정보 없음. 기본 값..
									//		-	D3DUSAGE_DYNAMIC	:	버퍼를 동적으로 생성..
									//		-	D3DUSAGE_POINTS		:	정점버퍼 생성시에만 사용되며
									//									파티클 시스템에서 주로 사용..
		D3DFVF_CUSTOMVERTEX,		//	정점 포맷( FVF )형식..
		D3DPOOL_DEFAULT,			//	정점 버퍼가 저장될 메모리 위치와
									//			( 비디오 카드, 시스템 메모리 )
									//	관리방식 설정..
									//	-	D3DPOOL_DEFAULT..
									//		ㄴ	가장 적합한 메모리풀로 설정..
									//	-	D3DPOOL_MANAGED..
									//		ㄴ	비디오 카드..
									//	-	D3DPOOL_SYSTEMMEM..
									//		ㄴ	시스템 메모리..
		/*
			비디오 메모리에 생성되는 경우..
			-	GPU에 의해 정점 셰이더, T&L등
				강력한 하드웨어 가속을 사용할 수 있음..
			-	비디오 카드 자체의 메모리 용량을
				벗어날 순 없음..

			시스템 메모리에 생성되는 경우..
			-	하드웨어 가속 사용 불가..
			-	메모리 용량이 비디오 메모리에 비해
				상대적으로 풍부함..
		*/


		&m_pVB,						//	반환될 정점버퍼..
		NULL)))						//	예약값, 현재는 NULL..
		return E_FAIL;

	VOID* pVertices;

	//	버텍스 버퍼의 메모리에 대한 독점과
	//						( 외부 접근 차단 )
	//	버텍스 버퍼의 포인터 획득..
	//				(주소값)
	if (FAILED(m_pVB->Lock
	(
		0,					//	독점하려는 정점 정보 시작점..
		sizeof(vertices),	//	독점하려는 정점 정보 사이즈..
							//	-	정점 버퍼 전체를 독점하려면
							//		시작점과 사이즈를 모두 0으로 지정..
		(void**)&pVertices,	//	버텍스 버퍼의 포인터를 반환 받을 포인터..
		0					//	독점 방식 설정 옵션, 기본값은 0..
	)))
		return E_FAIL;

	//	버텍스 정보를 버텍스 버퍼에 복사..
	memcpy(pVertices, vertices, sizeof(vertices));

	//	독점 해제..
	m_pVB->Unlock();

	return S_OK;
}
//============================================
INT		CMyGame::Init()
{
	//	버텍스 버퍼 초기화..
	InitVB();

	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render3D()
{
	/*	버텍스 버퍼 - 4)
		-	버텍스 렌더링..
			-	BeginScene()과 EndScene() 사이에
				정점의 렌더링 코드를 작성..
	*/
	//	1)	정점 버퍼를 디바이스의
	//		데이터 스트림에 연결..
	//		( 연속적인 데이터 흐름 )
	GetDev()->SetStreamSource(
		0,			//	정점 버퍼를 연결할 스트림 소스 지정..
					//	ㄴ	다중스트림을 안쓸거면 0으로 지정..

		m_pVB,		//	스트림을 연결할 정점 버퍼의 포인터..

		0,			//	렌더링 파이프 라인으로 보내질
					//	정점 버퍼의 옵셋..
					//	ㄴ	일반적으로 0으로 설정..
		sizeof(CUSTOMVERTEX)	//	정점 버퍼 한덩어리의 크기..
	);
	//	2)	FVF 정보 설정..
	GetDev()->SetFVF(D3DFVF_CUSTOMVERTEX);

	//	3)	그리기..
	GetDev()->DrawPrimitive(
		D3DPT_TRIANGLELIST,		//	그리기 타입 설정..
								//	ㄴ	참고 : https://blog.naver.com/znfgkro1/80174814358
		0,						//	시작 버텍스의 인덱스..
		2						//	렌더링하는 기본 도형의 수..
	);

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove() { return S_OK; }
//============================================
void	CMyGame::Destroy()
{
	/*	버텍스 버퍼 - 5)
		-	버퍼 해제..
		-	D3D 디바이스를 통해 생성된 메모리는
			프로그램 종료전에 반드시 해제할 것..
	*/
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