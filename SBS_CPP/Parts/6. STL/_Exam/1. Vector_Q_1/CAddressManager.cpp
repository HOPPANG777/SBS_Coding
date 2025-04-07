//=====================================================
#include "CAddressManager.h"
using namespace std;
//=====================================================
CAddressManager::~CAddressManager()	{ DeleteAllData(); }
//-------------------------------
//	추가..
void CAddressManager::AddData(CPerson* pPerson)	{ _list.push_back(pPerson); }
//-------------------------------
//	삭제..
bool CAddressManager::DeleteData(char* pszName)
{
	CPERSONVEC_ITER iterBegin = _list.begin();
	CPERSONVEC_ITER iterEnd = _list.end();
	CPERSONVEC_ITER iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CPerson* pTmp = (*iterCur);
		if (strcmp(pTmp->GetName(), pszName) == 0)
		{
			delete pTmp;
			pTmp = NULL;

			_list.erase(iterCur);

			return true;

		}//	if (strcmp(pTmp->GetName(), pszName) == 0)

	}//	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	
	return false;

}//	void CAddressManager::DeleteData(char* pszName)
//-------------------------------
//	전체 삭제..
bool CAddressManager::DeleteAllData()
{
	if (_list.size() == 0)
		return false;

	CPERSONVEC_ITER iterBegin = _list.begin();
	CPERSONVEC_ITER iterEnd = _list.end();
	CPERSONVEC_ITER iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CPerson *pTmp = (*iterCur);
		delete pTmp;
		pTmp = NULL;

		//_list.erase(iterCur);
	}
	_list.clear();

	return true;

}//	void CAddressManager::DeleteAllData()
//-------------------------------
//	이름으로 인덱스 탐색..
int CAddressManager::GetIndex(char *pszName)
{
	int idx = -1;
	CPERSONVEC_ITER iterBegin = _list.begin();
	CPERSONVEC_ITER iterEnd = _list.end();
	CPERSONVEC_ITER iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		++idx;
		CPerson *pTmp = (*iterCur);
		if (strcmp(pTmp->GetName(), pszName) == 0)
			return idx;

	}//	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)

	return -1;

}//	int CAddressManager::GetIndex(char *pszName)
//-------------------------------
//	특정 인물의 정보 출력..
bool CAddressManager::ShowData(char* pszName)
{
	CPERSONVEC_ITER iterBegin = _list.begin();
	CPERSONVEC_ITER iterEnd = _list.end();
	CPERSONVEC_ITER iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CPerson *pTmp = (*iterCur);
		if (strcmp(pTmp->GetName(), pszName) == 0) {
			pTmp->ShowInfo(); return true; }

	}//	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	
	return false;

}//	void CAddressManager::ShowData(char* pszName)
//-------------------------------
//	모든 정보 출력..
bool CAddressManager::ShowAllData()
{
	if( _list.size() == 0)
		return false;

	CPERSONVEC_ITER iterBegin = _list.begin();
	CPERSONVEC_ITER iterEnd = _list.end();
	CPERSONVEC_ITER iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CPerson *pTmp = (*iterCur);
		pTmp->ShowInfo();
		cout << endl;

	}//	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)

	return true;

}//	void CAddressManager::ShowAllData()
//-------------------------------
//	 전체 프로세스 처리..
void CAddressManager::Process()
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

			case FINISH: Finish(); break;

			default: DoError(); break;
		
		}//	switch (_select)

	}//	while (1)

}//	void CAddressManager::Process()
//-------------------------------
//	메뉴 출력..
void CAddressManager::ShowMenu()
{
	system("cls");
	cout << "주소록 관리 프로그램입니다.\n" << "번호를 입력하세요~" << endl;
	cout << "1. 추가" << endl;
	cout << "2. 삭제" << endl;
	cout << "3. 전체 삭제" << endl;
	cout << "4. 조회" << endl;
	cout << "5. 전체 조회" << endl;
	cout << "6. 편집" << endl;
	cout << "7. 종료" << endl;

	cin >> _select;

	getchar();


}//	void CAddressManager::ShowMenu()
//-------------------------------
//	주소록 등록..
void CAddressManager::Add()
{
	system("cls");

	cout << "이름 : ";	
    char szName[50] = "";
	cin >> szName;

	cout << "전화 번호 : ";
	char szPhone[50] = "";
	cin >> szPhone;

    cout << "주소 : ";
    char szAddress[50] = "";
    cin >> szAddress;

	int age = 0;
	cout << "나이 : ";
	cin >> age;

	CPerson *pPerson = new CPerson(szName, age, szAddress, szPhone);
	AddData(pPerson);
	cout << szName << "님이 추가되었습니다" << endl;

	getchar();
	getchar();

}//	void CAddressManager::Add()
//-------------------------------
//	주소록에서 제거..
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

}//	void CAddressManager::Delete()
//-------------------------------
void CAddressManager::DeleteAll()
{
	system("cls");
	bool bResult = DeleteAllData();

	if (bResult)
		cout << "모든 데이터가 삭제되었습니다." << endl;
	else
		cout << "삭제에 실패 했습니다ㅠㅠ" << endl;

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
			cout << "검색 결과가 없습니다 ㅠ.ㅠ" << endl;

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
void CAddressManager::Edit()
{
	system("cls");
	if (_list.size() == 0)
		cout << "편집할 데이터가 없네요 ㅠㅠ" << endl;
	else
	{
		char szName[50] = "";
		cout << "편집 하고자하는 분의 이름을 입력하세요 : ";
		cin >> szName;

		int idx = GetIndex(szName);

		if( idx == -1 )
			cout << "존재하지 않는 이름입니다 ㅠㅠ" << endl;
		else
		{
			int select = 0;
			cout << "1.이름   2.나이   3.주소,   4.전화번호" << endl;
			cout << "어떤 정보를 수정할까요?? : ";
			cin >> select;
			cout << "정보를 입력해주세요." << endl;			
			switch (select)
			{
				case 1:
				{
					char szTmp[50];
					cin >> szTmp;
					_list[idx]->SetName(szTmp);
				}
				break;

				case 2:
					int tmpAge;
					cin >> tmpAge;
					_list[idx]->SetAge(tmpAge);
					break;

				case 3:
				{
					char szTmp[50];
					cin >> szTmp;
					_list[idx]->SetAddress(szTmp);
				}
				break;

				case 4:
				{
					char szTmp[50];
					cin >> szTmp;
					_list[idx]->SetPhoneNumber(szTmp);
				}
				break;
			}
			getchar();
			_list[idx]->ShowInfo();
			getchar();
		
		}//	~if( idx == -1 )

	}//	~if (_list.size() == 0)

}//	void CAddressManager::Edit()
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

}//	void CAddressManager::Finish()
//-------------------------------