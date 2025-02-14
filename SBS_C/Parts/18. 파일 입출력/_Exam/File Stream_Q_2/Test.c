//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	Q - 2)	
			fread / fwrite 를 이용해 파일 복사 프로그램 작성.
*/
//======================================================
int main()
{
	FILE* pfSrc = fopen("src.bin", "rb");
	FILE* pfDst = fopen("dst.bin", "wb");

	if (pfSrc == NULL || pfDst == NULL)
	{
		puts("파일 열기 실패!!");
		return -1;
	}

	int readCount = 0;
	int readBuf[7] = { 0 };
	
	//*	방법 1)
	readCount = fread(readBuf, sizeof(int), 7, pfSrc);
	fwrite(readBuf, sizeof(int), 7, pfDst);
	//*/

	

	/*	방법 2)
	while (1)
	{
		//	메모리 읽어오기.
		readCount = fread(readBuf, sizeof(int), 7, pfSrc);

		//	읽어온 메모리가 항목 갯수보다 적은 경우..
		if (readCount < 7)
		{
			//	에러코드 검사.			
			int errCode = feof(pfSrc);
			//	0이 아닌 값 반환.
			//	-	파일 끝에 도달.
			//	-	읽기 완료.
			if (errCode != 0)
			{
				fwrite(readBuf, sizeof(int), readCount, pfDst);
				puts("파일 복사 완료");
				break;
			}
			else
				puts("파일 복사 실패!!!ㅠㅠ");

			break;

		}//	if (readCount < 7)

		fwrite(readBuf, sizeof(int), 7, pfDst);
	}
	//*/
	fclose(pfSrc);
	fclose(pfDst);

	return 0;
}
//*/
//======================================================