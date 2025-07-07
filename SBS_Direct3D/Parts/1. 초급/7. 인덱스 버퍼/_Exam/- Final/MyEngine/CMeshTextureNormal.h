#pragma once
#include "Global.h"
class CMeshTextureNormal :	public CMeshTexture
{
protected:
	virtual HRESULT InitVB();
public:
	virtual void Render();
	void SetMaterial();
	void SetLight();
};

