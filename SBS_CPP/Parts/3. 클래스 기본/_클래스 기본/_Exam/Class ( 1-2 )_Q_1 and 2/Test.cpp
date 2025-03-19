//=================================================
#include<iostream>
using namespace std;
//=================================================
//*	only 구조체 ..
struct SAccount
{
	char _name[30];
	int _money;
};

void Deposit(SAccount *pAccount, int money)		{ pAccount->_money += money; }
void WithDraw(SAccount *pAccount, int money)	{ pAccount->_money -= money; }
void ShowMetheMoney(SAccount account)			{ cout << account._name << "\'s " << "Money is " << account._money << endl; }
//*/


/*	구조체 + 함수
struct SAccount
{
public:
	char _name[30];
	int _money;

	void Deposit(int money)		{ _money += money; ShowMetheMoney(); }
	void WithDraw(int money)	{ _money -= money; ShowMetheMoney(); }
//private:
	void ShowMetheMoney()		{ cout << _name <<"\'s" << "money is " << _money << endl; }
};
//*/



int main()
{
	SAccount myAccount = { "홍길동", 10000 };

	//*	only 구조체 ..
	ShowMetheMoney(myAccount);

	Deposit(&myAccount, 1000);
	ShowMetheMoney(myAccount);

	WithDraw(&myAccount, 500);
	ShowMetheMoney(myAccount);
	//*/

	/*	구조체 + 함수
	myAccount.ShowMetheMoney();
	myAccount.Deposit( 1000 );
	myAccount.WithDraw( 500 );
	//*/

	return 0;

}//	int main()
 //=================================================