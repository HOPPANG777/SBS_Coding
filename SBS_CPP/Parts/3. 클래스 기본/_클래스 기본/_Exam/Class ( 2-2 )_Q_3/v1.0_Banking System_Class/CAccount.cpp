//=================================================================
#include"CAccount.h"
#include<iostream>
using namespace std;
#pragma warning( disable : 4996)
//=================================================================
const int NAMELEN = 20;			//	¿Ã∏ß ±Ê¿Ã..
//=================================================================
//--------------------------------
CAccount::CAccount()
{	
	_id = -1;
	_money = 0;
	_pszName = new char[NAMELEN];

}//	CAccount::CAccount()
//--------------------------------
CAccount::~CAccount()
{
	if (_pszName != nullptr)
	{
		delete[] _pszName;
		_pszName = nullptr;
	}

}//	CAccount::~CAccount()
//--------------------------------
void CAccount::SetInfo(int id, int money, char* pszName)
{
	_id = id;
	_money = money;
	strcpy(_pszName, pszName);

}//	void CAccount::SetInfo(int id, int money, char* pszName)
//--------------------------------
void CAccount::ShowInfo()
{
	cout << "1. ∞Ë¡¬ ID : " << _id << endl;
	cout << "2. ¿Ã ∏ß : " << _pszName << endl;
	cout << "3. ¿‹ æ◊ : " << _money << endl;

}//	void CAccount::ShowInfo()
//--------------------------------
void CAccount::Input(int money) { _money += money; }
//--------------------------------
void CAccount::Output(int money) { _money -= money; }
//--------------------------------
//=================================================================