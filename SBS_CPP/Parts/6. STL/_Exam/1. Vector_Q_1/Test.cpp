//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
#include"CAddressManager.h"
//=================================================
int main()
{
	CAddressManager* pAddressManager = new CAddressManager();
	
	pAddressManager->Process();
	
	delete pAddressManager;

	return 0;

}//	int main()
//=================================================