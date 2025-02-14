//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <string.h>	//	문자열 관련 함수 헤더파일.
//======================================================
int main()
{
	printf("글자를 입력하세요 ( 종료 : finish ) : ");
	char szSource[128] = { 0, };
	scanf("%s", szSource);

	while (strcmp(szSource, "finish") != 0)
	{
		printf("얼만큼 복사할까요 ? [ 1. 전부      2. 일부 ]");
		int select = 0;
		scanf("%d", &select);

		char szClones[128] = { 0, };
		switch (select)
		{
		case 1:
			strcpy(szClones, szSource);
			break;

		case 2:
			printf("몇글자만 복사할까요 ? ");
			int length;
			scanf("%d", &length);
			strncpy(szClones, szSource, length);
			break;

		default:
			printf("잘못 입력했습니다!!\n");
			break;
		}

		printf("%s\n", szClones);

		printf("글자를 입력하세요 ( 종료 : finish ) : ");
		scanf("%s", szSource);

	}//	while (strcmp(szSource, "finish") != 0)
	
	printf("끝!!!\n");

	return 0;

}//	int main()
//======================================================//