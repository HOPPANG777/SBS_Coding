#include<iostream>
#include "FunctionOverload.h"

using namespace std;

int main()
{
	int nA = 10, nB = 20;
	char cA = 'a', cB = 'b';
	double dA = 1.2, dB = 1.3;
	cout << "===== before =====" << endl;
	cout << nA << " , " << nB << endl;
	cout << cA << " , " << cB << endl;
	cout << dA << " , " << dB << endl;

	Swap(&nA, &nB);
	Swap(&cA, &cB);
	Swap(&dA, &dB);

	cout << "===== after =====" << endl;
	cout << nA << " , " << nB << endl;
	cout << cA << " , " << cB << endl;
	cout << dA << " , " << dB << endl;

	return 0;
}