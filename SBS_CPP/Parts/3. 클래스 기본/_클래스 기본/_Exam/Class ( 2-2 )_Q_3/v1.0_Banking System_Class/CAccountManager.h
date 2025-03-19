//==================================================
#pragma once
//==================================================
#include<iostream>
#include"CAccount.h"
using namespace std;
//==================================================
const int ACCOUNT_SIZE = 100;	//	계좌정보 배열..
//==================================================
enum
{
	MAKEACCOUNT = 1,
	DEPOSIT,
	WITHDRAW,
	INQUIRE,
	INQUIREALL,
	EXIT,

};
//==================================================
//==================================================
class CAccountManager
{
	CAccount* _pAccountArray;	//	계좌정보 배열.
	int _curIndex;

public:
	CAccountManager();
	~CAccountManager();

	void ShowMenu();
	void MakeAccount();
	void Deposit();
	void Withdraw();
	void Inquire();
	void InquireAll();

	void Process();
};
//==================================================