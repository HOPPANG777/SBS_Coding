//============================================================
/*	
*	Seq 3)	CMAseLexer
*	[ 참고 : https://m.blog.naver.com/duaa83/60125306227 ]
*	-	ASE 파일 로딩..
*	-	문장을 토큰단위로 구분..
*		-	토큰
*			-	문장을 구성하는 단어들을
				데이터로 표현..
*			-	예)
*					A = B + 1
*					->	"A", "=", "B", "+", "1"의 각 데이터 표현.
* 
*	-	ASE 파일은
		만들어진 모델링 데이터의
		형태에 따라
		다양한 형식으로 저장됨..
*	-	ASE 파일에 들어있는
		데이터 모두를
		해석할 필요는 없음..
*		-	필요한 데이터를
			가공해서 사용해야 함..
*/
//============================================================
#pragma once

class CMAseLexer
{
public:
	CMAseLexer();
	~CMAseLexer();

public:
	bool LoadAseFile(const wchar_t* pFilename);
	void MakeToken();
	bool GetToken(wstring& strTokenOut);
	bool GetTokenForDebug(wstring& strTokenOut);
	bool FindToken(const wstring& strToken);
	bool FindTokenInThisBlock(const wstring& strToken);
	

private:
	vector<wstring> Tokens;
	wstring FileRawData;
	//	입력 전용 파일 스트림..
	unique_ptr<ifstream> FileStream;
	DWORD CurTokenNum;
};
