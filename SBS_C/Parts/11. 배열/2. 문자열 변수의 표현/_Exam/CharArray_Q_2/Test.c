//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main(void)
{
	char str[50];
	int idx = 0;
	
	printf("문자열 입력 : ");
	scanf("%s", str);
	printf("\n--- before -------\n");
	printf("%s\n", str);
	while (str[idx] != '\0')
	{
		if ('A' <= str[idx] && str[idx] <= 'Z')
			str[idx] += 32;

		else if ('a' <= str[idx] && str[idx] <= 'z')
			str[idx] -= 32;

		++idx;
	}
	printf("\n--- after -------\n");
	printf("->  %s\n", str);

	return 0;
}
//======================================================