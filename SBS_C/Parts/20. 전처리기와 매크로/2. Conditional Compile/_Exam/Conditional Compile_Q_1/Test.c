//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
#define MAX(a,b) ((a) > (b) ? (a) : (b))
void main()
{
	int num1, num2;
	printf("숫자 1 : ");
	scanf("%d", &num1);

	printf("숫자 2 : ");
	scanf("%d", &num2);

	int max = MAX(num1, num2);
	printf("%d이(가) 더 큰 수입니다. \n", max);
}
//======================================================