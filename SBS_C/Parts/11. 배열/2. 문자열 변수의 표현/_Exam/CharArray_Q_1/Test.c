//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main(void)
{
	char str[50];
	int idx = 0;
	int length = 0;

	printf("문자열 입력 : ");
	scanf("%s", str);
	
	while (str[idx] != '\0')
		++idx;

	printf("\n");
	length = idx;
	printf("%s의 길이는 %d 입니다.\n\n", str, length);

	return 0;
}
//======================================================