//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main(void)
{
	int inputNumSmall;
	int inputNumBig;
	int total = 0;

	printf("작은수를 입력하세요 : ");
	scanf("%d", &inputNumSmall);
	printf("큰 수를 입력하세요 : ");
	scanf("%d", &inputNumBig);

	for (int cur = inputNumSmall; cur <= inputNumBig; ++cur)
		total += cur;

	printf("%d ~ %d 까지의 합 : %d\n", inputNumSmall, inputNumBig, total);

	return 0;
}
//======================================================