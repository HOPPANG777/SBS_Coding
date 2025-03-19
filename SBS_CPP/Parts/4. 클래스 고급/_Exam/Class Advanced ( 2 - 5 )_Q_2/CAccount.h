//================================================
#pragma once
#pragma warning( disable : 4996 )
//================================================
#include<iostream>
using namespace std;
//================================================
class CAccount
{
	int _money;
	char _accNum[20];

public:

	CAccount(const char* pszAccNum, int money);
	void ShowData();
};
//	class CAccount
//================================================