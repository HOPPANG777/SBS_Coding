//============================================
#include "Global.h"
//============================================
CMyGame::CMyGame()	{}
//============================================
CMyGame::~CMyGame()	{}
//============================================
//	인덱스 버퍼 4)
//	-	버텍스 버퍼 초기화.
//============================================
INT		CMyGame::Init()
{
	m_pDxFont = new CDxFont();
	if (FAILED(m_pDxFont->Create(GetDev(), _T("궁서체"), 20, FW_BOLD)))
		return E_FAIL;

	m_pGrid = new CDxGrid();
	m_pGrid->Create(GetDev());

	m_BoxColor.Create(GetDev());
	m_BoxColor.SetPos(-5, 0, 0);

	m_BoxTexture.Create(GetDev());
	m_BoxTexture.SetPos(0, 0, 0);

	m_BoxTextureNormal.Create(GetDev());
	m_BoxTextureNormal.SetPos(5, 0, 0);
	
	m_pMesh[0] = &m_BoxColor;
	m_pMesh[1] = &m_BoxTexture;
	m_pMesh[2] = &m_BoxTextureNormal;

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
	//	그리드 렌더링.
	m_pGrid->FrameMove();
	m_pGrid->Render();

	//	박스 그리기.
	for (int cur = 0; cur < 3; ++cur)
		m_pMesh[cur]->Render();

	return 0;

}//	INT		CMyGame::Render()
//============================================
INT		CMyGame::FrameMove()
{
	UpdateFPS();

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
		D3DXVECTOR3 mouseEps = GetInput()->GetMouseEps();
		bool isLShift = GetInput()->KeyPress(VK_LSHIFT);

		GetCam()->FrameMove(isForward, isBack, isLeft, isRight, isUp, isDown, isMouseRBttnPress, mouseEps, isLShift);

	}//	if (m_pInputManager)

	return S_OK;
}
//============================================
void	CMyGame::Destroy()
{
	for (int cur = 0; cur < 3; ++cur)
		m_pMesh[cur]->Destroy();

	SAFE_DELETE(m_pGrid);
	SAFE_DELETE(m_pDxFont);	
}
//============================================
LRESULT CMyGame::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (GetInput())
		GetInput()->MsgProc(hWnd, msg, wParam, lParam);

	return CCore::MsgProc(hWnd, msg, wParam, lParam);
}
//============================================//