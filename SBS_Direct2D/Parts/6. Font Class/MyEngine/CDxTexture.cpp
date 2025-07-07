#include "Global.h"
//========================================================
CDxTexture::CDxTexture()
{
	m_pDev	= NULL;
	m_pTx	= NULL;	
	m_color = D3DXCOLOR(1, 1, 1, 1);
	memset(&m_ImgInfo, 0, sizeof m_ImgInfo);
	m_dwColorKey = 0;

}//	CDxTexture::CDxTexture()
//========================================================
CDxTexture::~CDxTexture() {	Destroy(); }
//========================================================
void CDxTexture::Destroy() { SAFE_RELEASE(m_pTx); }
//========================================================
INT CDxTexture::Create(LPDIRECT3DDEVICE9 pDev, char* sFile, DWORD dwColorKey)
{
	m_pDev	= pDev;
	m_dwColorKey = dwColorKey;
	if(FAILED(D3DXCreateTextureFromFileEx(
		m_pDev
		, sFile
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 1
		, 0
		, D3DFMT_UNKNOWN
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE
		, D3DX_FILTER_NONE
		, m_dwColorKey
		, &m_ImgInfo
		, NULL
		, &m_pTx
		)) )
	{
		m_pTx = NULL;
		MessageBox( GetActiveWindow()
					, "Create Texture Failed"
					, sFile
					, MB_ICONEXCLAMATION
					);
		return -1;
	}

	m_vecPivot = GetImageCenter();
	m_drawRect = GetImageRect();

	return 0;

}//	INT CDxTexture::Create(LPDIRECT3DDEVICE9 pDev, char* sFile)
//========================================================
RECT CDxTexture::GetImageRect()
{
	RECT tmp;
	tmp.left = 0;
	tmp.top = 0;
	tmp.right = m_ImgInfo.Width;
	tmp.bottom = m_ImgInfo.Height;

	return tmp;
}
//========================================================
D3DXVECTOR3 CDxTexture::GetImageCenter()
{
	D3DXVECTOR3	vcCenter;	
	vcCenter.x = (LONG)GetImageWidth() * 0.5f;
	vcCenter.y = (LONG)GetImageHeight() * 0.5f;
	vcCenter.z = 0;

	return vcCenter;
}
//========================================================
void CDxTexture::Draw(LPD3DXSPRITE spr, D3DXVECTOR3 vecPos)
{
	m_vecPos = vecPos;	
	Draw(spr);
}
//========================================================
void CDxTexture::Draw( LPD3DXSPRITE spr )
{
	spr->Draw(GetTexture(),
		&m_drawRect,
		&m_vecPivot,
		&m_vecPos,		
		m_color);
}
//========================================================//