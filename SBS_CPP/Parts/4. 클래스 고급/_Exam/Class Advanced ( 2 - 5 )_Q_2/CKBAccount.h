//===========================================================================
#pragma once
#include "CKoreaAccount.h"
//===========================================================================
class CKBAccount : public CKoreaAccount
{
	float _interestRate;
public:
	CKBAccount(const char* pszAccNum, int money, int moneyLimit, float _interestRate);
	void ShowData();
};
//	class CKBAccount : public CKoreaAccount
//===========================================================================