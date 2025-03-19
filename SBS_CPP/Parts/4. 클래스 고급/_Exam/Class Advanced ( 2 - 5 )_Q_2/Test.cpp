//===============================================================
#include<iostream>
#include "CKBAccount.h"
#include "CKoreaAccount.h"
using namespace std;
//===============================================================
int main()
{
	CKoreaAccount korAcc("123-456-789", 100, 1000);
	korAcc.ShowData();

	cout << endl;

	CKBAccount kbAcc("111-222-333", 200, 3500, 3.6f);
	kbAcc.ShowData();

	return 0;

}//	int main()
//===============================================================