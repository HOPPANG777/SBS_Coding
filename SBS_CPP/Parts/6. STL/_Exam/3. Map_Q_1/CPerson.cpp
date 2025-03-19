#pragma warning( disable : 4996 )
#include<iostream>
#include"CPerson.h"
using namespace std;
CPerson::CPerson(string szName, int age, char* pszAddress, char* pszPhoneNumber)
{
	_szName = szName;
	_age = age;
	strcpy(_szPhoneNumber, pszPhoneNumber);
    strcpy(_szAddress, pszAddress);
}

void CPerson::ShowInfo()
{
	cout << "이름 : " << _szName.c_str() << endl;
	cout << "나이 : " << _age << endl;
    cout << "주소 : " << _szAddress << endl;
	cout << "전화번호 : " << _szPhoneNumber << endl;
}
