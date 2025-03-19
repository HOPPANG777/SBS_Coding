//=================================================
#include<iostream>
#include"CStack.h"
//=================================================
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
int main()
{
	CStack< char > stackChar;
	stackChar.Push('a');
	stackChar.Push('b');
	stackChar.Push('c');
	int size = stackChar.GetCount();
	for (int i = 0; i < size; ++i)
		cout << stackChar.Pop() << endl;

	cout << endl;

	CStack< int > stackInt;
	stackInt.Push(10);
	stackInt.Push(20);
	stackInt.Push(30);
	stackInt.Push(40);
	stackInt.Push(50);
	size = stackInt.GetCount();
	for (int i = 0; i < size; ++i)
		cout << stackInt.Pop() << endl;

	cout << endl;

	CStack< double > stackDouble;
	stackDouble.Push(1.2);
	stackDouble.Push(1.3);
	stackDouble.Push(1.5);
	stackDouble.Push(1.9);
	stackDouble.Push(2.1);
	stackDouble.Push(3.2);
	stackDouble.Push(3.3);
	stackDouble.Push(15.3);
	stackDouble.Push(2.8);
	size = stackDouble.GetCount();
	for (int i = 0; i < size; ++i)
		cout << stackDouble.Pop() << endl;

	return 0;

}//	int main()
//=================================================