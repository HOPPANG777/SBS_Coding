//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <string.h>	//	문자열 관련 함수 헤더파일.
//======================================================
int main()
{
	const int LIMIT_CHAR_LENGTH = 10;
	
	int length = 0;

	do
	{
		char szTmp[50];

		printf("문자열을 입력하세요 : ");
		scanf("%s", szTmp);

		length = strlen(szTmp);

	}
	while (length < LIMIT_CHAR_LENGTH);

	printf("10 글자를 넘겼습니다!!\n");
	return 0;

}//	int main()
//======================================================//