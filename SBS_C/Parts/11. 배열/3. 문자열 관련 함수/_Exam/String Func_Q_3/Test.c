//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <string.h>	//	문자열 관련 함수 헤더파일.
//======================================================
int CharToNumber(char cWord) { return cWord - '0'; }

int main()
{
	//-----------------------------------
	//	문자열 입력..
	char szWords[30] = "";
	printf("숫자가 포함된 문자를 입력하세요 : " );
	scanf("%s", szWords);

	//-----------------------------------
	//	숫자 형식의 문자 필터링 및 합계 연산..
	int len = strlen(szWords);
	int sum = 0;
	char szOnlyNumbers[100] = "";
	for (int cur = 0; cur < len; ++cur)
	{
		if ('0' <= szWords[cur] && szWords[cur] <= '9')
		{
			strncat(szOnlyNumbers, &szWords[cur], 1);
			sum += CharToNumber(szWords[cur]);
			strcat(szOnlyNumbers, " ");

			//	szOnlyNumbers -> "1 3 2 4 "
		}
	}
	printf("%s의 숫자들 : %s\n", szWords, szOnlyNumbers);

	//-----------------------------------
	//	형식 정리 및 출력..
	int idx = 0;
	int resLen = strlen(szOnlyNumbers);
	while (szOnlyNumbers[idx] != 0)
	{
		if (szOnlyNumbers[idx] == ' ' &&
			 idx < (resLen - 1) )
			szOnlyNumbers[idx] = '+';

		++idx;
	}
	//	szOnlyNumbers -> "1+3+2+4 "
	printf("%s= %d\n", szOnlyNumbers,sum);
	//	"1+3+2+4 = 10"

	return 0;
}
//======================================================//