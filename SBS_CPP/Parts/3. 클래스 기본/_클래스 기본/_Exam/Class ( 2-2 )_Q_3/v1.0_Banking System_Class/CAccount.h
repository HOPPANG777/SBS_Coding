//=================================================================
#pragma once
//=================================================================
class CAccount
{
	int _id;		//	계좌번호..
	int _money;		//	보유금액..
	char* _pszName;	//	이름..

public:
	CAccount();
	~CAccount();
	void SetInfo(int id, int money, char* pszName);
	void ShowInfo();
	void Input(int money);
	void Output(int money);
	int GetID() { return _id; }

};
// class CAccount
//=================================================================