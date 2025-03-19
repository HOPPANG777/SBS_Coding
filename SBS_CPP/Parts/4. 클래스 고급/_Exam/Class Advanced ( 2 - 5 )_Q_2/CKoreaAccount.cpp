//===========================================================================
#include "CKoreaAccount.h"
//===========================================================================
CKoreaAccount::CKoreaAccount(const char* pszAccNum, int money, int moneyLimit)
	: CAccount(pszAccNum, money)
{
	_moneyLimit = moneyLimit;
}
//===========================================================================
void CKoreaAccount::ShowData()
{
	CAccount::ShowData();
	cout << "이체 한도 : " << _moneyLimit << endl;
}
//===========================================================================//