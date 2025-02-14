//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main(void)
{
	int num;
	printf("숫자를 입력하세요 : ");
	scanf("%d", &num);

	int res = num * 0.1f;

	switch (res)
	{
	case 0:
		printf("0 이상 10 미만\n");
		break;

	case 1:
		printf("10 이상 20 미만\n");
		break;

	case 2:
		printf("20 이상 30 미만\n");
		break;

	default :
		printf("음수 또는 30 이상\n");
		break;
	}

	return 0;
}