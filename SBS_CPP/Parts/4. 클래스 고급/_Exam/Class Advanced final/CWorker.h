//================================================
#pragma once
#pragma warning( disable : 4996 )
//================================================
#include<iostream>
using namespace std;
//================================================
class CWorker
{
protected:
	char _szName[30];		//	이름..
	char _szWorkType[30];	//	고용타입..
	float _salaryPerMonth;	//	월급..	
	virtual void CalculateSalary() = 0;	//	월급 계산..
	void SetName(const char* pszName) { strcpy(_szName, pszName); }
	void SetWorkType(const char* pszWorkType) { strcpy(_szWorkType, pszWorkType); }	
	
public:
	CWorker(const char* pszName)
	{
		memset(_szName, 0, sizeof(_szName));
		memset(_szWorkType, 0, sizeof(_szWorkType));
		SetName(pszName);
		_salaryPerMonth = 0;
	}

	void ShowInfo() { cout << "이름 : " << _szName << "   고용 타입 : " << _szWorkType << "   급여 : " << _salaryPerMonth << " 만원" << endl; }

	bool IsEqualName(const char* pszName)
	{
		if (strcmp(_szName, pszName) == 0)
			return true;

		return false;
	}

	char* GetWorkType() { return _szWorkType; }
	virtual ~CWorker(){}
};
//	CWorker
//================================================
class CRegularWorker : public CWorker
{
public:
	CRegularWorker(const char* pszName, float salaryPerMonth) : CWorker(pszName)
	{
		SetSalaryPerMonth( salaryPerMonth );
		CalculateSalary();
		SetWorkType("정규직");
	}
	virtual ~CRegularWorker() {}
	void SetSalaryPerMonth(float salary) { _salaryPerMonth = salary; }
	virtual void CalculateSalary()	{}
};
//================================================
class CDailyWorker : public CWorker
{
	int _workDay;
	float _salaryPerDay;

public:
	CDailyWorker(const char* pszName, int workDay, float salaryPerDay) : CWorker(pszName)
	{
		SetSalaryPerMonth(workDay, salaryPerDay);
		SetWorkType("일용직");
	}
	virtual ~CDailyWorker() {}

	void SetSalaryPerMonth(int workDay, float salaryPerDay)
	{
		_workDay = workDay;
		_salaryPerDay = salaryPerDay;
		CalculateSalary();
	}

	virtual void CalculateSalary() { _salaryPerMonth = _workDay * _salaryPerDay; }
};
//================================================
class CPartimeWorker : public CWorker
{
	int _workHour;
	float _salaryPerHour;

public:
	CPartimeWorker(const char* pszName, int workHour, float salaryPerHour) : CWorker(pszName)
	{
		SetSalaryPerMonth(workHour, salaryPerHour);
		SetWorkType("파트타임");
	}
	virtual ~CPartimeWorker() {}

	void SetSalaryPerMonth(int workHour, float salaryPerHour)
	{
		_workHour = workHour;
		_salaryPerHour = salaryPerHour;
		CalculateSalary();
	}
	virtual void CalculateSalary() { _salaryPerMonth = _workHour * _salaryPerHour; }
};
//================================================//