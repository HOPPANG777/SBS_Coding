//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main(void)
{
	int num = 0;
	int sum = 0;

	//*	规过 1)
	do
	{
		printf("%d + %d = %d\n", sum, num, sum + num);
		sum += num;
		num += 2;

	} while (num <= 100);	//	;栏肺 付公府!!
	printf("%d\n", sum);

	printf("\n=========================\n\n");
	//*/


	/*	规过 2)
	do
	{		
		sum += num % 2 == 0 ? num : 0;
		num++;

	} while (num <= 100);	//	;栏肺 付公府!!
	printf("%d\n", sum);
	
	printf("\n=========================\n\n");
	//*/

	

	/*	规过 3)
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

	} while (num <= 100);	//	;栏肺 付公府!!

	printf("%d\n", sum);
	printf("\n=========================\n\n");
	//*/
	return 0;
}
//======================================================