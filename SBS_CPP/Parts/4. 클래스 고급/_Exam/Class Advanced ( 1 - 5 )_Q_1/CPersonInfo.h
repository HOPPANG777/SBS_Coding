//================================================
#pragma once
#pragma warning( disable : 4996 )
//================================================
#include<iostream>
using namespace std;
//================================================
class CPersonInfo
{
	char* _pszName;
	char* _pszPhone;
	int _age;

public:
	CPersonInfo(char* pszName, char* pszPhone, int age);
	CPersonInfo(const CPersonInfo& test);
	~CPersonInfo();
	void ShowData();
};
//================================================