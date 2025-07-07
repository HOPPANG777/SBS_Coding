//============================================
#include "Global.h"
//============================================
CMyGame* g_pMyGame;
//============================================
CMyGame::CMyGame()
{
	_isLBttnPress = false;
	_dwLBttnClickTime = 0;
}
//============================================
CMyGame::~CMyGame()	{}
//============================================
INT		CMyGame::Init()
{
	//	텍스쳐.
	if (FAILED(m_dxTxtrTest.Create(GetDev(), "texture/myfamily.jpg")))
		return -1;

	//	텍스쳐.(애니메이션)
	m_pDxTxtrAnim = new CDxTextureAnim(30, 10);
	if (FAILED(m_pDxTxtrAnim->Create(GetDev(), "texture/animate.bmp", 0xFF000000)))
		return -1;
	m_pDxTxtrAnim->SetPivot(D3DXVECTOR3(16, 16, 0));

	//	폰트.
	m_pDxFont = new CDxFont();
	//if (FAILED(m_pDxFont->Create(m_pD3DDevice, _T("굴림체"), 20, FW_LIGHT)))
	if (FAILED(m_pDxFont->Create(GetDev(), _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;
	m_pDxFont->SetPos(0, 0);
	m_pDxFont->SetSize(200, 50);

	_pDxFontLBttnMsg = new CDxFont();
	if (FAILED(_pDxFontLBttnMsg->Create(GetDev(), _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;
	_pDxFontLBttnMsg->SetPos(300, 550);
	_pDxFontLBttnMsg->SetSize(200, 50);

	//	입력 관리자.
	m_pInputManager = new CInputManager();
	m_pInputManager->Create(m_hWnd);


	return 0;

}//	INT		CMyGame::Init()
//============================================
INT		CMyGame::Render()
{
	//	텍스쳐.
	D3DXVECTOR3	vcPos(m_dwScrWidth * 0.5f, m_dwScrHeight * 0.5f, 0);
	m_dxTxtrTest.Draw(GetSprite(), vcPos);

	//	텍스쳐.(애니메이션.)
	m_pDxTxtrAnim->Draw(GetSprite());

	//	폰트.
	//m_pDxFont->Draw(GetSprite(), _T("우리 가족 입니다 ^^"), 0, 0, 300, 50, D3DXCOLOR(1, 1, 0, 1), DT_LEFT);
	m_pDxFont->Draw(GetSprite(), _T("우리 가족 입니다 ^^"), D3DXCOLOR(1, 1, 0, 1), DT_LEFT);

	if (m_pInputManager)
	{
		//	마우스 버튼
		memset(m_tszMouseMsg, 0, sizeof(m_tszMouseMsg));
		m_pDxFont->Draw(GetSprite(), _T("현재 클릭한 마우스 버튼 : "), 0, 50, 300, 50, D3DXCOLOR(0, 0, 0, 1), DT_LEFT);

		_isLBttnPress = false;
		if (m_pInputManager->MouseBtnDown(0))
			_dwLBttnClickTime = timeGetTime();

		if (m_pInputManager->MouseBtnPress(0))
		{
			sprintf(m_tszMouseMsg, "마우스 왼쪽 버튼 클릭!!");
			m_pDxFont->Draw(GetSprite(), m_tszMouseMsg, 280, 50, 220, 50, D3DXCOLOR(1, 0.2f, 0, 1), DT_LEFT);
			_isLBttnPress = true;
		}

		if (m_pInputManager->MouseBtnPress(1))
		{
			sprintf(m_tszMouseMsg, "마우스 우측 버튼 클릭!!");
			m_pDxFont->Draw(GetSprite(), m_tszMouseMsg, 280, 50, 220, 50, D3DXCOLOR(1, 0.2f, 0, 1), DT_LEFT);
		}

		if (m_pInputManager->MouseBtnPress(2))
		{
			sprintf(m_tszMouseMsg, "마우스 가운데 버튼 클릭!!");
			m_pDxFont->Draw(GetSprite(), m_tszMouseMsg, 280, 50, 220, 50, D3DXCOLOR(1, 0.2f, 0, 1), DT_LEFT);
		}

		//	키보드
		memset(m_tszKbdMsg, 0, sizeof(m_tszKbdMsg));
		int curIdx = 0;
		for (curIdx = 0; curIdx < 256; ++curIdx)
		{
			if (m_pInputManager->KeyDown(curIdx))
			{
				sprintf(m_tszKbdMsg, "Key Down : %c / %d", curIdx, curIdx);
				m_pDxFont->Draw(GetSprite(), m_tszKbdMsg, 280, 350, 220, 50, D3DXCOLOR(1, 0.2f, 0, 1), DT_LEFT);
			}
		}

		for (curIdx = 0; curIdx < 256; ++curIdx)
		{
			if (m_pInputManager->KeyUp(curIdx))
			{
				sprintf(m_tszKbdMsg, "Key Up : %c / %d", curIdx, curIdx);
				m_pDxFont->Draw(GetSprite(), m_tszKbdMsg, 280, 450, 220, 50, D3DXCOLOR(1, 0.2f, 0, 1), DT_LEFT);
			}
		}

		for (curIdx = 0; curIdx < 256; ++curIdx)
		{
			if (m_pInputManager->KeyPress(curIdx))
			{
				sprintf(m_tszKbdMsg, "Key Press : %c / %d", curIdx, curIdx);
				m_pDxFont->Draw(GetSprite(), m_tszKbdMsg, 280, 400, 220, 50, D3DXCOLOR(1, 0.2f, 0, 1), DT_LEFT);
			}
		}

		//	마우스 좌표		
		sprintf(m_tszMouseMsg, "마우스 좌표 x : %f, y : %f", m_pInputManager->GetMousePos().x, m_pInputManager->GetMousePos().y);
		m_pDxFont->Draw(GetSprite(), m_tszMouseMsg, 0, 100, 500, 50, D3DXCOLOR(1, 0, 1, 1), DT_LEFT);

		//	마우스 이동 옵셋 및 휠 정보.
		static RECT rc = { 0,200,500,130 };
		D3DXVECTOR3	vcEps = m_pInputManager->GetMouseEps();
		rc.top += long(vcEps.z / 40);
		rc.bottom = rc.top + 30;
		sprintf(m_tszMouseWheelMsg, "마우스 이동 옵셋(%.f, %.f, %.f), 휠: %d", vcEps.x, vcEps.y, vcEps.z, rc.top);

		m_pDxFont->GetFont()->DrawText(GetSprite(), m_tszMouseWheelMsg, -1, &rc, 0, D3DXCOLOR(0, 0, 1, 1));

		if (_isLBttnPress)
		{
			DWORD elapsedTime = timeGetTime() - _dwLBttnClickTime;
			float rate = (float)elapsedTime / PRESSINGTIME;
			if (rate > 1.0f)
			{
				rate = 1.0f;
				sprintf(_tszLBttnMsg, "에너지 충전 완료!!!");
			}
			else
				sprintf(_tszLBttnMsg, "에너지 충전 중... : %.2f%%", rate*100);

			_pDxFontLBttnMsg->Draw(GetSprite(), _tszLBttnMsg, D3DXCOLOR(1, 0.5f, 0.5f, 1), DT_LEFT);

		}//	if (_isLBttnPress)
		
	}//	if (m_pInputManager)

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	//	애니메이션 텍스쳐.
	DWORD dwTime = timeGetTime();
	m_pDxTxtrAnim->OnUpdateFrame(dwTime);

	m_pDxTxtrAnim->SetPos2D(cosf(D3DX_PI * dwTime * 0.0001f), sinf(D3DX_PI * dwTime * 0.0003f));
	D3DXVECTOR3 tmp = m_pDxTxtrAnim->GetPos();
	tmp *= 100.0f;
	tmp += D3DXVECTOR3(400, 300, 0);
	m_pDxTxtrAnim->SetPos2D(tmp.x, tmp.y);

	//	폰트 이동.
	D3DXVECTOR3 tmpPos = m_pDxFont->GetPos();
	//int tmpRange = tmpPos.x + m_pDxFont->GetWidth();
	int tmpRange = tmpPos.x + m_pDxFont->GetTextWidth(GetSprite(), _T("우리 가족 입니다 ^^"));

	if (_isForward)
	{
		tmpPos.x += 1;

		if (tmpRange > m_dwScrWidth)
			_isForward = !_isForward;
	}
	else
	{
		tmpPos.x -= 1;

		if (tmpPos.x < 0)
			_isForward = !_isForward;
	}

	m_pDxFont->SetPos(tmpPos.x, tmpPos.y);

	//	입력 처리.
	if (m_pInputManager)
	{
		m_pInputManager->FrameMove();

		if (CInputManager::DBLCLK == m_pInputManager->MouseBtnState(0))
		{
			TCHAR	sMsg[1024] = { 0 };
			sprintf(sMsg, _T("마우스 좌측 버튼 더블 클릭!!"));
			SetWindowText(m_hWnd, sMsg);
		}

		if (CInputManager::DBLCLK == m_pInputManager->MouseBtnState(1))
		{
			TCHAR	sMsg[1024] = { 0 };
			sprintf(sMsg, _T("마우스 우측 버튼 따블 클릭!!"));
			SetWindowText(m_hWnd, sMsg);
		}

		if (CInputManager::DBLCLK == m_pInputManager->MouseBtnState(2))
		{
			TCHAR	sMsg[1024] = { 0 };
			sprintf(sMsg, _T("마우스 가운데 버튼 따블 클릭!!"));
			SetWindowText(m_hWnd, sMsg);
		}

	}//	if (m_pInputManager)


	return S_OK;
}
//============================================
void	CMyGame::Destroy()
{
	m_dxTxtrTest.Destroy();
	m_pDxTxtrAnim->Destroy();
	m_pDxFont->Destroy();
	_pDxFontLBttnMsg->Destroy();

	SAFE_DELETE( m_pInputManager );
	SAFE_DELETE( m_pDxTxtrAnim );
	SAFE_DELETE( m_pDxFont );
	SAFE_DELETE( _pDxFontLBttnMsg );
}
//============================================
LRESULT CMyGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pInputManager)
		m_pInputManager->MsgProc(hWnd, msg, wParam, lParam);

	return CCore::MsgProc(hWnd, msg, wParam, lParam);
}
//============================================//