//======================================================================================
#include "StdAfx.h"
#include "MArchive.h"
#include "MFile.h"
//======================================================================================
CMArchive::CMArchive(CMFile* file) : File(file) { bIsLoading = File->IsLoading(); }
CMArchive::~CMArchive() { }
//--------------------------------------------------------------------------------------
CMArchive& CMArchive::operator<<(DWORD dw)
{
	if (File) *File << dw << TEXT("\t");
	return *this;
}
//--------------------------------------------------------------------------------------
CMArchive& CMArchive::operator<<(const D3DXVECTOR3& v3)
{
	if (File)
	{
		*File << v3.x << TEXT("\t");
		*File << v3.y << TEXT("\t");
		*File << v3.z << TEXT("\t");
	}

	return *this;
}
//--------------------------------------------------------------------------------------
CMArchive& CMArchive::operator<<(const CUSTOM_INDEX& ci)
{
	if (File)
	{
		*File << ci._0 << TEXT("\t");
		*File << ci._1 << TEXT("\t");
		*File << ci._2 << TEXT("\t");
	}

	return *this;
}
//--------------------------------------------------------------------------------------
CMArchive& CMArchive::operator<<(const wstring& str)
{
	if (File) *File << str << TEXT("\t");
	return *this;
}
//--------------------------------------------------------------------------------------
CMArchive& CMArchive::operator>>(DWORD& dw)
{
	if (File) *File >> dw;
	return *this;
}
//--------------------------------------------------------------------------------------
CMArchive& CMArchive::operator>>(D3DXVECTOR3& v3)
{
	if (File)
	{
		*File >> v3.x;
		*File >> v3.y;
		*File >> v3.z;
	}

	return *this;
}
//--------------------------------------------------------------------------------------
CMArchive& CMArchive::operator>>(CUSTOM_INDEX& ci)
{
	if (File)
	{
		*File >> ci._0;
		*File >> ci._1;
		*File >> ci._2;
	}

	return *this;
}
//--------------------------------------------------------------------------------------
CMArchive& CMArchive::operator>>(wstring& str)
{
	if (File) *File >> str;
	return *this;
}
//======================================================================================