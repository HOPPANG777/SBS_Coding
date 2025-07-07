//======================================================
#include "Global.h"
//======================================================
HRESULT CMeshTextureNormal::InitVB()
{
	SVtxTxtrNormal vtx[] =
	{
		//	Front..
		{D3DXVECTOR3(-1, -1, -1), D3DXVECTOR3(0, 0, -1), 0,1 },
		{D3DXVECTOR3(-1, 1, -1), D3DXVECTOR3(0, 0, -1), 0,0 },
		{D3DXVECTOR3(1, -1, -1), D3DXVECTOR3(0, 0, -1), 1,1 },
		
		{D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 0, -1), 1,0 },
		{D3DXVECTOR3(1, -1, -1), D3DXVECTOR3(0, 0, -1), 1,1 },
		{D3DXVECTOR3(-1, 1, -1), D3DXVECTOR3(0, 0, -1), 0,0 },

		//	Right..
		{D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(1, 0, 0), 0,0 },
		{D3DXVECTOR3(1, -1, 1), D3DXVECTOR3(1, 0, 0), 1,1 },
		{D3DXVECTOR3(1, -1, -1), D3DXVECTOR3(1, 0, 0), 0,1 },

		{D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(1, 0, 0), 0,0 },
		{D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(1, 0, 0), 1,0 },
		{D3DXVECTOR3(1, -1, 1), D3DXVECTOR3(1, 0, 0), 1,1 },

		//	Back..
		{D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 0, 1), 0,0 },
		{D3DXVECTOR3(-1, -1, 1), D3DXVECTOR3(0, 0, 1), 1,1 },
		{D3DXVECTOR3(1, -1, 1), D3DXVECTOR3(0, 0, 1), 0,1 },

		{D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 0, 1), 0,0 },
		{D3DXVECTOR3(-1, 1, 1), D3DXVECTOR3(0, 0, 1), 1,0 },
		{D3DXVECTOR3(-1, -1, 1), D3DXVECTOR3(0, 0, 1), 1,1 },

		//	Left..
		{D3DXVECTOR3(-1, 1, 1), D3DXVECTOR3(-1, 0, 0), 0,0 },
		{D3DXVECTOR3(-1, -1, -1),D3DXVECTOR3(-1, 0, 0), 1,1  },
		{D3DXVECTOR3(-1, -1, 1), D3DXVECTOR3(-1, 0, 0), 0,1 },

		{D3DXVECTOR3(-1, 1, 1), D3DXVECTOR3(-1, 0, 0), 0,0 },
		{D3DXVECTOR3(-1, 1, -1), D3DXVECTOR3(-1, 0, 0), 1,0 },
		{D3DXVECTOR3(-1, -1, -1), D3DXVECTOR3(-1, 0, 0), 1,1 },

		//	Bottom..
		{D3DXVECTOR3(-1, -1, -1), D3DXVECTOR3(0, -1, 0), 0,0 },
		{D3DXVECTOR3(1, -1, 1), D3DXVECTOR3(0, -1, 0), 1,1 },
		{D3DXVECTOR3(-1, -1, 1), D3DXVECTOR3(0, -1, 0), 0,1 },

		{D3DXVECTOR3(-1, -1, -1), D3DXVECTOR3(0, -1, 0), 0,0 },
		{D3DXVECTOR3(1, -1, 1), D3DXVECTOR3(0, -1, 0), 1,1 },
		{D3DXVECTOR3(1, -1, -1), D3DXVECTOR3(0, -1, 0), 1,0 },

		//	Top..
		{D3DXVECTOR3(-1, 1, 1), D3DXVECTOR3(0, 1, 0), 0,0 },
		{D3DXVECTOR3(1, 1, 1), D3DXVECTOR3(0, 1, 0), 1,0 },
		{D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 1, 0), 1,1 },

		{D3DXVECTOR3(-1, 1, 1), D3DXVECTOR3(0, 1, 0), 0,0 },
		{D3DXVECTOR3(1, 1, -1), D3DXVECTOR3(0, 1, 0), 1,1 },
		{D3DXVECTOR3(-1, 1, -1), D3DXVECTOR3(0, 1, 0), 0,1 },
		
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

}//	HRESULT CMeshTextureNormal::InitVB()
//--------------------------------
void CMeshTextureNormal::SetMaterial()
{
	D3DMATERIAL9 mtrl = { 0 };
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;

	GetDev()->SetMaterial(&mtrl);
}
//--------------------------------
void CMeshTextureNormal::SetLight()
{
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	memset(&light, 0, sizeof(D3DLIGHT9));
	light.Type = D3DLIGHT_DIRECTIONAL;	//	조명 종류.
	light.Diffuse.r = 1.0f;				//	조명 색상.
	light.Diffuse.g = 1.0f;
	light.Diffuse.b = 0.0f;

	vecDir = D3DXVECTOR3(cosf(timeGetTime() / 500.f), 1.0f, sinf(timeGetTime() / 500.f));
	//vecDir = D3DXVECTOR3(1,1,1);

	//	조명 방향.	
	D3DXVec3Normalize((D3DXVECTOR3*)&light.Direction, &vecDir);

	light.Range = 1000.0f;	// 조명 유효 범위.

	GetDev()->SetRenderState(D3DRS_LIGHTING, TRUE);		// 광원설정 On.

	//	디바이스에 조명 설정.
	GetDev()->SetLight(0, &light);

	//	조명 활성화.
	GetDev()->LightEnable(0, TRUE);

	// 주변 광원 설정.
	GetDev()->SetRenderState(D3DRS_AMBIENT, 0x11111111);
}
//--------------------------------
void CMeshTextureNormal::Render()
{
	FrameUpdate();

	SetMaterial();

	SetLight();
	
	// 현재 은면제거 상태 확인.
	DWORD dCullMode = 0;
	GetDev()->GetRenderState(D3DRS_CULLMODE, &dCullMode);

	// 은면제거 비활성화
	GetDev()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	/*	텍스쳐 - 3)
		-	텍스쳐 지정. */
	GetDev()->SetTexture(0, _txtr.GetTexture());

	// 정점을 디바이스에 연결
	GetDev()->SetStreamSource(0, _pVB, 0, sizeof(SVtxTxtrNormal));
	// 정점 포멧을 설정
	GetDev()->SetFVF(D3DFVF_XYZTEXNORMAL);
	// 렌더링
	//GetDev()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	GetDev()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 12);

	// 은면 제거 상태 복구.
	GetDev()->SetRenderState(D3DRS_CULLMODE, dCullMode);
}
//======================================================