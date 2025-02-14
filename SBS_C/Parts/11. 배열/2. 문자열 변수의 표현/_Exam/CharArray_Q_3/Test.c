//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main()
{
	char szInput[50];
	printf("영단어를 입력하세요 : ");
	scanf("%s", szInput);

	int idx = 0;
	char max = szInput[0];
	while (szInput[idx] != 0)
	{
		printf("%c :  %d\n", szInput[idx], szInput[idx]);

		if (max < szInput[idx])
			max = szInput[idx];

		++idx;
	}
	
	printf("아스키 코드값이 가장 큰 문자는 %c\n", max);

	return 0;
}
//======================================================