//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main(void)
{
	int inputNum = 0;
	printf("숫자를 입력하세요 : (단,  -1은 종료.)");
	scanf("%d", &inputNum);

	while (inputNum != -1)
	{
		int count = 1;
		while (count <= 9)
		{
			printf("%d x %d = %d\n", inputNum, count, inputNum * count);
			++count;

		}//	while (count <= 9)

		printf("숫자를 입력하세요 : (단,  -1은 종료.)");
		scanf("%d", &inputNum);

	}//	while (inputNum != -1)

	printf("수고하셨습니다!!^^\n");

	return 0;

}//	int main(void)
//======================================================