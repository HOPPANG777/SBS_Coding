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

public:
	CDxTexture();
	virtual ~CDxTexture();

	virtual INT		Create(LPDIRECT3DDEVICE9 pDev, const char* sFile);
	virtual void	Destroy();
	void Draw(LPD3DXSPRITE spr, D3DXVECTOR3 vecPos);
	void Draw(LPD3DXSPRITE spr);

	INT		GetImageWidth() { return m_ImgInfo.Width; }
	INT		GetImageHeight() { return m_ImgInfo.Height; }
	RECT	GetImageRect();
	LPDIRECT3DTEXTURE9 GetTexture() { return m_pTx; }
	D3DXVECTOR3 GetImageCenter();

	
};

#endif