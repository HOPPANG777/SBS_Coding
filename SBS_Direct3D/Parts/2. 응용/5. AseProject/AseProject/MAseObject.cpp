//==========================================================================================
#include "StdAfx.h"
#include "MAseObject.h"
#include "MD3DFramework.h"
#include "MArchive.h"
//==========================================================================================
CMAseObject::CMAseObject() : D3DDevice(nullptr), VertexBuffer(nullptr), Texture(nullptr) { }
CMAseObject::~CMAseObject() { Clear(); }
//------------------------------------------------------------------------------------------
BOOL CMAseObject::Init(LPDIRECT3DDEVICE9 d3DDevice)
{
	D3DDevice = d3DDevice;

	if (D3DDevice == nullptr) return FALSE;
	return TRUE;

}//	BOOL CMAseObject::Init(LPDIRECT3DDEVICE9 d3DDevice)
//------------------------------------------------------------------------------------------
void CMAseObject::Clear()
{
	if (D3DDevice != nullptr) D3DDevice = nullptr;
	if (VertexBuffer != nullptr)
	{
		VertexBuffer->Release();
		VertexBuffer = nullptr;
	}

	if (Texture != nullptr)
	{
		Texture->Release();
		Texture = nullptr;
	}

}//	void CMAseObject::Clear()
//------------------------------------------------------------------------------------------
//	좌표 변환 세팅..
void CMAseObject::Update()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationY(&matWorld, GetTickCount() / 1000.0f);

	D3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEyePt(0.0f, 140.0f, -100.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 30.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	D3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f);
	D3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);

}//	void CMAseObject::Update()
//------------------------------------------------------------------------------------------
void CMAseObject::Render()
{
	//	텍스쳐 블렌딩..
	//	-	텍스쳐 + 버텍스 컬러..
	D3DDevice->SetTexture(0, Texture);
	D3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	D3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	D3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	D3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_DISABLE);

	D3DDevice->SetStreamSource(0, VertexBuffer, 0, sizeof(CUSTOMVERTEX));
	D3DDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	D3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, NumVertex / 3);

}//	void CMAseObject::Render()
//------------------------------------------------------------------------------------------
//	텍스쳐 버퍼 세팅..
bool CMAseObject::SetTextureData(const wchar_t* filename)
{
	if (FAILED(D3DXCreateTextureFromFile(D3DDevice, filename, &Texture))) return false;
	return true;

}//	bool CMAseObject::SetTextureData(const wchar_t* filename)
//------------------------------------------------------------------------------------------
//	버텍스 버퍼, 인덱스 버퍼, uv 버퍼 세팅..
bool CMAseObject::SetVertexData(DWORD numVertexData, D3DXVECTOR3* vertexData, 
								DWORD numFaceData, CUSTOM_INDEX* faceData,
								DWORD numTVertexData, D3DXVECTOR3* tVertexData,
								DWORD numTFaceData, CUSTOM_INDEX* tFaceData)
{
	NumVertex = numFaceData * 3;

	if (FAILED(D3DDevice->CreateVertexBuffer(NumVertex * sizeof(CUSTOMVERTEX),
		0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &VertexBuffer, NULL))) return false;

	CUSTOMVERTEX* dstVertices;
	if (FAILED(VertexBuffer->Lock(0, NumVertex * sizeof(CUSTOMVERTEX), (void**)&dstVertices, 0))) return false;

	for (DWORD i = 0; i < numFaceData; ++i)
	{
		// postion
		dstVertices[i * 3].position.x = vertexData[faceData[i]._0].x;
		dstVertices[i * 3].position.y = vertexData[faceData[i]._0].y;
		dstVertices[i * 3].position.z = vertexData[faceData[i]._0].z;

		dstVertices[i * 3 + 1].position.x = vertexData[faceData[i]._1].x;
		dstVertices[i * 3 + 1].position.y = vertexData[faceData[i]._1].y;
		dstVertices[i * 3 + 1].position.z = vertexData[faceData[i]._1].z;

		dstVertices[i * 3 + 2].position.x = vertexData[faceData[i]._2].x;
		dstVertices[i * 3 + 2].position.y = vertexData[faceData[i]._2].y;
		dstVertices[i * 3 + 2].position.z = vertexData[faceData[i]._2].z;

		// color
		//*
		dstVertices[i * 3].color = 0xffffffff;
		dstVertices[i * 3 + 1].color = 0xffffffff;
		dstVertices[i * 3 + 2].color = 0xffffffff;
		//*/
		/*
		dstVertices[i * 3].color = 0xff00ff00;
		dstVertices[i * 3 + 1].color = 0xff00ff00;
		dstVertices[i * 3 + 2].color = 0xff00ff00;
		//*/

		// uv
		dstVertices[i * 3].tu = tVertexData[tFaceData[i]._0].x;
		dstVertices[i * 3].tv = tVertexData[tFaceData[i]._0].y;

		dstVertices[i * 3 + 1].tu = tVertexData[tFaceData[i]._1].x;
		dstVertices[i * 3 + 1].tv = tVertexData[tFaceData[i]._1].y;

		dstVertices[i * 3 + 2].tu = tVertexData[tFaceData[i]._2].x;
		dstVertices[i * 3 + 2].tv = tVertexData[tFaceData[i]._2].y;

	}//	for (DWORD i = 0; i < numFaceData; ++i)

	VertexBuffer->Unlock();

	return true;

}//	bool CMAseObject::SetVertexData(DWORD numVertexData, D3DXVECTOR3* vertexData, ...
//------------------------------------------------------------------------------------------
//	렌더링 데이터 세팅..
void CMAseObject::Serialize(CMArchive& ar)
{
	if (ar.IsLoading())
	{
		wstring textureName;
		ar >> textureName;
		SetTextureData(textureName.c_str());

		DWORD dwNumVertexData;
		ar >> dwNumVertexData;
		D3DXVECTOR3* pVertexData = new D3DXVECTOR3[dwNumVertexData];
		for (DWORD i = 0; i < dwNumVertexData; ++i)
			ar >> pVertexData[i];

		DWORD dwNumFaceData;
		ar >> dwNumFaceData;
		CUSTOM_INDEX* pFaceData = new CUSTOM_INDEX[dwNumFaceData];
		for (DWORD i = 0; i < dwNumFaceData; ++i)
			ar >> pFaceData[i];

		DWORD dwNumTVertexData;
		ar >> dwNumTVertexData;
		D3DXVECTOR3* pTVertexData = new D3DXVECTOR3[dwNumTVertexData];
		for (DWORD i = 0; i < dwNumTVertexData; ++i)
			ar >> pTVertexData[i];

		DWORD dwNumTFaceData;
		ar >> dwNumTFaceData;
		CUSTOM_INDEX* pTFaceData = new CUSTOM_INDEX[dwNumTFaceData];
		for (DWORD i = 0; i < dwNumTFaceData; ++i)
			ar >> pTFaceData[i];

		SetVertexData(dwNumVertexData, pVertexData, dwNumTFaceData, pFaceData, dwNumTVertexData, pTVertexData, dwNumTFaceData, pTFaceData);

	}//	if (ar.IsLoading())

}//	void CMAseObject::Serialize(CMArchive& ar)
//==========================================================================================//