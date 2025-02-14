//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main(void)
{
	int arr[] = { 1,2,3,4,5 };

	int length = sizeof( arr ) / sizeof( int );
	int* ptr = &arr[ length - 1 ];
	int sum = 0;
	while (length > 0)
	{
		sum += *(ptr--);
		//sum += *ptr--;
		--length;
	}
	printf("%d\n", sum);
	return 0;
}
