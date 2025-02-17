//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	2.	continue
*/
//======================================================
void main(void)
{	
	printf("input 3 Number : \n");
	int num1, num2, num3;
	scanf("%d %d %d", &num1, &num2, &num3);
	for (int num = 1; num <= 100; num++)
	{
		if ( num % num1 == 0 ||
			num % num2 == 0 ||
			num % num3 == 0)
			continue;
		
		printf("%d\n", num);
	}
}
//======================================================