//==================================================
#include <iostream>
#include <stdlib.h>
#include"Func.h"
using namespace std;
//==================================================
int main()
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
			return 0;

		default :
			cout << " 다시 선택하세요 !!" << endl;
			system("pause");
			break;

		}//	switch (select)
		
	}//	while (1)

	return 0;

}//	int main()
//-------------------------------