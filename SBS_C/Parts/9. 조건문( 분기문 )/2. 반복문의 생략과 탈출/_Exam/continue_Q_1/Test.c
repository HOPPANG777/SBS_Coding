//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
2.	continue
*/
//======================================================
int main(void)
{
	int num = 0;
	int count = 1;
	int sum = 0;

	printf("input number : ");
	scanf("%d", &num);

	while (count<=100)
	{
		if (count % num != 0)
		{
			++count;
			continue;
		}

		sum += count;
		++count;
	}

	printf("%d\n", sum);

	return 0;
}
//======================================================