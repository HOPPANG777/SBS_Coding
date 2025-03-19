//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
#include"CScoreManager.h"
//=================================================
int main()
{
	CScoreManager* pScoreManager = new CScoreManager();
	
	pScoreManager->Process();
	
	delete pScoreManager;

	return 0;

}//	int main()
//=================================================