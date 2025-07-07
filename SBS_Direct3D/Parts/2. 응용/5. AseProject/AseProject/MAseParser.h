//============================================================
/*
*	Seq 4)	CMAseParser
*	[ 참고 : https://m.blog.naver.com/duaa83/60125369154 ]
*	
*	-	CMAseLexer에서 구분한
		토큰들의 의미를 분석( Parse )..
*	-	모델링 데이터에
		적용하려는 기능만
		추출해서 관리..
*/ 
//============================================================
#pragma once

class CMAseLexer;
class CMAseObject;
class CMArchive;
struct CUSTOM_INDEX;

class CMAseParser
{
public:
	CMAseParser();
	~CMAseParser();

	bool Init();
	void Destroy();

	bool LoadAseFile(const wchar_t* pszFilename);
	bool ParsingMaterialList();
	bool ParsingGeomObject();

	void Serialize(CMArchive& ar);

public:
	D3DXQUATERNION	ParseQuaternion();
	D3DXVECTOR3		ParseVector3();
	LONG			ParseLong();
	DWORD			ParseDWORD();
	WORD			ParseWORD();
	float			ParseFloat();

protected:
	//	unique_ptr..
	//	[ 참고 : https://bunhere.tistory.com/407 ]
	//	-	C++에서 제공하는 스마트 포인터..
	//	-	동적으로 힙 영역에 할당된 인스턴스에 대한 소유권을 얻음.
	//	-	unique_ptr 객체가 사라지면 해당 인스턴스를 해제.
	//		-	개발자가 delete를 해줄 필요가 없음.
	//		-	객체가 스스로 자신의 소멸 시점에 할당된 메모리를 제거.
	unique_ptr<CMAseLexer> AseLexer;

	//	이미지 파일 이름..
	wstring TextureFilename;

	//	버텍스 갯수..
	DWORD NumVertexData;
	//	인덱스 갯수..
	DWORD NumFaceData;
	//	uv좌표 갯수..
	DWORD NumTVertexData;
	//	uv 좌표의 인덱스 갯수..
	DWORD NumTFaceData;
	//	버텍스 좌표 정보..
	D3DXVECTOR3* VertexData;
	//	인덱스 버퍼 정보..
	CUSTOM_INDEX* FaceData;
	//	uv좌표 정보..
	D3DXVECTOR3* TVertexData;
	//	uv 좌표의 인덱스..
	CUSTOM_INDEX* TFaceData;
};
//============================================================//