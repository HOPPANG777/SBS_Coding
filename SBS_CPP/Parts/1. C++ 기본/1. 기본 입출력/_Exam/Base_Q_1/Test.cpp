#include <iostream>
using namespace std;
void main()
{
	int num1, num2, num3;
	int sum = 0;

	cout << "숫자를 3개 입력하세요. : " << endl;
	cin >> num1 >> num2 >> num3;

	sum = num1 + num2 + num3;

	cout << num1 << " + " << num2 << " + " << num3 << " = " << sum << endl;
}