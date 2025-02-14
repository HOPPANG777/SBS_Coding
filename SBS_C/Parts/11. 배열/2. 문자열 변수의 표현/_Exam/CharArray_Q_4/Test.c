//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main()
{
	char szInput[50];
	printf("영단어를 입력하세요 : ");
	scanf("%s", szInput);
	//scanf("%[^\n]", szInput);
	
	//[ 참고 : https://kldp.org/node/72882 ]
	int idx = 0;	
	while (szInput[idx] != 0)
		++idx;

	int length = idx;

	int wordCount = 1;
	for (idx = 0; idx < length; ++idx)
	{
		for (int curWord = 0; curWord < wordCount; ++curWord)
			printf("%c", szInput[curWord]);

		wordCount++;

		printf("\n");
	}

	return 0;
}
//======================================================