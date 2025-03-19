#pragma once
using namespace std;
class CPerson
{
	string _szName;
	int _age;
    char _szAddress[100];
	char _szPhoneNumber[20];

public:
	CPerson(string szName, int age, char* pszAddress, char* pszPhoneNumber);
	string GetName() { return _szName; }
	void ShowInfo();
};