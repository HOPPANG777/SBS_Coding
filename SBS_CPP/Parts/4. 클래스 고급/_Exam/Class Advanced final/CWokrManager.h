//==============================================================
#pragma once
//==============================================================
#include<iostream>
#include"CWorker.h"
//==============================================================
const int WORKERCOUNT = 10;
class CWorkManager
{
	CWorker* _pWorker[WORKERCOUNT];
	int _count;


	bool Register()
	{
		system("cls");
		cout << "--- 근로자 등록 ---" << endl;
		cout << "이름 : ";
		char szName[50];
		cin >> szName;

		cout << "고용 타입 : " << endl;
		cout << "1. 정규직    2. 일용직   3. 파트타임 " << endl;
		int select;
		cin >> select;

		switch (select)
		{
		case 1:
			Register_RegularWorker(szName);
			break;

		case 2:
			Register_DailyWorker(szName);
			break;

		case 3:
			Register_ParttimeWorker(szName);
			break;
		}

		++_count;


		return true;
	}
	//-------------------------------------
	void Register_RegularWorker(char *pszName)
	{
		system("cls");
		cout << "[ 정규직 설정 ]" << endl;
		cout << "  월급 : ( 만원 )";
		float salaryPerMonth;
		cin >> salaryPerMonth;
		_pWorker[_count] = new CRegularWorker(pszName, salaryPerMonth);
	}
	//-------------------------------------
	void Register_DailyWorker(char *pszName)
	{
		system("cls");
		cout << "[ 일용직 설정 ]" << endl;
		cout << "  일당 : ( 만원 )";
		float salaryPerDay;
		cin >> salaryPerDay;

		cout << "  근무 일수 : ";
		int workDay;
		cin >> workDay;
		_pWorker[_count] = new CDailyWorker(pszName, workDay, salaryPerDay);
	}
	//-------------------------------------
	void Register_ParttimeWorker(char *pszName)
	{
		system("cls");
		cout << "[ 파트타임 설정 ]" << endl;
		cout << "  시간 수당 : ( 만원 )";
		float salaryPerHour;
		cin >> salaryPerHour;

		cout << "  근무 시간 : ";
		int workHour;
		cin >> workHour;
		_pWorker[_count] = new CPartimeWorker(pszName, workHour, salaryPerHour);
	}
	//-------------------------------------
	int GetWorkerCount()
	{
		int count = 0;
		for (int i = 0; i < WORKERCOUNT; ++i)
		{
			if (_pWorker[i] != NULL)
				++count;
		}

		return count;
	}
	//-------------------------------------
	void FindAllWorker()
	{
		system("cls");

		int count = GetWorkerCount();

		if (count == 0)
		{
			cout << "등록된 작업자가 없네요!!!" << endl;
			getchar();
			getchar();
			return;
		}

		for (int i = 0; i < WORKERCOUNT; ++i)
		{
			if (_pWorker[i] != NULL)
				_pWorker[i]->ShowInfo();
		}

		getchar();
		getchar();
	}
	//-------------------------------------
	void RemoveWorker()
	{
		system("cls");

		int count = GetWorkerCount();

		if (count == 0)
		{
			cout << "등록된 작업자가 없네요!!!" << endl;
			getchar();
			getchar();
			return;
		}

		system("cls");
		cout << "[ 근로자 삭제 ]" << endl;
		cout << "삭제할 근로자의 이름을 입력하세요 : " << endl;
		char szName[50];
		cin >> szName;

		int removeIdx = -1;
		for (int i = 0; i < WORKERCOUNT; ++i)
		{
			if (_pWorker[i] != NULL && _pWorker[i]->IsEqualName(szName))
			{
				removeIdx = i;
				break;
			}
		}

		if (removeIdx != -1)
		{
			cout << "삭제하시겠습니까 ? " << endl;
			cout << "y : yes    n : no " << endl;
			char answer;
			cin >> answer;
			switch (answer)
			{
			case 'y':
			case 'Y':
				cout << "삭제 합니다." << endl;
				delete _pWorker[removeIdx];
				_pWorker[removeIdx] = NULL;
				break;

			case 'n':
			case 'N':
				cout << "취소 합니다." << endl;
				break;

			}//	switch (answer)

		}//	if (pTmpWorker != NULL)
		else
			cout << szName << "(이)라는 근로자가 없습니다." << endl;

		getchar();
		getchar();

	}//	void RemoveWorker()
	//-------------------------------------
	void EditWorker()
	{
		system("cls");

		int count = GetWorkerCount();

		if (count == 0)
		{
			cout << "등록된 작업자가 없네요!!!" << endl;
			getchar();
			getchar();
			return;
		}

		system("cls");
		cout << "[ 근로자 수정 ]" << endl;
		cout << "수정할 근로자의 이름을 입력하세요 : " << endl;
		char szName[50];
		cin >> szName;

		int editIdx = -1;
		for (int i = 0; i < WORKERCOUNT; ++i)
			if (_pWorker[i] != NULL && _pWorker[i]->IsEqualName(szName)) { editIdx = i; break; }

		if (editIdx != -1)
		{
			_pWorker[editIdx]->ShowInfo();

			char* pszWorkType = _pWorker[editIdx]->GetWorkType();

			if (strcmp(pszWorkType, "정규직") == 0)
			{
				cout << "  월급 : ( 만원 )";
				float salaryPerMonth;
				cin >> salaryPerMonth;

				CRegularWorker* pTmp = (CRegularWorker*)_pWorker[editIdx];
				pTmp->SetSalaryPerMonth(salaryPerMonth);
						
			}//	if (strcmp(pszWorkType, "정규직") == 0)
			else if (strcmp(pszWorkType, "일용직") == 0)
			{
				cout << "  일당 : ( 만원 )";
				float salaryPerDay;
				cin >> salaryPerDay;

				cout << "  근무 일수 : ";
				int workDay;
				cin >> workDay;

				CDailyWorker* pTmp = (CDailyWorker*)_pWorker[editIdx];
				pTmp->SetSalaryPerMonth(workDay, salaryPerDay);
			
			}//	else if (strcmp(pszWorkType, "일용직") == 0)
			else
			{
				cout << "  시간 수당 : ( 만원 )";
				float salaryPerHour;
				cin >> salaryPerHour;

				cout << "  근무 시간 : ";
				int workHour;
				cin >> workHour;

				CPartimeWorker* pTmp = (CPartimeWorker*)_pWorker[editIdx];
				pTmp->SetSalaryPerMonth(workHour, salaryPerHour);

			}

		}//	if (editIdx != -1)
		else
			cout << szName << "(이)라는 근로자가 없습니다." << endl;

		getchar();
		getchar();

	}//	void EditWorker()
	//-------------------------------------
public:
	//-------------------------------------
	CWorkManager()
	{
		for (int cur = 0; cur < WORKERCOUNT; ++cur)
			_pWorker[cur] = NULL;

		_count = 0;

	}//	CWorkManager()

	virtual ~CWorkManager()
	{
		for (int cur = 0; cur < WORKERCOUNT; ++cur)
			delete _pWorker[cur];

	}//	virtual ~CWorkManager()
	//-------------------------------------
	void Process()
	{
		while (1)
		{
			system("cls");

			cout << "어떤 작업을 하시겠습니까 ? " << endl;
			cout << "1. 등록    2. 조회   3. 삭제   4. 편집   5. 종료 " << endl;
			int select;
			cin >> select;
			switch(select)
			{
				case 1:
					Register();
					break;
				
				case 2:
					FindAllWorker();
					break;

				case 3:
					RemoveWorker();
					break;

				case 4:
					EditWorker();
					break;

				case 5:
					cout << "Bye~~" << endl;
					return;
				default:
					break;

			}//	switch(select)
			
		}//	while (1)

	}//	void Process()
	//-------------------------------------
};
//	class CWorkManager
//==============================================================