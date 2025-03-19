//==================================================
#include<iostream>
#include"CAccountManager.h"
#pragma warning( disable : 4996)
using namespace std;
//==================================================
int main()
{
	CAccountManager* pAccount = new CAccountManager();

	pAccount->Process();

	delete pAccount;

	return 0;

}//	int main()
//-------------------------------