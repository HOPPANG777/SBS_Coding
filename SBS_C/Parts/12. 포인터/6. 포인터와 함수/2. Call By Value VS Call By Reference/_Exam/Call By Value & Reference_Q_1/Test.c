//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
//	-	함수 오버로딩은 c++에 도입 
/*
void SwapPtr(int n1, int n2)
{
	int tmp = n1;
	n1 = n2;
	n2 = tmp;
}
//*/
//----------------------------------
//	n1과 n2를 바꾸는 함수.
void SwapPtr(int* pn1, int* pn2)
{
	int tmp = *pn1;
	*pn1 = *pn2;
	*pn2 = tmp;
}
//----------------------------------
int main(void)
{
	int n1 = 10;
	int n2 = 20;
	printf("n1 = %d,   n2 = %d\n", n1, n2);

	SwapPtr(&n1, &n2);

	printf("n1 = %d,   n2 = %d\n", n1, n2);

	return 0;	
}
//======================================================