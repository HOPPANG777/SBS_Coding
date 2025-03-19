//=====================================================
#include "CWorkerManager.h"
using namespace std;
//=====================================================
CWorkerManager::~CWorkerManager() { 
	DeleteAllData();
	delete _pFactory;
	_pFactory = NULL;
}
//-------------------------------
void CWorkerManager::AddData(CWorker* pWorker) { _list.push_back(pWorker); }
//-------------------------------
bool CWorkerManager::EditData(char* pszName)
{
	ITER_WORKER iterBegin = _list.begin();
	ITER_WORKER iterEnd = _list.end();
	ITER_WORKER iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CWorker* pTmp = (*iterCur);
		if (strcmp(pTmp->GetName(), pszName) == 0)
		{
			char* pType = pTmp->GetWorkType();
			if (strcmp(pType, "정규직") == 0)
			{
				CRegularWorker* pReg = (CRegularWorker*)pTmp;
				cout << "급여를 입력하세요 : ";
				int monthSalary = 0;
				cin >> monthSalary;
				pReg->SetSalary( monthSalary );

			}else if (strcmp(pType, "일용직") == 0)
			{
				CDailyWorker* pDaily = (CDailyWorker*)pTmp;

				cout << "근무 날짜를 입력하세요 : ";
				int workday = 0;
				cin >> workday;
				cout << "일당을 입력하세요 : ";
				int money = 0;
				cin >> money;
				pDaily->SetSalary(workday, money);

			}
			else if (strcmp(pType, "파트타임") == 0)
			{
				CPartimeWorker* pPart = (CPartimeWorker*)pTmp;

				cout << "근무 시간을 입력하세요 : ";
				int workTime = 0;
				cin >> workTime;
				cout << "시급을 입력하세요 : ";
				int money = 0;
				cin >> money;
				pPart->SetSalary(workTime, money);
			}

			return true;

		}//	if (strcmp(pTmp->GetName(), pszName) == 0)

	}//	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)

	return false;

}//	bool CWorkerManager::EditData(char* pszName, CWorker* pWorker)
//-------------------------------
bool CWorkerManager::DeleteData(char* pszName)
{
	ITER_WORKER iterBegin = _list.begin();
	ITER_WORKER iterEnd = _list.end();
	ITER_WORKER iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CWorker* pTmp = (*iterCur);
		if (strcmp(pTmp->GetName(), pszName) == 0)
		{
			delete pTmp;
			pTmp = NULL;
			_list.erase(iterCur);

			return true;
		}
	}

	return false;

}//	void CWorkerManager::DeleteData(char* pszName)
//-------------------------------
bool CWorkerManager::DeleteAllData()
{
	if (_list.size() == 0)
		return false;

	ITER_WORKER iterBegin = _list.begin();
	ITER_WORKER iterEnd = _list.end();
	ITER_WORKER iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CWorker* pTmp = (*iterCur);
		delete pTmp;
		pTmp = NULL;
	}
	_list.clear();

	return true;

}//	void CWorkerManager::DeleteAllData()
//-------------------------------
bool CWorkerManager::ShowData(char* pszName)
{
	ITER_WORKER iterBegin = _list.begin();
	ITER_WORKER iterEnd = _list.end();
	ITER_WORKER iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CWorker* pTmp = (*iterCur);
		if (strcmp(pTmp->GetName(), pszName) == 0)
		{
			pTmp->ShowInfo();
			return true;
		}
	}
	return false;

}//	void CWorkerManager::ShowData(char* pszName)
//-------------------------------
bool CWorkerManager::ShowAllData()
{
	if (_list.size() == 0)
		return false;

	ITER_WORKER iterBegin = _list.begin();
	ITER_WORKER iterEnd = _list.end();
	ITER_WORKER iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		CWorker* pTmp = (*iterCur);
		pTmp->ShowInfo();
		cout << endl;
	}

	return true;

}//	void CWorkerManager::ShowAllData()
//-------------------------------
void CWorkerManager::Process()
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

		case EDIT:
			Edit();
			break;

		case FINISH:
			Finish();
			break;

		default:
			DoError();
			break;

		}//	switch (_select)

	}//	while (1)

}//	void CWorkerManager::Process()
//-------------------------------
void CWorkerManager::ShowMenu()
{
	system("cls");
	cout << "근로자 관리 프로그램입니다.\n" << "번호를 입력하세요~" << endl;
	cout << "1. 추가" << endl;
	cout << "2. 삭제" << endl;
	cout << "3. 전체 삭제" << endl;
	cout << "4. 조회" << endl;
	cout << "5. 전체 조회" << endl;
	cout << "6. 편집" << endl;
	cout << "7. 종료" << endl;

	cin >> _select;

	getchar();


}//	void CWorkerManager::ShowMenu()
//-------------------------------
void CWorkerManager::Add()
{
	system("cls");

	cout << "이름 : ";
	char szName[50] = "";
	cin >> szName;

	cout << "직종 :  1) 정규직   2) 일용직   3) 파트타임 : ";
	int select;
	cin >> select;
	CWorker* pWorker = NULL;
	switch (select)
	{
		case 1:
		{
			CRegularWorker* pReg = (CRegularWorker*)_pFactory->Create(REGULAR, szName);
			cout << "월급 : ";
			int salary;
			cin >> salary;
			pReg->SetSalary(salary);
			pWorker = pReg;
		}		
		break;

	case 2:
		{
			CDailyWorker* pDaily = (CDailyWorker*)_pFactory->Create(DAILY, szName);
			cout << "일 급여 : ";
			int salaryPerDay;
			cin >> salaryPerDay;
			cout << "근무 일수 : ";
			int workDay;
			cin >> workDay;
			pDaily->SetSalary(workDay, salaryPerDay);
			pWorker = pDaily;
		}		
		break;

	case 3:
		{
			CPartimeWorker* pPart = (CPartimeWorker*)_pFactory->Create(PARTTIME, szName);
			cout << "시간 급여 : ";
			int salaryPerTime;
			cin >> salaryPerTime;
			cout << "근무 시간 : ";
			int workTime;
			cin >> workTime;
			pPart->SetSalary(workTime, salaryPerTime);
			pWorker = pPart;
		}
		break;

	default:
		cout << "Ouch!!! My Fault!!!" << endl;
		getchar();
		getchar();
		return;

	}//	switch (select)

	AddData(pWorker);
	cout << szName << "님이 추가되었습니다" << endl;
	ShowAll();

	getchar();	

}//	void CWorkerManager::Add()
//-------------------------------
void CWorkerManager::Delete()
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

}//	void CWorkerManager::Delete()
//-------------------------------
void CWorkerManager::DeleteAll()
{
	system("cls");
	bool bResult = DeleteAllData();

	if (bResult)
		cout << "모든 데이터가 삭제되었습니다." << endl;
	else
		cout << "삭제할 데이터가 없네요 ㅠㅠ" << endl;

	system("pause");

}//	void CWorkerManager::DeleteAll()
//-------------------------------
void CWorkerManager::Show()
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
	}

	system("pause");

}//	void CWorkerManager::Show()
//-------------------------------
void CWorkerManager::ShowAll()
{
	system("cls");
	bool bResult = ShowAllData();

	if (bResult == false)
		cout << "조회할 데이터가 없네요 ㅠㅠ" << endl;

	system("pause");

}//	void CWorkerManager::ShowAll()
//-------------------------------
void CWorkerManager::Edit()
{
	system("cls");
	if (_list.size() == 0)
		cout << "편집할 데이터가 없네요 ㅠㅠ" << endl;
	else
	{
		char szName[50] = "";
		cout << "편집 하고자하는 분의 이름을 입력하세요 : ";
		cin >> szName;
		getchar();

		bool res = EditData(szName);

		if (res)
			cout << "편집 되었습니다." << endl;
		else
			cout << "편집 하려는 데이터가 없습니다 ㅠ.ㅠ" << endl;

	}//	~if (_list.size() == 0)

	system("pause");

}//	void CWorkerManager::Edit()
//-------------------------------
void CWorkerManager::DoError()
{
	system("cls");
	cout << "잘못 눌렀네요~ㅜ.ㅜ" << endl;

	system("pause");
}
//-------------------------------
void CWorkerManager::Finish()
{
	system("cls");
	cout << "프로그램을 종료합니다." << endl;
	exit(1);
}
//-------------------------------