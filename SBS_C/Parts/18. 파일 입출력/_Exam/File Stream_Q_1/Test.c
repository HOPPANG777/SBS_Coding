//======================================================
/*
    Q - 1)

        위 예제와 동일한 작업을 fgets와 fputs를 이용하여 작성한다.
*/
//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main()
{
	FILE* pfSrc = fopen("Test.txt", "rt");
	FILE* pfDst = fopen("TestCopy.txt", "wt");

	int ch;

	puts("파일 복사 시작!!");
	if (pfSrc == NULL || pfDst == NULL)
	{
		puts("파일 오픈 실패!!");

		return -1;
	}
	char *pszTmp;
	char szTmp[128] = { 0, };
	while (pszTmp = fgets(szTmp, 128, pfSrc))
		fputs(pszTmp, pfDst);

	if (feof(pfSrc) != 0)
		puts("파일 복사 완료!!");
	else
		puts("파일 복사 실패!!");

	puts("프로그램 종료!!");

	fclose(pfSrc);
	fclose(pfDst);

	return 0;
}
//*/
//======================================================










































/*	파일 복사
int main()
{
	FILE* pfSrc = fopen("Test.txt", "rt");
	FILE* pfDst = fopen("TestCopy.txt", "wt");

	char str[30];

	puts("파일 복사 시작!!");
	if (pfSrc == NULL || pfDst == NULL)
	{
		puts("파일 오픈 실패!!");
		return -1;
	}

	while ((fgets( str, sizeof(str), pfSrc)) != NULL)
		fputs(str, pfDst);

	if (feof(pfSrc) != 0)
		puts("파일 복사 완료!!");
	else
		puts("파일 복사 실패!!");

	puts("프로그램 종료!!");

	fclose(pfSrc);
	fclose(pfDst);

	return 0;
}
//*/