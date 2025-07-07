//============================================================
/*	
*	Seq 5)	CMAseObject
*	[ 참고 : https://m.blog.naver.com/duaa83/60126169201 ]
*	
*	-	모델링 정보( 버텍스, 텍스처 등... )를 이용하여
*		렌더링할 실제 객체 생성..
*	-	Serialize를 이용해
		데이터 조합 및 메모리 생성..
*/
//============================================================
#pragma once

#include "MDefines.h"

class CMArchive;

class CMAseObject
{
public:
	CMAseObject();
	~CMAseObject();

	BOOL Init(LPDIRECT3DDEVICE9 d3DDevice);
	void Clear();
	void Update();
	void Render();
		
	void Serialize(CMArchive& ar);

private:
	LPDIRECT3DDEVICE9 D3DDevice;
	LPDIRECT3DVERTEXBUFFER9 VertexBuffer;
	LPDIRECT3DTEXTURE9 Texture;

	DWORD NumVertex;

	bool SetVertexData(DWORD numVertexData, D3DXVECTOR3* vertexData, DWORD numFaceData, CUSTOM_INDEX* faceData,
		DWORD numTVertexData, D3DXVECTOR3* tVertexData, DWORD numTFaceData, CUSTOM_INDEX* tFaceData);
	bool SetTextureData(const wchar_t* filename);

};