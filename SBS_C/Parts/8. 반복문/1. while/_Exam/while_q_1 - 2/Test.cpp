//======================================================
#pragma warning (disable : 4996)

#include <stdio.h>
//======================================================
int main(void)
{
	int num = 0;

	printf("숫자를 입력하세요 : ");
	scanf("%d", &num);
	
	int count = 1;

	int res = 0;
	while (count <= num)
	{
		res += count;

		++count;

	}//	while (count <= 9)

	printf("\n1 ~ %d 까지의 합 : %d\n", num, res);

	return 0;
}
//======================================================