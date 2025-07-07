//============================================================
//	c4996 에러 무시..
//	-	strcpy함수와 관련하여
//		strcpy_s를 사용할 것을 권고하는 에러..
//		-	무시해도 상관 없음..
#pragma warning(disable : 4996)
//============================================================
#pragma comment(lib, "d3d9.lib")	//	라이브러리 추가..
									//	속성 - 링커 - 입력 - 추가 종속성..

#pragma comment(lib, "winmm.lib")
//============================================================
#include <windows.h>
#include <d3d9.h>	//	d3d 헤더파일..
//============================================================
//	Window 관련 변수들..
char				g_sCls[128];
HINSTANCE			g_hInst = NULL;	//	윈도우 인스턴스..
HWND				g_hWnd = NULL;	//	윈도우 핸들..
DWORD				g_dWinStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;	//	윈도우 스타일..
DWORD				g_dScnX = 800;			//	윈도우	너비..
DWORD				g_dScnY = 600;			//			높이..
BOOL				g_bWindow = TRUE;		// 윈도우 모드..
BOOL				g_bShowCusor = TRUE;	// 커서 노출 상태..
//------------------------------------
//	DX 관련 변수들..
LPDIRECT3D9			g_pD3D = NULL;			//	D3D 객체..
LPDIRECT3DDEVICE9	g_pd3dDevice = NULL;	//	디바이스 객체..
											//	ㄴ	일반적으로 그래픽 카드와
											//		유사한 개념..
int					g_VtxProcessMode = D3DCREATE_HARDWARE_VERTEXPROCESSING;	//	버텍스 프로세싱 방법..
//============================================================
//	Window 관련 함수들..
void	RegistWinClass(const char* pszClassName);
HWND	CreateWindows(HINSTANCE hInst);
LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//------------------------------------
//	DX 관련 함수들..
HRESULT InitDX();
void	SetVtxProcessMode();
INT		Game_Render();


//게임 실행 관련 함수들..
INT		Game_Init();
INT		Game_Run();
void	Game_Destroy();
INT		Game_Update();
void	Game_Cleanup();


