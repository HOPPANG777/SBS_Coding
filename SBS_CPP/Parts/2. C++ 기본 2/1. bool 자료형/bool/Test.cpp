//=================================================
/*
	
	bool 형 변수..

	-	c++에서 추가된 기본 자료형..

	-	[ true ]와 [ false ]만
		관리..

	-	크기는 1Byte..

		ㄴ	true와 false만 관리하므로
			[ 1Bit ]만 있어도 충분..
			
			ㄴ	하지만 프로그램에서 다루는
				기본 데이터의 단위가 바이트..
			

*/
//=================================================
#include<iostream>
using namespace std;
//=================================================
bool IsPositive(int nNum)
{
	if (nNum < 0)
		return false;
	else
		return true;

}//	bool IsPositive(int nNum)
//=================================================
int main()
{
	int nNum;
	bool bResult;

	cout << "숫자 입력 : ";
	cin >> nNum;

	bResult = IsPositive(nNum);

	if (bResult == true)
		cout << nNum << " (은)는 양수!!" << endl;
	else
		cout << nNum << " (은)는 음수!!" << endl;

	cout << "bool 의 크기 : " << sizeof(bool) << endl;

	/*
		true와 false는
		각각 int형 정수인 1, 0으로
		묵시적 형변환이 이뤄짐..
	*/
	int boolValue = true;
	cout << "true == " << boolValue << endl;
	boolValue = false;
	cout << "false == " << boolValue << endl;

	return 0;

}//	int main()
//=================================================