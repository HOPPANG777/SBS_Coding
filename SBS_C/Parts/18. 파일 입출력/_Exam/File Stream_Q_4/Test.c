//======================================================
/*
	Q - 4)	fseek 과 ftell 함수를 이용하여 파일의 크기를 구하는 프로그램 작성.
*/
//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
int main()
{
	//	파일 생성.
	FILE *pFile = fopen("FTellTest.txt", "wt");
	if (pFile == NULL)
	{
		puts("파일 열기 실패");
		return -1;
	}

	fputs("1234-", pFile);
	fclose(pFile);

	//	파일 열기.
	pFile = fopen("FTellTest.txt", "rt");
	
	fseek(pFile, 0, SEEK_END);
	int size = ftell(pFile);

	printf("%s 의 크기는 %d\n", "FTellTest.txt", size);
	fclose(pFile);

	return 0;
}