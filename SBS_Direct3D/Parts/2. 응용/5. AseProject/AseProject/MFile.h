//==================================================================
//	Seq 1)	파일 입출력 기능 관리 클래스..
//==================================================================
#pragma once
#include "MDefines.h"
//==================================================================
class CMFile
{
public:
	//	파일 엑세스 모드..
	enum eMode
	{
		READ = ios_base::in,
		WRITE = ios_base::out,
		CREATE = ios_base::trunc,
		NOCREATE = ios_base::_Nocreate
	};

public:
	~CMFile();

	inline bool IsLoading() const { return bIsLoading; }

	bool Open(const wchar_t* fileName, unsigned int Mode = eMode::READ);
	void Close();

	
	//	연산자 오버로딩을 활용한 파일 출력 스트림 관리..
	CMFile& operator<<(float f);
	CMFile& operator<<(DWORD dw);
	CMFile& operator<<(const D3DXVECTOR3& v3);
	CMFile& operator<<(const CUSTOM_INDEX& ci);
	CMFile& operator<<(const wstring& str);

	//	연산자 오버로딩을 활용한 파일 입력 스트림 관리..
	CMFile& operator>>(float& f);
	CMFile& operator>>(DWORD& dw);
	CMFile& operator>>(D3DXVECTOR3& v3);
	CMFile& operator>>(CUSTOM_INDEX& ci);
	CMFile& operator>>(wstring& str);

private:
	
	//	unique_ptr
	//	[ 참고 : https://jungwoong.tistory.com/48
	//			 https://www.boost.org/ ]
	//	-	c++ 11부터 boost에서 제공되던 스마트 포인터가 stl에 추가..
	//	-	스마트 포인터 중 하나로써
	//		포인터를 고유하게 관리하도록 하여
	//		해당 포인터를 소유한 오브젝트가 소멸되면
	//		자동적으로 메모리를 해제..
	
	//	입력 전용 스트림..
	unique_ptr<wifstream> IFileStream;
	//	출력 전용 스트림..
	unique_ptr<wofstream> OFileStream;

	bool bIsLoading;
};
//==================================================================//