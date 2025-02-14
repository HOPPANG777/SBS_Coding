//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
//---------------------
int GetMinimum(int a, int b, int c)
{
	if (a < b)
	{
		if (a < c)
			return a;
		else
			return c;
	}
	else if (b < c)
		return b;
	else 
		return c;
}
//---------------------
int GetMaximum(int a, int b, int c)
{
	if (a > b)
	{
		if (a > c)
			return a;
		else
			return c;
	}
	else if (b > c)
		return b;
	else
		return c;
}
//---------------------
int main(void)
{
	printf("3개의 숫자를 입력하세요 \n");

	int a, b, c;

	scanf("%d %d %d", &a, &b, &c);

	int min, max;

	min = GetMinimum(a, b, c);
	max = GetMaximum(a, b, c);

	printf("가장 작은 수 : %d\n", min);
	printf("가장 큰 수 : %d\n", max);

	return 0;
}
//---------------------