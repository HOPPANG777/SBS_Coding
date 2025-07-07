//======================================================================================
/*
*	Seq 2)	CMArchive
*	
*		-	CMFile에 있는 스트림 데이터를
			입출력하기 편하도록
*			연산자 오버로딩 활용..
*/
//======================================================================================
#pragma once
#include "MDefines.h"
class CMFile;
//======================================================================================
class CMArchive
{
public:
	enum eMode
	{
		STORE = 0,
		LOAD = 1,
	};

	CMArchive(CMFile* file);

	~CMArchive();

public:
	inline bool IsLoading() const { return bIsLoading; }
	inline bool IsStroing() const { return !bIsLoading; }


	//	연산자 오버로딩을 활용한 파일 출력 스트림 관리..
	//	-	내부에서 File의 << 를 호출..
	CMArchive& operator<<(DWORD dw);
	CMArchive& operator<<(const D3DXVECTOR3& v3);
	CMArchive& operator<<(const CUSTOM_INDEX& ci);
	CMArchive& operator<<(const wstring& str);

	//	연산자 오버로딩을 활용한 파일 입력 스트림 관리..
	//	-	내부에서 File의 >> 를 호출..
	CMArchive& operator>>(DWORD& dw);
	CMArchive& operator>>(D3DXVECTOR3& v3);
	CMArchive& operator>>(CUSTOM_INDEX& ci);
	CMArchive& operator>>(wstring& str);

private:
	CMFile* File;
	bool bIsLoading;
};
//======================================================================================