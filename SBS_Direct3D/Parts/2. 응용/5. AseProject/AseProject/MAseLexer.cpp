//=========================================================================
#include "StdAfx.h"
#include "MAseLexer.h"
//=========================================================================
CMAseLexer::CMAseLexer() : CurTokenNum(0) { FileStream = unique_ptr<ifstream>(new ifstream); }
CMAseLexer::~CMAseLexer() { FileRawData.clear(); Tokens.clear(); }
//-------------------------------------------------------------------------
//	ASE 로딩..
//	-	실제로 ASE 파일을 로딩하는 부분..
bool CMAseLexer::LoadAseFile(const wchar_t* pszFilename)
{
	//	파일 접근..
	FileStream->open(pszFilename);

	if (FileStream->good())
	{
		//	파일에 있는 문자열 데이터 할당..
		FileRawData.assign(istreambuf_iterator<char>(*FileStream.get()), istreambuf_iterator<char>());
		FileStream->close();
		return true;
	}
	else 
	{ FileStream->close(); return false; }

}//	bool CMAseLexer::LoadAseFile(const wchar_t* pszFilename)
//-------------------------------------------------------------------------
//	토큰 가져오기..
//	-	함수를 호출한 순서대로 토큰 가져옴..
bool CMAseLexer::GetToken(wstring& strTokenOut)
{
	if (CurTokenNum < Tokens.size())
	{
		strTokenOut = Tokens.at(CurTokenNum);
		++CurTokenNum;

		return true;
	}
	else
		return false;

}//	bool CMAseLexer::GetToken(wstring& strTokenOut)
//-------------------------------------------------------------------------
//	strToken 토큰 찾기..
bool CMAseLexer::FindToken(const wstring& strToken)
{
	while (CurTokenNum < Tokens.size())
	{
		++CurTokenNum;

		wstring strTemp = Tokens.at(CurTokenNum - 1);

		if (strToken == strTemp) return true;

	}//	while (CurTokenNum < Tokens.size())

	return false;

}//	bool CMAseLexer::FindToken(const wstring& strToken)
//-------------------------------------------------------------------------
//	현재 블록에서 토큰 찾기..
bool CMAseLexer::FindTokenInThisBlock(const wstring& strToken)
{
	while (CurTokenNum < Tokens.size())
	{
		++CurTokenNum;
		
		wstring strTemp = Tokens.at(CurTokenNum - 1);
		
		if (strToken == strTemp) return true;

		else if (TEXT("}") == strTemp) return false;

	}//	while (CurTokenNum < Tokens.size())

	return false;

}//	bool CMAseLexer::FindTokenInThisBlock(const wstring& strToken)
//-------------------------------------------------------------------------
//	현재 검색 인덱스의 토큰 가져오기..
//	-	디버깅 용..
bool CMAseLexer::GetTokenForDebug(wstring& strTokenOut)
{
	if (CurTokenNum < Tokens.size())
	{
		strTokenOut = Tokens.at(CurTokenNum);
		return true;
	}
	else
		return false;

}//	bool CMAseLexer::GetTokenForDebug(wstring& strTokenOut)
//-------------------------------------------------------------------------
//	토큰 단위로 데이터 빌드..
void CMAseLexer::MakeToken()
{
	wstring strSeparators(TEXT(" \t\r\n"));
	size_t nFileStrLen = FileRawData.length();
	size_t nStart, nStop;

	//	find_first_not_of
	//	[ 참고 : https://forhjy.medium.com/c-std-string-%EB%AC%B8%EC%9E%90%EC%97%B4-%EC%A1%B0%EC%9E%91-%ED%95%A8%EC%88%98-72a7d7dc5be7 ]
	//	-	처음으로 strSeparators에 해당되지 않는 문자열의 인덱스 반환..
	// 
	//		예)		string str = "bbbbbbbabbbbbbabbbbbb";
	//				cout << str.find_first_not_of("b") << endl;
	//				->	7
	nStart = FileRawData.find_first_not_of(strSeparators);

	//	전체 파일길이의 30%만큼 공간 예약 할당..
	Tokens.reserve(static_cast<size_t>(nFileStrLen * 0.3f));

	while ((nStart >= 0) && (nStart < nFileStrLen))
	{
		// 따옴표가 발견되면 따옴표 끝까지 하나의 토큰이 된다.
		if (FileRawData[nStart] == '\"')
		{
			//	따옴표 다음 글자부터 다음 따옴표가 나오는 부분까지 세팅..
			nStart += 1;
			nStop = FileRawData.find_first_of('\"', nStart);
		}
		else			
			nStop = FileRawData.find_first_of(strSeparators, nStart);	//	nStart 부터 strSeparators에 의해 필터링되는 부분까지 세팅.

		//	nStop 필터링..
		//	-	예상치 못한 값이나 파일길이를 넘어가는 경우
		//		파일 길이로 강제 세팅..
		if ((nStop < 0) || (nStop > nFileStrLen))
			nStop = nFileStrLen;

		//	substr
		//	[ 참고 : https://modoocode.com/235 ]
		//	-	FileRawData에 있는 문자열 중 nStart 인덱스 부터 nStop - nStart 길이 만큼 토큰으로 설정..		
		Tokens.push_back(FileRawData.substr(nStart, nStop - nStart));

		//	다음 읽어올 위치 세팅..
		nStart = FileRawData.find_first_not_of(strSeparators, nStop + 1);

	}//	while ((nStart >= 0) && (nStart < nFileStrLen))

}//	void CMAseLexer::MakeToken()
//=========================================================================//