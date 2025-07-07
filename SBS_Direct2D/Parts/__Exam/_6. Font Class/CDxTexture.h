//========================================================
#pragma once
//========================================================
#ifndef _DXTEXTURE_H_
#define _DXTEXTURE_H_
//========================================================
class CDxTexture
{
protected:
	LPDIRECT3DDEVICE9	m_pDev;
	D3DXIMAGE_INFO		m_ImgInfo;
	LPDIRECT3DTEXTURE9	m_pTx;
	D3DXVECTOR3			m_vecPos;
	D3DXVECTOR3			m_vecCenter;
	D3DXCOLOR			m_color;
	RECT				m_drawRect;
	DWORD				m_dwColorKey;	//	ÄÃ·¯Å°.

public:
	CDxTexture();
	virtual ~CDxTexture();

	virtual INT		Create(LPDIRECT3DDEVICE9 pDev, const char* sFile, DWORD colorKey = 0);
	virtual void	Destroy();
	void Draw(LPD3DXSPRITE spr, D3DXVECTOR3 vecPos);
	void Draw(LPD3DXSPRITE spr);


	void SetPos(D3DXVECTOR3 vecPos) { m_vecPos = vecPos; }
	void SetPos2D(float posX, float posY)
	{
		D3DXVECTOR3 tmpPos(posX, posY, 0);
		SetPos(tmpPos);
	}
	D3DXVECTOR3 GetPos() { return m_vecPos; }
	INT		GetImageWidth() { return m_ImgInfo.Width; }
	INT		GetImageHeight() { return m_ImgInfo.Height; }
	RECT	GetImageRect();
	D3DXVECTOR3 GetSrcImageCenter();
	void SetCenter(D3DXVECTOR3 vecCenter) { m_vecCenter = vecCenter; }

	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTx; }
	
};

#endif