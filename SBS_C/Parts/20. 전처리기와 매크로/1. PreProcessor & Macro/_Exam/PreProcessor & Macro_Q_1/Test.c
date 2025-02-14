//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
#define SQUARE(X) ((X)*(X))

int main()
{
	int num = 30;

	printf("넓이 : %d\n", SQUARE(num));
	printf("넓이 : %d\n", SQUARE(-10));
	printf("넓이 : %f\n", SQUARE(5.5));

	//	예상하지 못한 결과 1)
	printf("넓이 : %d\n", SQUARE(2+5));
	
	//	예상하지 못한 결과 2)
	int res = 120 / SQUARE(2);
	printf("res = %d\n", res);

	return 0;
}