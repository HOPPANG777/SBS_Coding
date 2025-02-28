//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main(void)
{
	int filterNum = 0;

	printf("필터링 할 배수 : ");
	scanf("%d", &filterNum);
	
	int num = 0;
	printf("숫자를 입력하세요 : ");
	scanf("%d", &num);

	while (num % filterNum != 0)
	{
		printf("숫자를 입력하세요 : ");
		scanf("%d", &num);
	}

	printf("안녕~\n ");

	return 0;

}//	int main(void)
//======================================================