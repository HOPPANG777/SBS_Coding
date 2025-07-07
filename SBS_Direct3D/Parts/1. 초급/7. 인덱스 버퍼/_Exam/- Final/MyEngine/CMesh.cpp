//================================================
#include "Global.h"
//================================================
CMesh::CMesh()
{
	_pVB = NULL;
	_pIB = NULL;
	_pDev = NULL;
	_pos = D3DXVECTOR3(0, 0, 0);

}//	CVtx::CVtx()
//-------------------------------
CMesh::~CMesh() { Destroy(); }
//-------------------------------
void CMesh::Destroy()
{
	SAFE_RELEASE(_pVB);
	SAFE_RELEASE(_pIB);
}
//-------------------------------
HRESULT CMesh::Create(LPDIRECT3DDEVICE9 pDev)
{
	_pDev = pDev;

	if (FAILED(InitVB()))
		return E_FAIL;

	if (FAILED(InitIB()))
		return E_FAIL;

	return S_OK;
}
//-------------------------------
void CMesh::FrameUpdate()
{
	D3DXMATRIX tmp;
	D3DXMatrixIdentity(&tmp);
	D3DXMatrixTranslation(&tmp, _pos.x, _pos.y, _pos.z);
	_pDev->SetTransform(D3DTS_WORLD, &tmp);
}
//-------------------------------
//================================================