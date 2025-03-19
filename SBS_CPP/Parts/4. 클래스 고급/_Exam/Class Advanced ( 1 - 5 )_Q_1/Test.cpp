#include<iostream>
#include"CPersonInfo.h"

using namespace std;

int main()
{
	CPersonInfo Kim("Kim", "010xxxxxxxx", 20);
	CPersonInfo Kim2 = Kim;

	Kim.ShowData();
	Kim2.ShowData();

	return 0;
}