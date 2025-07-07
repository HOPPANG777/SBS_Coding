//========================================================
#include "Global.h"
//========================================================
CDxCore*	g_pDxCore;
//========================================================
//-------------------------------
CDxCore::CDxCore()
{
	g_pDxCore = this;

	strcpy(m_tszClassName, "2D Game App");

	m_hInst = NULL;
	m_hWnd = NULL;
	m_dwWinStyle	= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
	m_dwScrWidth	= 800;
	m_dwScrHeight	= 600;

	m_bShowCursor	= TRUE;
	m_bWindowMode	= TRUE;			// Window mode

	m_pD3D			= NULL;			// D3D
	m_pD3DDevice	= NULL;			// Device

	m_pInputManager = NULL;			//	입력 매니져.

	m_fFPS = 60;
	ZeroMemory(m_tszFPS, sizeof(m_tszFPS));

	m_bDeviceLost = FALSE;

}//	CDxCore::CDxCore()
//-------------------------------
void CDxCore::RegistWinClass()
{
	// Register the window class
	WNDCLASS wc =
	{
		CS_CLASSDC
		, WndProc
		, 0L
		, 0L
		, m_hInst
		, NULL
		, LoadCursor(NULL,IDC_ARROW)
		, (HBRUSH)GetStockObject(WHITE_BRUSH)
		, NULL
		, m_tszClassName
	};

	RegisterClass(&wc);

}//	void CDxCore::RegistWinClass()
//-------------------------------
HRESULT CDxCore::CreateWindows()
{
	//	regist win class
	RegistWinClass();

	//Create the application's window
	RECT rc;
	SetRect(&rc, 0, 0, m_dwScrWidth, m_dwScrHeight);
	AdjustWindowRect(&rc, m_dwWinStyle, FALSE);

	int iScnSysW = GetSystemMetrics(SM_CXSCREEN);
	int iScnSysH = GetSystemMetrics(SM_CYSCREEN);

	m_hWnd = CreateWindow(m_tszClassName
		, m_tszClassName
		, m_dwWinStyle
		, (iScnSysW - (rc.right - rc.left)) / 2
		, (iScnSysH - (rc.bottom - rc.top)) / 2
		, (rc.right - rc.left)
		, (rc.bottom - rc.top)
		, NULL
		, NULL
		, m_hInst
		, NULL);

	if (m_hWnd == NULL)
		return E_FAIL;

	GetWindowRect(m_hWnd, &m_rcWin);

	return S_OK;

}//	HRESULT CDxCore::CreateWindows()
//-------------------------------
HRESULT CDxCore::CreateDX()
{
	// D3D생성
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// D3D를 통해서 화면 모드를 찾는다.
	D3DDISPLAYMODE d3ddm;
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
		return E_FAIL;

	// 디바이스를 생성하기 위해서는 프리젠트 파라메터 구조체가 필요
	// 전부 0으로 셋팅한다음 일부만 변수세팅
	ZeroMemory(&m_D3DPp, sizeof(m_D3DPp));
	m_D3DPp.Windowed = m_bWindowMode;
	m_D3DPp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DPp.BackBufferFormat = d3ddm.Format;
	m_D3DPp.BackBufferCount = 2;
	m_D3DPp.BackBufferWidth = m_dwScrWidth;
	m_D3DPp.BackBufferHeight = m_dwScrHeight;
	m_D3DPp.EnableAutoDepthStencil = TRUE;
	//	http://telnet.or.kr/directx/graphics/reference/d3d/constants/d3dpresent.htm
	//	런타임은 윈도우 클라이언트 영역을 즉시 갱신한다.
	//	어댑터 리프레쉬 간격중에 2 회 이상 이 갱신을 실시하는 일이 있다.
	//	이것은, DirectX 8.0 의 D3DSWAPEFFECT_COPY 를 사용하는 것에 동일하다. 
	//	IDirect3DDevice9::Present 에 직접 영향을 주는 경우가 있다. 이 옵션은, 윈도우 스왑 체인 및 풀 스크린 스왑 체인의 양쪽 모두로 항상 사용할 수 있다.
	m_D3DPp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	m_D3DPp.AutoDepthStencilFormat = D3DFMT_D16;

	//	D3DADAPTER_DEFAULT: 대부분의 그래픽카드는 모노 듀얼일 경우 이부분을 수정
	//	D3DDEVTYPE_HAL : 하드웨어 가속(가장 큰 속도)을 받을 것인가.. 하드웨어 지원이 없을 경우 D3D는 소프트웨어로 이를 대체 할 수 있다.
	//	D3DCREATE_HARDWARE_VERTEXPROCESSING	:	정점처리를 gpu에 맡김.
	//	D3DCREATE_SOFTWARE_VERTEXPROCESSING :	CPU에 맡김.
	//	D3DCREATE_MIXED_VERTEXPROCESSING    :	HVP, SVP간의 전환 가능.

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))
	{
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))
		{
			SAFE_RELEASE(m_pD3DDevice);
			SAFE_RELEASE(m_pD3D);
			return E_FAIL;
		
		}//	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))

	}//	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_MIXED_VERTEXPROCESSING, &m_D3DPp, &m_pD3DDevice)))
	
	// DX의 스프라이트는 디바이스가 생성된 후에 만들어야 한다.
	m_pDxSpriteManager = new CDxSprite();
	if (FAILED(m_pDxSpriteManager->Create(m_pD3DDevice)))
	{
		SAFE_DELETE(m_pDxSpriteManager);

		SAFE_RELEASE(m_pD3DDevice);
		SAFE_RELEASE(m_pD3D);

		return E_FAIL;
	}


	return S_OK;

}//	HRESULT CDxCore::CreateDX()
//-------------------------------
BOOL CDxCore::Create(HINSTANCE hInst)
{
	m_hInst = hInst;

	if (CreateWindows() == E_FAIL)
		return FALSE;

	if (CreateDX() == E_FAIL)
		return FALSE;

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);
	ShowCursor(m_bShowCursor);
	
	//	입력 관리자.
	m_pInputManager = new CInputManager();
	m_pInputManager->Create(m_hWnd);

	if (FAILED(Init()))
		return FALSE;

	if (FAILED(OnResetDevice()))
		return FALSE;

	return TRUE;

}//	INT	CDxCore::Create(HINSTANCE hInst)
//-------------------------------
void CDxCore::CleanUp()
{
	Destroy();

	SAFE_DELETE(m_pInputManager);
	SAFE_DELETE(m_pDxSpriteManager);
	SAFE_RELEASE(m_pD3DDevice);
	SAFE_RELEASE(m_pD3D);
	
}//	void CDxCore::CleanUp()
//-------------------------------
INT CDxCore::Run()
{
	HACCEL hAccel = LoadAccelerators(NULL, MAKEINTRESOURCE(IDR_ACCEL));

	MSG msg;
	memset(&msg, 0, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			if (hAccel == NULL || m_hWnd == NULL || 0 == TranslateAccelerator(m_hWnd, hAccel, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			
			}//	if (hAccel == NULL || m_hWnd == NULL || 0 == TranslateAccelerator(m_hWnd, hAccel, &msg))
		
		}//	if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		else
		{
			//	Process_2_2)
			//	다른 윈도우에 의해서 디바이스가 소실 된 경우 처리.
			//	cpu 타임을 다른 프로세스에게 양도.
			if (m_bDeviceLost)
				Sleep(100);

			//	Process_2_3)
			//	리셋 처리 여부 확인.
			if (m_bDeviceLost)
			{	
				HRESULT hr;

				//	리셋이 제대로 진행했는지 확인.
				//	-	리셋 처리 되지 않았다면 될때까지 반복.
				if (FAILED(hr = m_pD3DDevice->TestCooperativeLevel()))
				{
					// 디바이스 리셋.
					if (D3DERR_DEVICENOTRESET == hr)
						Reset3D();
					else if (D3DERR_DEVICELOST == hr) { }

				}//	if (FAILED(hr = m_pD3DDevice->TestCooperativeLevel()))
				else
					m_bDeviceLost = FALSE;

			}//	if (m_bDeviceLost)

			if (FAILED(Idle()))
				break;
			
		}//	~if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))

	}//	while (msg.message != WM_QUIT)

	UnregisterClass(m_tszClassName, m_hInst);

	return 0;

}//	INT CDxCore::Run()
//-------------------------------
HRESULT CDxCore::OnRender()
{
	m_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 120, 160), 1.0f, 0);

	if (FAILED(m_pD3DDevice->BeginScene()))
		return E_FAIL;
	
	if (FAILED(Render()))
		return E_FAIL;
	
	m_pD3DDevice->EndScene();

	// 후면버퍼 전면버퍼 교체( flipping)
	HRESULT hr = m_pD3DDevice->Present(0, 0, 0, 0);

	//	Process_2_1)	
	//	전체화면 상태에서 다른 윈도우가 활성화 될 때
	//	( 예 : ALT+TAB키, CTRL+ESC키 동작시) 호출 가능.
	//	디바이스가 소실된 것으로 설정.

	//	매 프레임마다 D3DERR_DEVICELOST가 리턴되는지 체크.
	//	디바이스가 소실 되면 리셋해줘야 함.
	if (D3DERR_DEVICELOST == hr)
		m_bDeviceLost = TRUE;

	return S_OK;

}//	HRESULT CDxCore::OnRender()
//-------------------------------
HRESULT	CDxCore::Idle()
{
	if (NULL == m_pD3DDevice)
		return E_FAIL;
	
	if (FAILED(FrameMove()))
		return E_FAIL;

	if (m_bDeviceLost == FALSE)
	{
		if (FAILED(OnRender()))
			return E_FAIL;

	}//	if (m_bDeviceLost == FALSE)	

	return S_OK;

}//	HRESULT	CDxCore::Idle()
//-------------------------------
LRESULT WINAPI CDxCore::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)	{ return g_pDxCore->MsgProc(hWnd, msg, wParam, lParam); }
//-------------------------------
LRESULT CDxCore::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//------------------------
	switch (msg)
	{
		case WM_KEYDOWN:
		{
			switch (wParam)
			{
				case VK_ESCAPE:
				{
					SendMessage(hWnd, WM_DESTROY, 0, 0);
					break;

				}//	case VK_ESCAPE:

			}//	switch (wParam)

			break;

		}//	case WM_KEYDOWN:

		case WM_DESTROY:
		{
			CleanUp();
			PostQuitMessage(0);
			break;

		}//	case WM_DESTROY:
				
	}//	switch (msg)
	//------------------------

	return DefWindowProc(hWnd, msg, wParam, lParam);

}//	LRESULT CDxCore::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//-------------------------------
INT CDxCore::Reset3D()
{
	//	Process_1_2)	화면 모드 체크 변수 전환.
	m_bWindowMode = !m_bWindowMode;

	//	Process_1_3)	Dx객체 소실 처리.
	//	-	Font 객체와 Sprite객체는 장치(Device)의 리셋전에
	//		OnLostDevice 처리 필요.
	OnLostDevice();
	m_pDxSpriteManager->OnLostDevice();

	//	Process_1_4)	D3DPRESENT_PARAMETERS 속성 일부 갱신.
	m_D3DPp.Windowed = m_bWindowMode;
	/*
		전체화면 인 경우 모니터 화면 주사율( 재생빈도 ) 설정.
		-	창 모드		:	0
			전체 화면	:	디바이스가 지원하는 수치 적용.
							IDirect3D9::EnumAdapterModes 으로 지원 수치 참고.
							보통 60Hz.
	*/	
	m_D3DPp.FullScreen_RefreshRateInHz = m_bWindowMode ? D3DPRESENT_RATE_DEFAULT : 60;

	//	Process_1_5)	디바이스 리셋.
	if (FAILED(m_pD3DDevice->Reset(&m_D3DPp)))
		return E_FAIL;
	
	//	Process_1_6)	화면 모드에 따라 윈도우 속성 갱신.
	if (m_bWindowMode)
	{
		//	윈도우 속성 설정.
		//	GWL_STYLE - 윈도우 스타일.
		SetWindowLong(m_hWnd, GWL_STYLE, m_dwWinStyle);

		//	윈도우 위치 설정.
		//	HWND_NOTOPMOST - 해당 윈도우가 화면상에서 팝업 상태라면 해제.
		//	SWP_SHOWWINDOW - 윈도우 바로 노출.
		SetWindowPos(m_hWnd, HWND_NOTOPMOST
			, m_rcWin.left
			, m_rcWin.top
			, m_rcWin.right - m_rcWin.left
			, m_rcWin.bottom - m_rcWin.top
			, SWP_SHOWWINDOW
		);		
	}else
		//	WS_POPUP - 팝업 윈도우 스타일.
		SetWindowLong(m_hWnd, GWL_STYLE, WS_POPUP | WS_VISIBLE);
	
	Sleep(100);

	//	Process_1_7)	DX 객체 리셋.
	//	-	Font 객체와 Sprite객체는 장치(Device)의 리셋 후에
	//		OnResetDevice 처리 필요.
	m_pDxSpriteManager->OnResetDevice();

	OnResetDevice();

}//	INT CDxCore::Reset3D()
//-------------------------------
void CDxCore::UpdateFPS()
{
	static int frameCount = 0;
	static float timeElapsed = 0.0f;
	static DWORD dwLastTime = timeGetTime();

	DWORD curTime = timeGetTime();
	float timeDelta = (curTime - dwLastTime) * 0.001f;

	timeElapsed += timeDelta;

	++frameCount;

	if (timeElapsed >= 1.0f)
	{
		float fps = (float)frameCount / timeElapsed;
		sprintf(m_tszFPS, TEXT("게임속도 FPS: %f"), fps);     //FPS출력 하는 소스

		frameCount = 0;
		timeElapsed = 0.0f;

	}//	if (timeElapsed >= 1.0f)

	dwLastTime = curTime;

}//	void CDxCore::UpdateFPS()
//-------------------------------
CDxCore::~CDxCore() { }
//-------------------------------