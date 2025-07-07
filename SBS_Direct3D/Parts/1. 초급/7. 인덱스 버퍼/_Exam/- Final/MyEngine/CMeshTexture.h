#pragma once
#include "Global.h"
class CMeshTexture : public CMesh
{	
protected:
	CDxTexture _txtr;
	virtual HRESULT InitVB();
public:
	virtual HRESULT Create(LPDIRECT3DDEVICE9 pDev);
	virtual void Render();
	virtual void Destroy();
};

