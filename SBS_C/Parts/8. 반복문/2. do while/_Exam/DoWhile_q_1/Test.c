//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main(void)
{
	int num = 0;
	int sum = 0;
	do
	{
		printf("%d + %d = %d\n", sum, num, sum + num);
		sum += num;
		num += 2;

	} while (num <= 100);	//	;으로 마무리!!
	printf("%d\n", sum);

	printf("\n=========================\n\n");
	/*
	num = 0;
	sum = 0;
	do
	{
		if (num % 2 == 0)
		{
			printf("%d + %d = %d\n", sum, num, sum + num);
			sum += num;
		}
		++num;

	} while (num <= 100);	//	;으로 마무리!!

	printf("%d\n", sum);
	//*/
	return 0;
}
//======================================================