//================================================
#pragma once
#pragma warning( disable : 4996 )
//================================================
#include<iostream>
#include"CAccount.h"
using namespace std;
//================================================
class CKoreaAccount : public CAccount
{
	int _moneyLimit;
public:
	CKoreaAccount(const char* pszAccNum, int money, int moneyLimit);
	void ShowData();
};
//	class CKoreaAccount : public CAccount
//================================================