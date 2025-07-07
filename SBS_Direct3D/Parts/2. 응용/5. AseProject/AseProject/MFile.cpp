//========================================================================
#include "StdAfx.h"
#include "MFile.h"
#include "MAseObject.h"
//========================================================================
CMFile::~CMFile() { Close(); }
//------------------------------------------------------------------------
//	파일 액세스..
bool CMFile::Open(const wchar_t* fileName, unsigned int Mode)
{
	//	읽기 모드로 액세스 ( 접근 )하는지 체크..
	bIsLoading = false;
	if (Mode & eMode::READ) bIsLoading = true;

	//	읽기 모드 수행..
	if (IsLoading())
	{
		IFileStream = unique_ptr<wifstream>(new wifstream());

		if (IFileStream)
		{
			IFileStream->open(fileName, Mode);		
			if (IFileStream->good() == false) return false;
		}

	}//	if (IsLoading())
	else
	//	출력 모드 수행..
	{
		OFileStream = unique_ptr<wofstream>(new wofstream());

		if (OFileStream)
		{
			OFileStream->open(fileName, Mode);
			if (OFileStream->good() == false) return false;
		}

	}//	~if (IsLoading())

	return true;

}//	bool CMFile::Open(const wchar_t* fileName, unsigned int Mode)
//------------------------------------------------------------------------
void CMFile::Close()
{
	if (IsLoading()) { if (IFileStream) IFileStream->close(); }
	else { if (OFileStream) OFileStream->close(); }

}//	void CMFile::Close()
//------------------------------------------------------------------------
CMFile& CMFile::operator>>(float& f)
{
	if (IFileStream) *IFileStream >> f;
	return *this;
}
//------------------------------------------------------------------------
CMFile& CMFile::operator>>(DWORD& dw)
{
	if (IFileStream) *IFileStream >> dw;
	return *this;
}
//------------------------------------------------------------------------
CMFile& CMFile::operator>>(D3DXVECTOR3& v3)
{
	if (IFileStream)
	{
		*IFileStream >> v3.x;
		*IFileStream >> v3.y;
		*IFileStream >> v3.z;
	}

	return *this;
}
//------------------------------------------------------------------------
CMFile& CMFile::operator>>(CUSTOM_INDEX& ci)
{
	if (IFileStream)
	{
		*IFileStream >> ci._0;
		*IFileStream >> ci._1;
		*IFileStream >> ci._2;
	}

	return *this;
}
//------------------------------------------------------------------------
CMFile& CMFile::operator>>(wstring& str)
{
	if (IFileStream) *IFileStream >> str;
	return *this;
}
//------------------------------------------------------------------------
CMFile& CMFile::operator<<(float f)
{
	if (OFileStream) *OFileStream << f << TEXT("\t");
	return *this;
}
//------------------------------------------------------------------------
CMFile& CMFile::operator<<(DWORD dw)
{
	if (OFileStream) *OFileStream << dw << TEXT("\t");
	return *this;
}
//------------------------------------------------------------------------
CMFile& CMFile::operator<<(const D3DXVECTOR3& v3)
{
	if (OFileStream)
	{
		*OFileStream << v3.x << TEXT("\t");
		*OFileStream << v3.y << TEXT("\t");
		*OFileStream << v3.z << TEXT("\t");
	}

	return *this;
}
//------------------------------------------------------------------------
CMFile& CMFile::operator<<(const CUSTOM_INDEX& ci)
{
	if (OFileStream)
	{
		*OFileStream << ci._0 << TEXT("\t");
		*OFileStream << ci._1 << TEXT("\t");
		*OFileStream << ci._2 << TEXT("\t");
	}

	return *this;
}
//------------------------------------------------------------------------
CMFile& CMFile::operator<<(const wstring& str)
{
	if (OFileStream) *OFileStream << str << TEXT("\t");
	return *this;
}
//========================================================================//