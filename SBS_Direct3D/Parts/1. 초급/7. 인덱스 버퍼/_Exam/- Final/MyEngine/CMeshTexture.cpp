//======================================================
#include "Global.h"
//======================================================
HRESULT CMeshTexture::Create(LPDIRECT3DDEVICE9 pDev)
{
	_txtr.Create(pDev, "texture/myfamily.jpg",false);
	
	return CMesh::Create(pDev);
}
//--------------------------------
HRESULT CMeshTexture::InitVB()
{
	SVtxTxtr vtx[] =
	{
		//	Front..
		{D3DXVECTOR3(-1, -1, -1), 0,1 },
		{D3DXVECTOR3(-1, 1, -1), 0,0 },
		{D3DXVECTOR3(1, -1, -1), 1,1 },

		{D3DXVECTOR3(1, 1, -1), 1,0 },
		{D3DXVECTOR3(1, -1, -1), 1,1 },
		{D3DXVECTOR3(-1, 1, -1), 0,0 },

		//	Right..
		{D3DXVECTOR3(1, 1, -1), 0,0 },
		{D3DXVECTOR3(1, -1, 1), 1,1 },
		{D3DXVECTOR3(1, -1, -1), 0,1 },

		{D3DXVECTOR3(1, 1, -1), 0,0 },
		{D3DXVECTOR3(1, 1, 1), 1,0 },
		{D3DXVECTOR3(1, -1, 1), 1,1 },

		//	Back..
		{D3DXVECTOR3(1, 1, 1), 0,0 },
		{D3DXVECTOR3(-1, -1, 1), 1,1 },
		{D3DXVECTOR3(1, -1, 1), 0,1 },

		{D3DXVECTOR3(1, 1, 1), 0,0 },
		{D3DXVECTOR3(-1, 1, 1), 1,0 },
		{D3DXVECTOR3(-1, -1, 1), 1,1 },

		//	Left..
		{D3DXVECTOR3(-1, 1, 1), 0,0 },
		{D3DXVECTOR3(-1, -1, -1), 1,1 },
		{D3DXVECTOR3(-1, -1, 1), 0,1 },

		{D3DXVECTOR3(-1, 1, 1), 0,0 },
		{D3DXVECTOR3(-1, 1, -1), 1,0 },
		{D3DXVECTOR3(-1, -1, -1), 1,1 },

		//	Bottom..
		{D3DXVECTOR3(-1, -1, -1), 0,0 },
		{D3DXVECTOR3(1, -1, 1), 1,1 },
		{D3DXVECTOR3(-1, -1, 1), 0,1 },

		{D3DXVECTOR3(-1, -1, -1), 0,0 },
		{D3DXVECTOR3(1, -1, 1), 1,1 },
		{D3DXVECTOR3(1, -1, -1), 1,0 },

		//	Top..
		{D3DXVECTOR3(-1, 1, 1), 0,0 },
		{D3DXVECTOR3(1, 1, 1), 1,0 },
		{D3DXVECTOR3(1, 1, -1), 1,1 },

		{D3DXVECTOR3(-1, 1, 1), 0,0 },
		{D3DXVECTOR3(1, 1, -1), 1,1 },
		{D3DXVECTOR3(-1, 1, -1), 0,1 },
	};

	// 정점버퍼를 생성한다.
	if (FAILED(GetDev()->CreateVertexBuffer(sizeof(vtx)
		, 0
		, D3DFVF_XYZTEX
		, D3DPOOL_MANAGED
		, &_pVB
		, NULL)))
	{
		return E_FAIL;
	}

	// 정점데이터를 채운다.
	// Lock은 현재의 독점을 유지
	void* pvtx;
	if (FAILED(_pVB->Lock(0, sizeof(vtx), (void**)&pvtx, 0)))
		return E_FAIL;

	memcpy(pvtx, vtx, sizeof(vtx));

	_pVB->Unlock();

	return S_OK;
}
//--------------------------------
void CMeshTexture::Render()
{
	FrameUpdate();

	// 현재 은면제거 상태 확인.
	DWORD dCullMode = 0;
	GetDev()->GetRenderState(D3DRS_CULLMODE, &dCullMode);

	// 은면제거 비활성화
	GetDev()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	/*	텍스쳐 - 3)
		-	텍스쳐 지정. */
	GetDev()->SetTexture(0, _txtr.GetTexture());

	// 정점을 디바이스에 연결
	GetDev()->SetStreamSource(0, _pVB, 0, sizeof(SVtxTxtr));
	// 정점 포멧을 설정
	GetDev()->SetFVF(D3DFVF_XYZTEX);
	// 렌더링
	//GetDev()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	GetDev()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);

	// 은면 제거 상태 복구.
	GetDev()->SetRenderState(D3DRS_CULLMODE, dCullMode);
}
//--------------------------------
void CMeshTexture::Destroy()
{
	CMesh::Destroy();
	_txtr.Destroy();
}
//======================================================