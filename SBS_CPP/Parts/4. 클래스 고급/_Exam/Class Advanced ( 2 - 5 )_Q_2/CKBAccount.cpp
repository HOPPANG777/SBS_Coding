//===========================================================================
#include "CKBAccount.h"
//===========================================================================
CKBAccount::CKBAccount(const char* pszAccNum, int money, int moneyLimit, float interestRate)
	: CKoreaAccount(pszAccNum, money, moneyLimit) 
{
	_interestRate = interestRate;
}
//===========================================================================
void CKBAccount::ShowData()
{
	CKoreaAccount::ShowData();
	cout << "ÀÌÀÚÀ² : " << _interestRate << endl;
}
//===========================================================================