//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	break
*/
//======================================================
int main(void)
{
	int num = 0;
	printf("input number : ");
	scanf("%d", &num);

	int count = 1;
	while (1)
	{
		if (count > num)
			break;

		printf("%d x %d = %d\n", num, count, num*count);
		++count;
	}

	return 0;
}
//======================================================