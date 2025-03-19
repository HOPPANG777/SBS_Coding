//=================================================
#include<iostream>

using namespace std;

int main()
{
	int studentCount;

	cout << "학생수 입력 : ";
	cin >> studentCount;

	int *pArr = new int [studentCount];

	int sum = 0;
	for (int i = 0; i < studentCount; ++i)
	{
		cout << i + 1 << " 번 학생 : ";
		cin >> pArr[i];
		sum += pArr[i];
	}

	float avg = (float)sum / studentCount;

	cout << "총점 : " << sum << endl;
	cout << "평균 : " << avg << endl;

	delete[] pArr;

	return 0;
}
//=================================================