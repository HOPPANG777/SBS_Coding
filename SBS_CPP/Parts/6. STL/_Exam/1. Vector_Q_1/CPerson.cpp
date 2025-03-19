//=======================================================
#pragma warning( disable : 4996 )
#include<iostream>
#include"CPerson.h"
using namespace std;
//=======================================================
CPerson::CPerson(char* pszName, int age, char* pszAddress, char* pszPhoneNumber)
{
	SetName(pszName);
	SetAge(age);
	SetAddress(pszAddress);
	SetPhoneNumber(pszPhoneNumber);
}
//----------------------------------------------
void CPerson::ShowInfo()
{
	cout << "이름 : " << _szName << endl;
	cout << "나이 : " << _age << endl;
    cout << "주소 : " << _szAddress << endl;
	cout << "전화번호 : " << _szPhoneNumber << endl;
}
//=======================================================//