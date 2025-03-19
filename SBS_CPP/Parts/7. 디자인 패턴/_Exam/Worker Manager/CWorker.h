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
	int _salaryPerMonth;	//	월급..	
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
	char* GetName() { return _szName; }
	char* GetWorkType() { return _szWorkType; }
	void ShowInfo() { cout << "이름 : " << _szName << "   고용 타입 : " << _szWorkType << "   급여 : " << _salaryPerMonth << endl; }

	virtual ~CWorker(){}
};
//	CWorker
//================================================
class CRegularWorker : public CWorker
{
public:
	CRegularWorker(const char* pszName) : CWorker(pszName){ SetWorkType("정규직"); }
	CRegularWorker(const char* pszName, int salaryPerMonth) : CWorker(pszName)
	{
		_salaryPerMonth = salaryPerMonth;
		CalculateSalary();
	}
	void SetSalary(int salary) { _salaryPerMonth = salary; }
	virtual ~CRegularWorker() {}

	virtual void CalculateSalary()	{}
};
//================================================
class CDailyWorker : public CWorker
{
	int _workDay;
	int _salaryPerDay;

public:
	CDailyWorker(const char* pszName) : CWorker(pszName) { SetWorkType("일용직"); }
	CDailyWorker(const char* pszName, int workDay, int salaryPerDay) : CWorker(pszName)
	{
		SetSalary(workDay, salaryPerDay);
	}	
	virtual ~CDailyWorker() {}

	void SetSalary(int workDay, int salaryPerDay) {
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
	int _salaryPerHour;

public:
	CPartimeWorker(const char* pszName) : CWorker(pszName) { SetWorkType("파트타임"); }
	CPartimeWorker(const char* pszName, int workHour, int salaryPerHour) : CWorker(pszName)
	{
		SetSalary(workHour, salaryPerHour);
	}
	virtual ~CPartimeWorker() {}

	void SetSalary(int workHour, int salaryPerHour) {
		_workHour = workHour;
		_salaryPerHour = salaryPerHour;
		CalculateSalary();
	}

	virtual void CalculateSalary() { _salaryPerMonth = _workHour * _salaryPerHour; }
};
//================================================//