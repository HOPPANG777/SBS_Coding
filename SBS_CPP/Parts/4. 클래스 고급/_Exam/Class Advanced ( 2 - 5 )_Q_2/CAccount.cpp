//===========================================================================
#include "CAccount.h"
//===========================================================================
CAccount::CAccount(const char* pszAccNum, int money)
{
	strcpy(_accNum, pszAccNum);
	_money = money;

}//	CAccount::CAccount(char* pszAccNum, int money)
//----------------------------------------------
void CAccount::ShowData()
{
	cout << "°èÁÂ ¹øÈ£ : " << _accNum << endl;
	cout << "°èÁÂ ÀÜ¾× : " << _money << endl;

}//	void CAccount::ShowData()
//===========================================================================//