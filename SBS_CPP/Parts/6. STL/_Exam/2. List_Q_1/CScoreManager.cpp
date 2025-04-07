//=====================================================
#include "CScoreManager.h"
#include<algorithm>
using namespace std;
//=====================================================
CScoreManager::~CScoreManager()	{ DeleteAllData(); }
//-------------------------------
//	추가..
void CScoreManager::AddData(CStudent* pPerson)	{ _list.push_back(pPerson); }
//-------------------------------
//	편집..
bool CScoreManager::EditData(char* pszName, int subjIdx, int score)
{
	ITER_CPERSON iterBegin = _list.begin();
	ITER_CPERSON iterEnd = _list.end();
	ITER_CPERSON iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CStudent* pTmp = (*iterCur);
		if ( strcmp( pTmp->GetName(), pszName ) == 0 ) 
			return pTmp->SetScore(subjIdx, score);
	}

	return false;

}//	bool CScoreManager::EditData(char* pszName, int subjIdx, int score)
//-------------------------------
//	삭제..
bool CScoreManager::DeleteData(char* pszName)
{
	ITER_CPERSON iterBegin = _list.begin();
	ITER_CPERSON iterEnd = _list.end();
	ITER_CPERSON iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CStudent* pTmp = (*iterCur);
		if (strcmp(pTmp->GetName(), pszName) == 0)
		{
			delete pTmp;
			pTmp = NULL;
			_list.erase(iterCur);

			return true;

		}//	if (strcmp(pTmp->GetName(), pszName) == 0)

	}//	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	
	return false;

}//	void CScoreManager::DeleteData(char* pszName)
//-------------------------------
//	전체 삭제..
bool CScoreManager::DeleteAllData()
{
	if (_list.size() == 0) return false;

	ITER_CPERSON iterBegin = _list.begin();
	ITER_CPERSON iterEnd = _list.end();
	ITER_CPERSON iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CStudent *pTmp = (*iterCur);
		delete pTmp;
		pTmp = NULL;
	}
	_list.clear();

	return true;

}//	void CScoreManager::DeleteAllData()
//-------------------------------
//	출력..
bool CScoreManager::ShowData(char* pszName)
{
	ITER_CPERSON iterBegin = _list.begin();
	ITER_CPERSON iterEnd = _list.end();
	ITER_CPERSON iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CStudent*pTmp = (*iterCur);
		if (strcmp(pTmp->GetName(), pszName) == 0) {
			pTmp->ShowInfo(); return true; }
	}
	
	return false;

}//	void CScoreManager::ShowData(char* pszName)
//-------------------------------
//	전체 출력..
bool CScoreManager::ShowAllData()
{
	if( _list.size() == 0) return false;

	ITER_CPERSON iterBegin = _list.begin();
	ITER_CPERSON iterEnd = _list.end();
	ITER_CPERSON iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CStudent*pTmp = (*iterCur);
		pTmp->ShowInfo();
		cout << endl;
	}

	return true;

}//	void CScoreManager::ShowAllData()
//-------------------------------
//	전체 시퀀스 처리..
void CScoreManager::Process()
{
	while (1)
	{
		ShowMenu();

		switch (_select)
		{
			case ADD: Add(); break;

			case DELETE: Delete(); break;

			case DELETEALL: DeleteAll(); break;

			case SHOW: Show(); break;

			case SHOWALL: ShowAll(); break;

			case EDIT: Edit(); break;

			case SORT_DESC: ShowAll_Desc(); break;

			case SORT_ASC: ShowAll_Asc(); break;

			case FINISH: Finish(); break;

			default: DoError(); break;
		
		}//	switch (_select)

	}//	while (1)

}//	void CScoreManager::Process()
//-------------------------------
//	메뉴 출력..
void CScoreManager::ShowMenu()
{
	system("cls");
	cout << "성적 관리 프로그램입니다.\n" << "번호를 입력하세요~" << endl;
	cout << "1. 추가" << endl;
	cout << "2. 삭제" << endl;
	cout << "3. 전체 삭제" << endl;
	cout << "4. 조회" << endl;
	cout << "5. 전체 조회" << endl;
	cout << "6. 편집" << endl;
	cout << "7. 1등부터 조회..( 내림차순 )" << endl;
	cout << "8. 꼴등부터 조회..( 오름차순 )" << endl;
	cout << "9. 종료" << endl;

	cin >> _select;

	getchar();


}//	void CScoreManager::ShowMenu()
//-------------------------------
void CScoreManager::Add()
{
	system("cls");

	cout << "이름 : ";	
    char szName[50] = "";
	cin >> szName;

	cout << "국어 : ";
	int kor;
	cin >> kor;

    cout << "영어 : ";
	int eng;
	cin >> eng;

	int math;
	cout << "수학 : ";
	cin >> math;

	CStudent* pPerson = new CStudent(szName, kor, eng, math);
	AddData(pPerson);
	cout << szName << "님이 추가되었습니다" << endl;

	getchar();
	getchar();

}//	void CScoreManager::Add()
//-------------------------------
void CScoreManager::Delete()
{
	system("cls");
	if (_list.size() == 0) cout << "삭제할 데이터가 없네요 ㅠㅠ" << endl;
	else
	{
		char szName[50] = "";
		cout << "삭제 하고자하는 분의 이름을 입력하세요 : ";
		cin >> szName;
		getchar();

		bool bResult = DeleteData(szName);

		if (bResult)
			cout << "삭제되었습니다." << endl;
		else
			cout << "삭제하려는 데이터가 없습니다 ㅠ.ㅠ" << endl;
	
	}//	~if (_list.size() == 0)
	
	system("pause");

}//	void CScoreManager::Delete()
//-------------------------------
void CScoreManager::DeleteAll()
{
	system("cls");
	bool bResult = DeleteAllData();

	if (bResult) cout << "모든 데이터가 삭제되었습니다." << endl;
	else cout << "삭제할 데이터가 없네요 ㅠㅠ" << endl;

	system("pause");

}//	void CScoreManager::DeleteAll()
//-------------------------------
//	출력..
void CScoreManager::Show()
{
	system("cls");
	if (_list.size() == 0) cout << "조회할 데이터가 없네요 ㅠㅠ" << endl;
	else
	{
		char szName[50] = "";
		cout << "조회 하고자하는 분의 이름을 입력하세요 : ";
		cin >> szName;

		bool bResult = ShowData(szName);

		if (bResult == false) cout << "검색결과가 없습니다 ㅠ.ㅠ" << endl;

	}//	~if (_list.size() == 0)

	system("pause");

}//	void CScoreManager::Show()
//-------------------------------
//	전체 출력..
void CScoreManager::ShowAll()
{
	system("cls");
	bool bResult = ShowAllData();

	if( bResult == false ) cout << "조회할 데이터가 없네요 ㅠㅠ" << endl;

	system("pause");

}//	void CScoreManager::ShowAll()
//-------------------------------
/*
	함수 객체..

	-	클래스의 객체를 마치 함수처럼 사용하는 방식..

*/
class CompareDesc {
public:
	bool operator()(CStudent* lhs, CStudent* rhs) { return lhs->Get_Avg() > rhs->Get_Avg(); }
};

