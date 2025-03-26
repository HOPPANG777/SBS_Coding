#include "CPersonInfo.h"

CPersonInfo::CPersonInfo(const char* pszName, const char* pszPhone, int age)
{
	_pszName = new char[strlen(pszName) + 1];
	_pszPhone = new char[strlen(pszPhone) + 1];

	strcpy(_pszName, pszName);
	strcpy(_pszPhone, pszPhone);
	_age = age;
}
CPersonInfo::CPersonInfo(const CPersonInfo& test)
{
	_pszName = new char[strlen(test._pszName) + 1];
	_pszPhone = new char[strlen(test._pszPhone) + 1];

	strcpy(_pszName, test._pszName);
	strcpy(_pszPhone, test._pszPhone);
	
	_age = test._age;
}

CPersonInfo::~CPersonInfo()
{
	delete[] _pszName;
	delete[] _pszPhone;
}

void CPersonInfo::ShowData()
{
	cout << _pszName << endl;
	cout << _pszPhone << endl;
	cout << _age << endl;
}
