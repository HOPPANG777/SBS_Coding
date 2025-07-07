#pragma once
#include "Global.h"
class CMeshColor :	public CMesh
{
protected:
	virtual HRESULT InitVB();
	virtual HRESULT	InitIB();
public:		
	virtual void Render();
};