class CompareAsc{
public:
	bool operator()(CStudent* lhs, CStudent* rhs) { return lhs->Get_Avg() < rhs->Get_Avg(); }
};
//-------------------------------
void CScoreManager::ShowAll_Desc()
{
	_list.sort(CompareDesc());

	ShowAll();
}
void CScoreManager::ShowAll_Asc()
{
	_list.sort(CompareAsc());

	ShowAll();
}
//-------------------------------
//	편집..
void CScoreManager::Edit()
{
	system("cls");
	if (_list.size() == 0) cout << "편집할 데이터가 없네요 ㅠㅠ" << endl;
	else
	{
		char szName[50] = "";
		cout << "편집 하고자하는 분의 이름을 입력하세요 : ";
		cin >> szName;
		
		bool bResult = ShowData(szName);
		if (bResult == false)
		{
			cout << "검색결과가 없습니다 ㅠ.ㅠ" << endl;
			return;
		}

		getchar();

		cout << "편집할 과목을 선택하세요 " << endl;
		cout << "1. 국어\t2. 영어\t3. 수학" << endl;
		int subIdx;
		cin >> subIdx;
		cout << "점수를 입력하세요 " << endl;
		int score;
		cin >> score;

		EditData(szName, subIdx - 1, score);
	
	}//	~if (_list.size() == 0)

}//	void CScoreManager::Edit()
//-------------------------------
void CScoreManager::DoError()
{
	system("cls");
	cout << "잘못 눌렀네요~ㅜ.ㅜ" << endl;

	system("pause");

}//	void CScoreManager::DoError()
//-------------------------------
void CScoreManager::Finish()
{
	system("cls");
	cout << "프로그램을 종료합니다." << endl;
	exit(1);	

}//	void CScoreManager::Finish()
//=====================================================
/*
	[ 참고 ]

		C++ Sorting Custom Objects in a list
		https://stackoverflow.com/questions/16507519/c-sorting-custom-objects-in-a-list

		C++ Function Object (함수 객체)를 알아보자
		https://mutpp.tistory.com/entry/C-Function-Object-%ED%95%A8%EC%88%98-%EA%B0%9D%EC%B2%B4%EB%A5%BC-%EC%95%8C%EC%95%84%EB%B3%B4%EC%9E%90
*/
//=====================================================