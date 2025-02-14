//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
void Calculate(
	int num1,
	int num2,
	int* pSum,
	int* pSub,
	int* pMulti,
	float* pDiv)
{
	*pSum = num1 + num2;
	*pSub = num1 - num2;
	*pMulti = num1 * num2;
	*pDiv = (float)num1 / num2;

}//	void Calculate(int num1, int num2, int* pSum, int* pSub, int* pMulti, float* pDiv)
//----------------------------------
int main(void)
{
	int n1;
	int n2;

	int sum, sub, multi;
	float div;

	printf("첫 번째 숫자 입력 : ");
	scanf("%d", &n1);
	printf("두 번째 숫자 입력 : ");
	scanf("%d", &n2);

	Calculate(n1, n2, &sum, &sub, &multi, &div);

	printf("\n== 결과 ==\n");
	printf("합 : %d\n", sum);
	printf("차 : %d\n", sub);
	printf("곱 : %d\n", multi);
	printf("몫 : %f\n\n", div);

	return 0;	
}
//======================================================