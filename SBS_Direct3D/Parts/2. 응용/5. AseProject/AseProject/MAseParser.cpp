//=================================================================================================
#include "StdAfx.h"
#include "MAseParser.h"
#include "MAseLexer.h"
#include "MAseObject.h"
#include "MArchive.h"
//=================================================================================================
CMAseParser::CMAseParser(void)	:	AseLexer(nullptr), VertexData(nullptr), FaceData(nullptr),
									TVertexData(nullptr), TFaceData(nullptr) { Init(); }
CMAseParser::~CMAseParser(void) { Destroy(); }
//-------------------------------------------------------------------------------------------------
//	렉서 할당..
bool CMAseParser::Init()
{
	AseLexer = unique_ptr<CMAseLexer>(new CMAseLexer);

	if (AseLexer == nullptr) return false;
	return true;

}//	bool CMAseParser::Init()
//-------------------------------------------------------------------------------------------------
void CMAseParser::Destroy()
{
	if (VertexData) { delete[] VertexData; VertexData = nullptr; }
	if (FaceData)	{ delete[] FaceData; FaceData = nullptr; }
	if (TVertexData) { delete[] TVertexData; TVertexData = nullptr; }
	if (TFaceData) { delete[] TFaceData; TFaceData = nullptr; }

}//	void CMAseParser::Destroy()
//-------------------------------------------------------------------------------------------------
float CMAseParser::ParseFloat()
{
	float fNum;
	wstring strToken;

	if (AseLexer->GetToken(strToken)) fNum = (float)_wtof(strToken.c_str());

	return fNum;

}//	float CMAseParser::ParseFloat()
//-------------------------------------------------------------------------------------------------
DWORD CMAseParser::ParseDWORD()
{
	DWORD dwNum;
	wstring strToken;

	if (AseLexer->GetToken(strToken)) dwNum = wcstoul(strToken.c_str(), nullptr, 10);

	return dwNum;
}
//-------------------------------------------------------------------------------------------------
D3DXVECTOR3 CMAseParser::ParseVector3()
{
	D3DXVECTOR3 vecNum;
	wstring strToken;

	if (AseLexer->GetToken(strToken))
		vecNum.x = (float)_wtof(strToken.c_str());

	if (AseLexer->GetToken(strToken))
		vecNum.y = (float)_wtof(strToken.c_str());

	if (AseLexer->GetToken(strToken))
		vecNum.z = (float)_wtof(strToken.c_str());

	return vecNum;
}
//-------------------------------------------------------------------------------------------------
D3DXQUATERNION CMAseParser::ParseQuaternion()
{
	D3DXQUATERNION quatNum;
	wstring strToken;

	if (AseLexer->GetToken(strToken))
		quatNum.x = (float)_wtof(strToken.c_str());

	if (AseLexer->GetToken(strToken))
		quatNum.y = (float)_wtof(strToken.c_str());

	if (AseLexer->GetToken(strToken))
		quatNum.z = (float)_wtof(strToken.c_str());

	if (AseLexer->GetToken(strToken))
		quatNum.w = (float)_wtof(strToken.c_str());

	return quatNum;
}
//-------------------------------------------------------------------------------------------------
LONG CMAseParser::ParseLong()
{
	LONG lNum;
	wstring strToken;

	if (AseLexer->GetToken(strToken))
		lNum = wcstoul(strToken.c_str(), nullptr, 10);

	return lNum;
}
//-------------------------------------------------------------------------------------------------
WORD CMAseParser::ParseWORD()
{
	WORD nNum;
	wstring strToken;

	if (AseLexer->GetToken(strToken))
		nNum = (WORD)wcstoul(strToken.c_str(), nullptr, 10);

	return nNum;
}
//-------------------------------------------------------------------------------------------------
bool CMAseParser::LoadAseFile(const wchar_t* pszFilename)
{
	if (AseLexer->LoadAseFile(pszFilename) == false)
	{
		wchar_t buf[MAX_PATH] = { 0, };
		wsprintf(buf, TEXT("Ase file \"%s\" is bad"), pszFilename);

		MessageBox(nullptr, buf, nullptr, 0);
		return false;
	}

	//	렉서를 통해 토큰을 만든다.
	AseLexer->MakeToken();

	//	머터리얼 파싱..
	ParsingMaterialList();

	//	모델링 데이터 파싱..
	ParsingGeomObject();
	
	return true;
}
//-------------------------------------------------------------------------------------------------
//	머터리얼 파싱..
bool CMAseParser::ParsingMaterialList()
{
	wstring strToken;
	wstring strTextureFilename;
	DWORD dwMatrialCnt;

	if (AseLexer->FindToken(TEXT("*MATERIAL_LIST")))
	{
		if (AseLexer->FindToken(TEXT("*MATERIAL_COUNT")))
		{
			if (AseLexer->GetToken(strToken)) dwMatrialCnt = wcstoul(strToken.c_str(), nullptr, 10);
		}

		for (DWORD i = 0; i < dwMatrialCnt; ++i)
		{
			//	텍스처 이름 얻어오기..
			if (AseLexer->FindToken(TEXT("*MAP_DIFFUSE")))
			{
				if (AseLexer->FindToken(TEXT("*BITMAP")))
				{					
					AseLexer->GetToken(strTextureFilename);
					TextureFilename = strTextureFilename;
				}
			}

		}//	for (DWORD i = 0; i < dwMatrialCnt; ++i)

	}//	if (AseLexer->FindToken(TEXT("*MATERIAL_LIST")))

	return true;

}//	bool CMAseParser::ParsingMaterialList()
//-------------------------------------------------------------------------------------------------
//	모델링 데이터 파싱..
bool CMAseParser::ParsingGeomObject()
{
	wstring strToken;

	if (AseLexer->FindToken(TEXT("*GEOMOBJECT")))
	{
		if (AseLexer->FindToken(TEXT("*MESH")))
		{
			//	버텍스 데이터 할당..
			if (AseLexer->FindToken(TEXT("*MESH_NUMVERTEX")))
			{
				NumVertexData = ParseDWORD();
				VertexData = new D3DXVECTOR3[NumVertexData];
				ZeroMemory(VertexData, sizeof(D3DXVECTOR3) * NumVertexData);

			}//	if (AseLexer->FindToken(TEXT("*MESH_NUMVERTEX")))

			//	인덱스 데이터 할당..
			if (AseLexer->FindToken(TEXT("*MESH_NUMFACES")))
			{
				NumFaceData = ParseDWORD();
				FaceData = new CUSTOM_INDEX[NumFaceData];
				ZeroMemory(VertexData, sizeof(D3DXVECTOR3) * NumVertexData);
			}

			//	버텍스 데이터 세팅..
			if (AseLexer->FindToken(TEXT("*MESH_VERTEX_LIST")))
			{
				for (DWORD i = 0; i < NumVertexData; ++i)
				{
					if (AseLexer->FindToken(_T("*MESH_VERTEX")))
					{
						DWORD dwVertexIndex = ParseDWORD();
						// 3ds Max의 좌표계를 DX의 좌표계로 변경하기 위해 y값과 z값을 바꿔줍니다.
						VertexData[dwVertexIndex].x = ParseFloat();
						VertexData[dwVertexIndex].z = ParseFloat();
						VertexData[dwVertexIndex].y = ParseFloat();
					}
				}

			}//	if (AseLexer->FindToken(TEXT("*MESH_VERTEX_LIST")))

			//	인덱스 데이터 세팅..
			if (AseLexer->FindToken(TEXT("*MESH_FACE_LIST")))
			{
				for (DWORD i = 0; i < NumFaceData; ++i)
				{
					if (AseLexer->FindToken(TEXT("*MESH_FACE")))
					{
						//	순서를 나타내는 값이기는 하지만 사용하지 않음..
						AseLexer->GetToken(strToken);

						//	3ds Max의 좌표계를 DX의 좌표계로 변경하기 위해 y값과 z값을 바꿈..
						AseLexer->GetToken(strToken);
						FaceData[i]._0 = ParseDWORD();

						AseLexer->GetToken(strToken);
						FaceData[i]._2 = ParseDWORD();

						AseLexer->GetToken(strToken);
						FaceData[i]._1 = ParseDWORD();
					}
				}

			}//	if (AseLexer->FindToken(TEXT("*MESH_FACE_LIST")))

			//	uv 데이터 할당 및 세팅..
			if (AseLexer->FindToken(TEXT("*MESH_NUMTVERTEX")))
			{
				NumTVertexData = ParseDWORD();

				TVertexData = new D3DXVECTOR3[NumTVertexData];
				ZeroMemory(TVertexData, sizeof(D3DXVECTOR3) * NumTVertexData);

				if (AseLexer->FindToken(TEXT("*MESH_TVERTLIST")))
				{
					for (DWORD i = 0; i < NumTVertexData; ++i)
					{
						if (AseLexer->FindToken(TEXT("*MESH_TVERT")))
						{
							//	3ds Max에서는 원점이 좌하단이므로
							//	좌상단이 원점인 dx에서 쓰려면
							//	v좌표를 1.0f-v로 보정..
							DWORD dwIndex = ParseDWORD();
							TVertexData[dwIndex].x = ParseFloat();
							TVertexData[dwIndex].y = ParseFloat();
							TVertexData[dwIndex].y = 1.0f - TVertexData[dwIndex].y;
						}
					}
				}

			}//	if (AseLexer->FindToken(TEXT("*MESH_NUMTVERTEX")))

			//	uv 인덱스 데이터 할당 및 세팅..
			if (AseLexer->FindToken(TEXT("*MESH_NUMTVFACES")))
			{
				NumTFaceData = ParseDWORD();
				TFaceData = new CUSTOM_INDEX[NumTFaceData];

				if (AseLexer->FindToken(TEXT("*MESH_TFACELIST")))
				{
					for (DWORD i = 0; i < NumTFaceData; ++i)
					{
						if (AseLexer->FindToken(TEXT("*MESH_TFACE")))
						{
							DWORD dwIndex = ParseDWORD();

							//	3ds Max의 좌표계를
							//  DX의 좌표계로 변경하기 위해
							//	y값과 z값을 바꿈..
							TFaceData[dwIndex]._0 = ParseDWORD();
							TFaceData[dwIndex]._2 = ParseDWORD();
							TFaceData[dwIndex]._1 = ParseDWORD();
						}
					}
				}

			}//	if (AseLexer->FindToken(TEXT("*MESH_NUMTVFACES")))

		}//	if (AseLexer->FindToken(TEXT("*MESH")))

	}//	if (AseLexer->FindToken(TEXT("*GEOMOBJECT")))

	return true;

}//	bool CMAseParser::ParsingGeomObject()
//-------------------------------------------------------------------------------------------------
//	파싱한 데이터 저장..
void CMAseParser::Serialize(CMArchive& ar)
{
	if (ar.IsStroing())
	{
		ar << TextureFilename;

		ar << NumVertexData;
		for (DWORD i = 0; i < NumVertexData; ++i) ar << VertexData[i];

		ar << NumFaceData;
		for (DWORD i = 0; i < NumFaceData; ++i) ar << FaceData[i];

		ar << NumTVertexData;
		for (DWORD i = 0; i < NumTVertexData; ++i) ar << TVertexData[i];

		ar << NumTFaceData;
		for (DWORD i = 0; i < NumTFaceData; ++i) ar << TFaceData[i];

	}//	if (ar.IsStroing())

}//	void CMAseParser::Serialize(CMArchive& ar)
//=================================================================================================//