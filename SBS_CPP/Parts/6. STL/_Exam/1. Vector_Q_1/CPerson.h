#pragma once

class CPerson
{
	char _szName[50];
	int _age;
    char _szAddress[100];
	char _szPhoneNumber[20];

public:
	CPerson(char* pszName, int age, char* pszAddress, char* pszPhoneNumber);
	
	const char* GetName() { return _szName; }
	void SetName(char *pszName) { strcpy(_szName, pszName); }

	int GetAge() { return _age; }
	void SetAge(int age) { _age = age; }

	const char* GetAddress() { return _szAddress; }
	void SetAddress(char *pszAddress) { strcpy(_szAddress, pszAddress); }

	const char* GetPhoneNumber() { return _szPhoneNumber; }
	void SetPhoneNumber(char *pszPhone) { strcpy(_szPhoneNumber, pszPhone); }

	void ShowInfo();
	
};