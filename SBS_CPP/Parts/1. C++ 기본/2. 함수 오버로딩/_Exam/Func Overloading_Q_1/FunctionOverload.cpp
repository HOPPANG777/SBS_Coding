#include "FunctionOverload.h"

void Swap(int* pTmp1, int* pTmp2)
{
	int tmp = *pTmp1;
	*pTmp1 = *pTmp2;
	*pTmp2 = tmp;
}

void Swap(char* pTmp1, char* pTmp2)
{
	char tmp = *pTmp1;
	*pTmp1 = *pTmp2;
	*pTmp2 = tmp;
}

void Swap(double* pTmp1, double* pTmp2)
{
	double tmp = *pTmp1;
	*pTmp1 = *pTmp2;
	*pTmp2 = tmp;
}
