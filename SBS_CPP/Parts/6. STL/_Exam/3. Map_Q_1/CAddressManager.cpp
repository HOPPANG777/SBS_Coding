//=====================================================
/*
	[ 참고 : https://leeusin.tistory.com/418
			 https://giantpark197cm.tistory.com/142 ]
*/
//=====================================================
#include "CAddressManager.h"
#include <string>
using namespace std;
//=====================================================
CAddressManager::~CAddressManager()	{ DeleteAllData(); }
//-------------------------------
void CAddressManager::AddData(CPerson* pPerson)	{	
	_list.insert(pair<string, CPerson*>(pPerson->GetName(), pPerson));
}
//-------------------------------
bool CAddressManager::DeleteData(char* pszName)
{
	ITER_CPERSON iterBegin = _list.begin();
	ITER_CPERSON iterEnd = _list.end();
	ITER_CPERSON iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CPerson *pTmp = (*iterCur).second;
		if (strcmp(pTmp->GetName().c_str(), pszName) == 0)
		{
			CPerson *pTmp = (*iterCur).second;
			delete pTmp;
			pTmp = NULL;

			_list.erase(iterCur);

			return true;
		}
	}
	
	return false;

}//	void CAddressManager::DeleteData(char* pszName)
//-------------------------------
bool CAddressManager::DeleteAllData()
{
	if (_list.size() == 0)
		return false;

	ITER_CPERSON iterBegin = _list.begin();
	ITER_CPERSON iterEnd = _list.end();
	ITER_CPERSON iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CPerson *pTmp = (*iterCur).second;
		delete pTmp;
		pTmp = NULL;

		//_list.erase(iterCur);
	}
	_list.clear();

	return true;

}//	void CAddressManager::DeleteAllData()
//-------------------------------
bool CAddressManager::ShowData(char* pszName)
{
	ITER_CPERSON iterBegin = _list.begin();
	ITER_CPERSON iterEnd = _list.end();
	ITER_CPERSON iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CPerson *pTmp = (*iterCur).second;
		if (strcmp(pTmp->GetName().c_str(), pszName) == 0)
		{
			pTmp->ShowInfo();
			return true;
		}
	}
	
	return false;

}//	void CAddressManager::ShowData(char* pszName)
//-------------------------------
bool CAddressManager::ShowAllData()
{
	if( _list.size() == 0)
		return false;

	ITER_CPERSON iterBegin = _list.begin();
	ITER_CPERSON iterEnd = _list.end();
	ITER_CPERSON iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CPerson *pTmp = (*iterCur).second;
		pTmp->ShowInfo();
		cout << endl;
	}

	return true;

}//	void CAddressManager::ShowAllData()
//-------------------------------
void CAddressManager::Process()
{
	while (1)
	{
		ShowMenu();

		switch (_select)
		{
		case ADD:
			Add();
			break;

		case DELETE:
			Delete();
			break;

		case DELETEALL:
			DeleteAll();
			break;

		case SHOW:
			Show();
			break;

		case SHOWALL:
			ShowAll();
			break;

		case FINISH:
			Finish();
			break;

		default:
			DoError();
			break;
		
		}//	switch (_select)

	}//	while (1)

}//	void CAddressManager::Process()
//-------------------------------
void CAddressManager::ShowMenu()
{
	system("cls");
	cout << "주소록 관리 프로그램입니다.\n" << "번호를 입력하세요~" << endl;
	cout << "1. 추가" << endl;
	cout << "2. 삭제" << endl;
	cout << "3. 전체 삭제" << endl;
	cout << "4. 조회" << endl;
	cout << "5. 전체 조회" << endl;
	cout << "6. 종료" << endl;

	cin >> _select;

	getchar();


}//	void CAddressManager::ShowMenu()
//-------------------------------
void CAddressManager::Add()
{
	system("cls");

	cout << "이름 : ";		
	string tmpName;
	getline(cin, tmpName);
	
	if( _list.find(tmpName) != _list.end())
	{	
		cout<<"동일한 이름이 존재합니다."<<endl;
		getchar();
		return;
	}
		

	cout << "전화 번호 : ";
	char szPhone[50] = "";
	cin >> szPhone;

    cout << "주소 : ";
    char szAddress[50] = "";
    cin >> szAddress;

	int age = 0;
	cout << "나이 : ";
	cin >> age;

	CPerson *pPerson = new CPerson(tmpName, age, szAddress, szPhone);
	AddData(pPerson);
	cout << tmpName << "님이 추가되었습니다" << endl;

	getchar();
	getchar();

}//	void CAddressManager::Add()
//-------------------------------
void CAddressManager::Delete()
{
	system("cls");
	if (_list.size() == 0)
		cout << "삭제할 데이터가 없네요 ㅠㅠ" << endl;
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
	}
	
	system("pause");
}
//-------------------------------
void CAddressManager::DeleteAll()
{
	system("cls");
	bool bResult = DeleteAllData();

	if (bResult)
		cout << "모든 데이터가 삭제되었습니다." << endl;
	else
		cout << "삭제할 데이터가 없네요 ㅠㅠ" << endl;

	system("pause");

}//	void CAddressManager::DeleteAll()
//-------------------------------
void CAddressManager::Show()
{
	system("cls");
	if (_list.size() == 0)
		cout << "조회할 데이터가 없네요 ㅠㅠ" << endl;
	else
	{
		char szName[50] = "";
		cout << "조회 하고자하는 분의 이름을 입력하세요 : ";
		cin >> szName;

		bool bResult = ShowData(szName);

		if (bResult == false)
			cout << "검색결과가 없습니다 ㅠ.ㅠ" << endl;

	}//	~if (_list.size() == 0)

	system("pause");

}//	void CAddressManager::Show()
//-------------------------------
void CAddressManager::ShowAll()
{
	system("cls");
	bool bResult = ShowAllData();

	if( bResult == false )
		cout << "조회할 데이터가 없네요 ㅠㅠ" << endl;

	system("pause");

}//	void CAddressManager::ShowAll()
//-------------------------------
void CAddressManager::DoError()
{
	system("cls");
	cout << "잘못 눌렀네요~ㅜ.ㅜ" << endl;

	system("pause");

}//	void CAddressManager::DoError()
//-------------------------------
void CAddressManager::Finish()
{
	system("cls");
	cout << "프로그램을 종료합니다." << endl;
	exit(1);

//	void CAddressManager::Finish()}
//-------------------------------