//============================================================
void RegistWinClass(const char* pszClassName)
{
	strcpy(g_sCls, pszClassName);

	WNDCLASS wc =
	{
		CS_CLASSDC
		, WndProc
		, 0L
		, 0L
		, g_hInst
		, NULL
		, LoadCursor(NULL,IDC_ARROW)
		, (HBRUSH)GetStockObject(LTGRAY_BRUSH)
		, NULL
		, g_sCls
	};

	RegisterClass(&wc);

}//	void RegistWinClass()
//============================================================
HRESULT InitDX()
{
	//	D3D 생성..
	// 
	//	-	Direct3D 객체는 SDK 버전에 따른
	//		사용 가능 여부를 확인..
	// 
	//		ㄴ	사용 가능하면 NULL이 아닌 값을 반환..
	// 
	//	-	[ D3D_SDK_VERSION ]는 고정값..
	if ( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;

	//	디바이스를 생성하기 위해서는
	//	D3DPRESENT_PARAMETERS 구조체가 필요..
	//	-	전부 0으로 리셋 후
	//		필요한 변수만 세팅..

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = g_bWindow;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//	후면 버퍼와 전면 버퍼가
												//	교환될 때( Fliping Chain )의
												//	방법 설정..
												// 
												//	ㄴ	주로 D3DSWAPEFFECT_DISCARD..


	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;	//	후면 버퍼의 픽셀 포멧..
												//	D3DFMT_UNKNOWN - 바탕 화면 모드에 맞게 설정..

	d3dpp.EnableAutoDepthStencil = TRUE;		//	깊이 / 스텐실 버퍼를 사용할 것인지..
												//	true : d3d가 자동으로 생성 및 관리..

	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//	깊이 / 스텐실 버퍼의 포멧..

	/*
		-	깊이 버퍼..
			( Depth Buffer, Z Buffer )

			-	일반적으로 Z 축을 기준으로
				화면으로부터 얼마나 가깝고 멀리
				배치되어있는지에 대한 정보를
				관리하는 메모리..

			-	0 ~ 1 사이의 정규화된 정보로 구성됨..

			-	이 값을 비교하여 픽셀이 서로 겹쳐졌을때
				화면에 그릴지 말지를 결정..


		-	스텐실 버퍼..
			( Stencil Buffer )

			-	특정 픽셀에만 그리기를 제한할 수 있는
				8비트 정수형 버퍼..

				ㄴ	렌더링할 영역을 선택적으로 제어 가능..

			예)	거울, 외곽선 등에 활용..


	*/

	//	버텍스 프로세싱 설정..
	SetVtxProcessMode();
	/*
		CreateDevice 주요 옵션..

		-	D3DADAPTER_DEFAULT	:	기본 그래픽 카드..
	 
		-	D3DDEVTYPE_HAL		:	하드웨어 가속( 가장 큰 속도 )을 받을 것인가.. 

									-	하드웨어 지원이 없을 경우..
										D3D는 소프트웨어로 대체 가능..

										-	D3DDEVTYPE_REF..
								
		-	D3DDEVTYPE_REF		:	DirectX를 소프트웨어로
									모방( 에뮬레이트 ) 하는 기능..

	*/
	if (FAILED(g_pD3D->CreateDevice(
		D3DADAPTER_DEFAULT
		, D3DDEVTYPE_HAL
		, g_hWnd
		, g_VtxProcessMode
		, &d3dpp
		, &g_pd3dDevice)))
	{
		g_pD3D->Release();
		return E_FAIL;
	}

	return S_OK;

}//	HRESULT InitDX()
//============================================================
void SetVtxProcessMode()
{
	D3DCAPS9 d3dCaps;

	//	하드웨어( 그래픽 카드 )가 제공하는 장치 특성..
	g_pD3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps);

	//	하드웨어 버텍스 프로세싱 지원 여부 확인..
	if (d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		g_VtxProcessMode = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		g_VtxProcessMode = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

}//	void SetVtxProcessMode()
//============================================================
HWND CreateWindows(HINSTANCE hInst)
{
	g_hInst = hInst;

	//	윈도우 클래스 등록.
	RegistWinClass("Create Device");

	RECT rc;
	SetRect(&rc, 0, 0, g_dScnX, g_dScnY);
	//	AdjustWindowRect(&rc, g_dWinStyle, FALSE);	
	//	-	rc			:	윈도우 클라이언트 영역..
	//	-	g_dWinStyle :	윈도우 스타일..
	//	-	FALSE		:	메뉴 생성 여부..
	//	윈도우의 순수 클라이언트 영역 설정..
	AdjustWindowRect(&rc, g_dWinStyle, FALSE);	

	//	GetSystemMetrics..
	//	-	매개변수로 전달된 값에 해당하는 시스템 정보 반환..
	//	-	SM_CXSCREEN /	SM_CYSCREEN..
	//		-	현재 화면 해상도의
	//			가로 / 세로 크기..( 단위 : pixel.. )
	int iScnSysW = ::GetSystemMetrics(SM_CXSCREEN);	
	int iScnSysH = ::GetSystemMetrics(SM_CYSCREEN);	

	g_hWnd = CreateWindow(g_sCls
		, g_sCls
		, g_dWinStyle
		, (iScnSysW - (rc.right - rc.left)) / 2
		, (iScnSysH - (rc.bottom - rc.top)) / 2
		, (rc.right - rc.left)
		, (rc.bottom - rc.top)
		, GetDesktopWindow()
		, NULL
		, g_hInst
		, NULL);

	if (g_hWnd)
	{
		ShowWindow(g_hWnd, SW_SHOW);
		UpdateWindow(g_hWnd);
		ShowCursor(g_bShowCusor);

	}//	if (g_hWnd)

	return g_hWnd;
	
}//	HWND CreateWindows(HINSTANCE hInst)
//============================================================
void Game_Cleanup()
{
	Game_Destroy();

	if (g_pd3dDevice) {
		g_pd3dDevice->Release();
		g_pd3dDevice = NULL; }

	if (g_pD3D) {
		g_pD3D->Release();
		g_pD3D = NULL; }

}//	void Cleanup()
//============================================================
LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		//-----------------------
		case WM_KEYDOWN:
		{
			switch (wParam) { 
				case VK_ESCAPE: SendMessage(hWnd, WM_DESTROY, 0, 0);
					break; }

			return 0;

		}//	case WM_KEYDOWN:
		//-----------------------
		case WM_DESTROY:
		{
			Game_Cleanup();
			PostQuitMessage(0);
			return 0;

		}//	case WM_DESTROY:
		//-----------------------

	}//	switch (msg)

	return DefWindowProc(hWnd, msg, wParam, lParam);

}//	LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//============================================================
INT Game_Run()
{
	// Enter the message loop
	MSG msg;
	memset(&msg, 0, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		//	1)	일반 어플리케이션..
		// 
		//		-	입력 또는 이벤트가 발생했을 경우에만
		//			데이터 처리..
		// 
		//		-	GetMessage()..
		// 
		//			-	해당 프로그램이 운영체제에서 보낸
		//				메시지를 받을 때까지 대기..
		// 
		//			-	블록 함수..( 예 : scanf, cin, getchar 등 )
		// 
		// 
		//	2)	게임..
		// 
		//		-	입력이 없는 경우에도
		//			다른 처리를 진행해야 함..
		// 
		//			-	NPC의 AI, 네트웍 데이터 처리 등
		//				유저의 입력과 무관한 동작..
		// 
		//		-	PeekMessage()..
		// 
		//			-	입력이 있는지 체크..
		// 
		//				Yes	:	그에 대한 처리..
		//				No	:	그외 처리 가능..
		// 
		//			-	PM_REMOVE..
		// 
		//				-	메세지 큐를 읽고 큐에 있던
		//					메세지 제거..

		if ( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if ( FAILED( Game_Update() ) )
				SendMessage(g_hWnd, WM_QUIT, 0, 0);

			if ( FAILED( Game_Render() ) )
				SendMessage(g_hWnd, WM_QUIT, 0, 0);
		}

	}//	while (msg.message != WM_QUIT)

	UnregisterClass(g_sCls, g_hInst);

	return 0;

}//	INT Run()
//============================================================
INT Game_Init()
{
	////////////////////////////////////////////////////////////////////////////
	//

	// 게임 데이터 생성..

	//
	////////////////////////////////////////////////////////////////////////////

	return 0;

}//	INT Game_Init()
//============================================================
void Game_Destroy()
{
	////////////////////////////////////////////////////////////////////////////
	//

	// 게임 데이터 해제..

	//
	////////////////////////////////////////////////////////////////////////////

}//	void Game_Destroy()
//============================================================
INT Game_Update()
{
	////////////////////////////////////////////////////////////////////////////
	//

	// 게임 데이터 실시간 갱신..

	//
	////////////////////////////////////////////////////////////////////////////

	return 0;

}//	INT Game_FrameMove()
//============================================================
INT Game_Render()
{
	if (NULL == g_pd3dDevice)
		return -1;

	/*
		1.	화면 초기화..

		2.	디바이스의 BeginScene() 함수를 호출하여
			장면을 후면 버퍼( Back Face Buffer )에 그린다..

		3.	장면을 그린다..( 렌더링 )

		4.	EndScene() 함수를 호출하여
			장면을 다 그렸다는 것을 알린다..

		5.	Present() 함수를 호출하여
			전면 버퍼( Front Face Buffer )와
			후면 버퍼를 교체한다..

		6.	1부터 5를 반복..
	*/
	
	// 실질적으로는 버퍼( 후면 버퍼: 색상, 깊이, 스텐실 )를
	// 지우는 것이 아니라 채우는 것이다..
	//	-	D3DCLEAR_TARGET		:	색상 버퍼를 지운다..
	//		D3DCLEAR_ZBUFFER	:	깊이 버퍼를 지운다..
	// 
	//		-	D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER 설정이 일반적..

	g_pd3dDevice->Clear(0
		, NULL
		, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER
		, D3DCOLOR_XRGB(0, 120, 160)
		, 1.0f, 0);


	// BeginScene과 EndScene 사이에
	// 렌더링을 구현..
	if (FAILED(g_pd3dDevice->BeginScene()))
		return -1;

	////////////////////////////////////////////////////////////////////////////
	//

	//	게임 데이터 랜더링..

	//
	////////////////////////////////////////////////////////////////////////////


	// EndScene
	g_pd3dDevice->EndScene();

	// 후면버퍼 전면버퍼 교체..( flipping )
	return g_pd3dDevice->Present(0, 0, 0, 0);

}//	INT Render()
//============================================================
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	return MsgProc(hWnd, msg, wParam, lParam); }
//============================================================
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	if ( FAILED( CreateWindows(hInst) ) )
		return FALSE;

	//*
	if ( FAILED( InitDX() ) )
		return FALSE;
	//*/

	if ( FAILED( Game_Init() ) )
		return -1;

	return Game_Run();
}
//============================================================
/*
*	Q)	다음과 같이 클래스를 이용하여 예제소스의 구조를 바꿔봅니다..
* 
*		-	윈도우와 관련된 기능을 클래스화..( class CCore; )
* 
*		-	DirectX와 관련된 기능을 클래스화..( class CDx; )
* 
*		-	CCore에서 CDx 클래스를 참조..
* 
*			-	CCore가 CDx의 객체를 멤버 변수로 소유..
* 
*		-	CCore 객체를 이용하여 프로그램 실행..
* 
* 
*		Advanced )
* 
*		-	CCore를 상속받는 CMyGame를
			이용하여 객체 생성..
* 
*			-	CCore를 기본틀로 구성하고
*				실제 게임은 CMyGame에서 재정의..
* 
*			-	게임마다 다르게 재정의 될 기능들
				( Init(), Destroy(), FrameMove(), Render() )은
*				virtual로 선언..
* 
*		-	CMyGame 객체를 이용하여 프로그램 실행..
*/
//============================================================
/*
	[ 참고 ]

		깊이 버퍼(Depth Buffer)
		https://kkadalg.tistory.com/23

		DirectX - 깊이 버퍼(Z - Buffer)
		https://blog.naver.com/hblee4119/221940188597

		OpenGL 정리 - 19. 스텐실(Stencil), 블랜딩(Blending), 컬링(Face Culling)
		https://surkim.tistory.com/54

		[C++, DirectX 12] DirectX 게임 프로그래밍 강좌 - 스텐실 버퍼
		https://blog.naver.com/wkdghcjf1234/220835885338

*/
//============================================================