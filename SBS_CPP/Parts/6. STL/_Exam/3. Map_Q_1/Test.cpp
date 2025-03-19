//=================================================
/*
	[ Âü°í : 
			https://ehpub.co.kr/7-5-stl%EC%9D%98-map-%EC%82%AC%EC%9A%A9/
			https://ehpub.co.kr/7-5-1-stl-map-%ec%82%ac%ec%9a%a9-%eb%b0%a9%eb%b2%95-1/
			https://ehpub.co.kr/7-5-2-stl-map-%ec%82%ac%ec%9a%a9-%eb%b0%a9%eb%b2%95-2/
	]
*/
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