#include <iostream>
using namespace std;
void main()
{
	int gugudan;
	cout << "몇 단을 출력할까요? : ( -1 은 종료 )";
	cin >> gugudan;

	while (gugudan != -1)
	{
		for (int i = 1; i <= 9; ++i)
			cout << gugudan << " x " << i << " = " << gugudan * i << endl;

		cout << "몇 단을 출력할까요? : ( -1 은 종료 )";
		cin >> gugudan;
	}
}