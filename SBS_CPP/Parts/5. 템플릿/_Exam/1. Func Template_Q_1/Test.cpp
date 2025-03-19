//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
//	ÇÔ¼ö ÅÛÇÃ¸´.
template <typename T>
T Add(T a, T b) { return a + b; }

template <typename T>
T Minus(T a, T b) { return a - b; }

template <typename T>
T Multi(T a, T b) { return a * b; }

template <typename T>
T Divide(T a, T b) { return a / b; }

int main()
{
	cout << Add(1.1f, 2.2f) << endl;

	cout << Minus(10, 2) << endl;

	cout << Multi(10, 2) << endl;

	cout << Divide(10, 3) << endl;

	cout << Divide(10.f, 2.2f) << endl;
	
	return 0;
}