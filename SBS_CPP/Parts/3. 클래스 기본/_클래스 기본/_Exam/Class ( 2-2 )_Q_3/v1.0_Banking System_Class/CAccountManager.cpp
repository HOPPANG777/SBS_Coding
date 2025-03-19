//===================================================================
#include "CAccountManager.h"
//===================================================================
//-------------------------------------------------
CAccountManager::CAccountManager()
{
	_pAccountArray = new CAccount[ ACCOUNT_SIZE ];
	_curIndex = 0;
}
//-------------------------------------------------
CAccountManager::~CAccountManager()	{

	if (_pAccountArray != NULL)
	{
		delete[] _pAccountArray;
		_pAccountArray = NULL;
	}
}
//-------------------------------------------------
//	메뉴 보기..
//-------------------------
void CAccountManager::ShowMenu()
{
	system("cls");

	cout << "----- Menu -----" << endl;
	cout << "1. 계좌 개설" << endl;
	cout << "2. 입 금" << endl;
	cout << "3. 출 금" << endl;
	cout << "4. 조 회" << endl;
	cout << "5. 전체 조회" << endl;
	cout << "6. 종 료" << endl;

}//	void CAccountManager::ShowMenu()
//-------------------------------------------------
//	계좌 개설..
//-------------------------
void CAccountManager::MakeAccount()
{
	system("cls");

	int id;
	char name[100];
	int money;

	cout << "-- 계좌 개설 --" << endl;
	cout << "1. 계좌 ID : ";	cin >> id;
	cout << "2. 이 름 : ";		cin >> name;
	cout << "3. 입금액 : ";		cin >> money;
	_pAccountArray[_curIndex].SetInfo(id, money, name);

	++_curIndex;

	cout << "개설되었습니다.!!" << endl;

	getchar();
	getchar();

}//	void CAccountManager::MakeAccount()
//-------------------------------------------------
//	입 금..
//-------------------------
void CAccountManager::Deposit()
{
	system("cls");

	int id;
	cout << "-- 입금할 계좌 ID : ";	cin >> id;

	for (int curId = 0; curId < _curIndex; ++curId)
	{
		if (_pAccountArray[curId].GetID() == id)
		{
			int money;

			cout << "입금할 금액 : ";	cin >> money;
			_pAccountArray[curId].Input(money);
			cout << "-- 입금 완료!!--" << endl;
			getchar();
			getchar();
			return;

		}//	if (g_AccountArray[curId]._id == id)

	}//	for (int curId = 0; curId < g_index; ++curId)

	cout << "-- 찾고자 하는 ID가 없습니다. !!--" << endl;

	getchar();
	getchar();

}//	void CAccountManager::Deposit()
//-------------------------------------------------
//	출 금..
//-------------------------
void CAccountManager::Withdraw()
{
	system("cls");

	int id;
	cout << "-- 출금할 계좌 ID : ";	cin >> id;

	for (int curId = 0; curId < _curIndex; ++curId)
	{
		if (_pAccountArray[curId].GetID() == id)
		{
			int money;

			cout << "출금할 금액 : ";	cin >> money;
			_pAccountArray[curId].Output(money);
			cout << "-- 출금 완료!!--" << endl;
			getchar();
			getchar();
			return;

		}//	if (g_AccountArray[curId]._id == id)

	}//	for (int curId = 0; curId < g_index; ++curId)

	cout << "-- 찾고자 하는 ID가 없습니다. !!--" << endl;

	getchar();
	getchar();

}//	void CAccountManager::Withdraw()
//-------------------------------------------------
//	검색후 조회..
//-------------------------
void CAccountManager::Inquire()
{
	system("cls");

	int id;
	cout << "-- 조회할 계좌 ID : ";	cin >> id;

	for (int curId = 0; curId < _curIndex; ++curId)
	{
		if (_pAccountArray[curId].GetID() == id)
		{
			_pAccountArray[curId].ShowInfo();
			getchar();
			getchar();
			return;

		}//	if (_pAccountArray[curId]._id == id)

	}//	for (int curId = 0; curId < g_index; ++curId)

	cout << "-- 찾고자 하는 ID가 없습니다. !!--" << endl;

	getchar();
	getchar();

}//	void CAccountManager::Inquire()
//-------------------------------------------------
//	전체 조회..
//-------------------------
void CAccountManager::InquireAll()
{
	system("cls");

	if (_curIndex == 0)
		cout << "개설된 계좌가 없습니다.!!" << endl;
	else
	{
		for (int curId = 0; curId < _curIndex; ++curId)
		{
			cout << "---------" << endl;
			_pAccountArray[curId].ShowInfo();
			cout << endl;

		}//	for (int curId = 0; curId < g_index; ++curId)

	}//	if(g_index == 0)

	getchar();
	getchar();

}//	void CAccountManager::InquireAll()
//-------------------------------------------------
//	프로세스 진행..
//-------------------------
void CAccountManager::Process()
{
	int select;

	while (1)
	{
		ShowMenu();
		cout << "-- 선택 : ";	cin >> select;

		switch (select)
		{
		case MAKEACCOUNT:
			MakeAccount();
			break;

		case DEPOSIT:
			Deposit();
			break;

		case WITHDRAW:
			Withdraw();
			break;

		case INQUIRE:
			Inquire();
			break;

		case INQUIREALL:
			InquireAll();
			break;

		case EXIT:
			return;

		default:
			cout << " 다시 선택하세요 !!" << endl;
			system("pause");
			break;

		}//	switch (select)

	}//	while (1)

}//	void CAccountManager::Process()
//-------------------------------------------------
//===================================================================//