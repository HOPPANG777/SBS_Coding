//======================================================
#include "Global.h"
//======================================================
HRESULT CMeshColor::InitVB()
{
	SVtxD vtx[8];

	vtx[0]._pos = D3DXVECTOR3(-1, 1, 1);
	vtx[0]._color = 0xffffff00;

	vtx[1]._pos = D3DXVECTOR3(1, 1, 1);
	vtx[1]._color = 0xffffff00;

	vtx[2]._pos = D3DXVECTOR3(1, 1, -1);
	vtx[2]._color = 0xffffff00;

	vtx[3]._pos = D3DXVECTOR3(-1, 1, -1);
	vtx[3]._color = 0xffff00ff;


	vtx[4]._pos = D3DXVECTOR3(-1, -1, 1);
	vtx[4]._color = 0xffff00ff;

	vtx[5]._pos = D3DXVECTOR3(1, -1, 1);
	vtx[5]._color = 0xffff00ff;

	vtx[6]._pos = D3DXVECTOR3(1, -1, -1);
	vtx[6]._color = 0xffffff00;

	vtx[7]._pos = D3DXVECTOR3(-1, -1, -1);
	vtx[7]._color = 0xffffff00;

	// 정점버퍼를 생성한다.
	if (FAILED(GetDev()->CreateVertexBuffer(sizeof(vtx) , 0, D3DFVF_XYZDIFFUSE, D3DPOOL_MANAGED, &_pVB, NULL)))
		return E_FAIL;

	// 정점데이터를 채운다.
	// Lock은 현재의 독점을 유지
	void* pvtx;
	if (FAILED(_pVB->Lock(0, sizeof(vtx), (void**)&pvtx, 0)))
		return E_FAIL;

	memcpy(pvtx, vtx, sizeof(vtx));

	_pVB->Unlock();

	return S_OK;
}
//------------------------------------
HRESULT	CMeshColor::InitIB()
{
	SIdx indices[] =
	{
		{ 0,1,2 }, { 0,2,3 },

		{ 4,6,5 }, { 4,7,6 },

		{ 0,3,7 }, { 0,7,4 },

		{ 1,5,6 }, { 1,6,2 },

		{ 3,2,6 }, { 3,6,7 },

		{ 0,4,5 }, { 0,5,1 }
	};

	if (FAILED(GetDev()->CreateIndexBuffer( sizeof(indices), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &_pIB, NULL )))
		return E_FAIL;

	void* pIndices;
	if (FAILED(_pIB->Lock( 0, sizeof(SIdx), (void**)&pIndices, 0)))
		return E_FAIL;

	memcpy(pIndices, indices, sizeof(indices));

	_pIB->Unlock();

	return S_OK;

}//	HRESULT	CVtxDiffuseBox::InitIB()
//------------------------------------
void CMeshColor::Render()
{
	//	월드 행렬 설정.
	FrameUpdate();

	// 현재 은면제거 상태 확인.
	DWORD dCullMode = 0;
	GetDev()->GetRenderState( D3DRS_CULLMODE, &dCullMode );

	// 은면제거 비활성화
	GetDev()->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	// 정점을 디바이스에 연결
	GetDev()->SetStreamSource( 0, GetVtxBuff(), 0, sizeof(SVtxD) );
	// 정점 포멧을 설정
	GetDev()->SetFVF( D3DFVF_XYZDIFFUSE );

	//	인덱스 버퍼 7)
	//	-	인덱스 버퍼를 이용한 렌더링 설정.
	GetDev()->SetIndices( GetIdxBuff() );
	// 렌더링
	GetDev()->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,	//	Type
		0,					//	BaseVertexIndex
		0,					//	MinIndex
		8,					//	NumVertices
		0,					//	StartIndex
		12					//	PrimitiveCount
	);
	// 은면 제거 상태 복구.
	GetDev()->SetRenderState(D3DRS_CULLMODE, dCullMode);

}//	void CMeshColor::Render()
//======================================================