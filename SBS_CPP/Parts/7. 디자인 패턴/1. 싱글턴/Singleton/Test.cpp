//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
#include"SingletonTemplate.h"
//=================================================
class CTest : public CSingletonTemplate<CTest>
{
public:
	void ShowTest()
	{
		cout << "Template Test!!!" << endl;
	}
};
//=================================================
int main()
{
	CTest::GetInst()->ShowTest();

	CTest::GetInst()->Destroy();

	return 0;
}
//=================================================