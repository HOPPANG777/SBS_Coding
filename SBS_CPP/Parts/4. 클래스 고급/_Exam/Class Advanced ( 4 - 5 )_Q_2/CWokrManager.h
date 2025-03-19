//==============================================================
#pragma once
//==============================================================
#include<iostream>
#include"CWorker.h"
//==============================================================
const int WORKERCOUNT = 5;
class CWorkManager
{
	CWorker* _pWorker[ WORKERCOUNT ];
	int _count;

	void Register()
	{
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

		}//	switch (select)

		++_count;

	}//	void Register()
	//-------------------------------------
	void Register_RegularWorker(char *pszName)
	{
		cout << "[ 정규직 설정 ]" << endl;
		cout << "  월급 : ";
		int salaryPerMonth;
		cin >> salaryPerMonth;
		_pWorker[_count] = new CRegularWorker(pszName, salaryPerMonth);
	
	}//	void Register_RegularWorker(char *pszName)
	//-------------------------------------
	void Register_DailyWorker(char *pszName)
	{
		cout << "[ 일용직 설정 ]" << endl;
		cout << "  일당 : ";
		int salaryPerDay;
		cin >> salaryPerDay;

		cout << "  근무 일수 : ";
		int workDay;
		cin >> workDay;
		_pWorker[_count] = new CDailyWorker(pszName, workDay, salaryPerDay);

	}//	void Register_DailyWorker(char *pszName)
	//-------------------------------------
	void Register_ParttimeWorker(char *pszName)
	{
		cout << "[ 파트타임 설정 ]" << endl;
		cout << "  시간 수당 : ";
		int salaryPerHour;
		cin >> salaryPerHour;

		cout << "  근무 시간 : ";
		int workHour;
		cin >> workHour;		
		_pWorker[_count] = new CPartimeWorker(pszName, workHour, salaryPerHour);

	}//	void Register_ParttimeWorker(char *pszName)
	//-------------------------------------
	void FindAllWorker()
	{
		system("cls");
		int cur = 0;
		if (_pWorker[cur] == NULL)
		{
			cout << "등록된 작업자가 없네요!!!" << endl;
			getchar();
			getchar();
			return;
		}

		while (_pWorker[cur] != NULL)
		{
			_pWorker[cur]->ShowInfo();
			++cur;
		}

		getchar();
		getchar();

	}//	void FindAllWorker()
	//-------------------------------------
public:
	//-------------------------------------
	CWorkManager()
	{
		for (int cur = 0; cur < WORKERCOUNT; ++cur)
			_pWorker[cur] = NULL;

		_count = 0;
	}

	virtual ~CWorkManager()
	{
		for (int cur = 0; cur < WORKERCOUNT; ++cur)
		{
			if (_pWorker[cur] != NULL)
			{
				delete _pWorker[cur];
				_pWorker[cur] = NULL;
			}
		}

	}//	virtual ~CWorkManager()
	//-------------------------------------
	void Process()
	{
		while (1)
		{
			system("cls");

			cout << "어떤 작업을 하시겠습니까 ? " << endl;
			cout << "1. 등록    2. 조회   3. 종료 " << endl;
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
					cout << "Bye~~" << endl;
					return;
				default:					
					cout << "Wrong Input~~!!" << endl;
					system("pause");
					break;

			}//	switch(select)
			
		}//	while (1)

	}//	void Process()
	//-------------------------------------
};
//==============================================================