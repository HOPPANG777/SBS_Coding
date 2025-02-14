//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	포인터 배열

		-	포인터 변수로 이뤄져서
			주소 값의 저장이 가능한 배열..

			예)
				int *pArr1[20];		->	길이가 20인
										int형 포인터 배열 pArr1.

				double *pArr2[30];	->	길이가 30인
										double형 포인터 배열 pArr2.			
*/
//======================================================
/*
int main(void)
{
	int num1 = 10, num2 = 20, num3 = 30;
	int* pArr[3] = { &num1, &num2, &num3 };
	printf("-- *pArr[n] -------------------\n");
	
	printf("%d\n", *pArr[0]);	//	*pArr[0] == *(&num1) == num1
	//printf("%d\n", **pArr);
	
	printf("%d\n", **(pArr + 1));
	//printf("%d\n", *pArr[1]);
		
	printf("%d\n", **(pArr + 2));
	//printf("%d\n", *pArr[2]);
	
	printf("-- pArr[x][y] -------------------\n");
	printf("%d\n", pArr[0][0]);	//	pArr[0][0] --> *pArr[0] --> **pArr
	printf("%d\n", pArr[1][0]);
	printf("%d\n", pArr[2][0]);
	
	printf("-- *pTr & pTr[n] -------------------\n");
	int* pTr = &num1;
	printf("%d\n", *pTr);
	printf("%d\n", pTr[0]);

	return 0;
}
//*/
//======================================================
/*
	2.	문자열 배열.

		-	문자열의 주소값을
			저장할 수 있는 배열..

		-	사실상 char형 포인터 배열.
			예)
				char * pStrArr[3];	//	길이가 3인
										char형 포인터 배열.
	
		-	""로 표현되는 문자열은
			메모리 공간에 저장된 후
			주소값이 반환됨..
*/
//======================================================
/*
int main(void)
{
	char *pStrArr[3] = {"Simple", "String", "Array"};
	printf("%s\n", pStrArr[0]);
	printf("%s\n", pStrArr[1]);
	printf("%s\n", pStrArr[2]);

	return 0;
}
//*/
//======================================================
/*
	3.	배열 포인터.
		[ 참고 : https://blockdmask.tistory.com/56 ]

		-	배열을 가리키는
			"하나의 포인터".
		-	특정 사이즈의 배열만
			가리킬 수 있는
			하나의 포인터..

		-	선언 방식.
			-	T	(*pTr)[N];
				예)	
					char (*pArr)[3];
					-	[ char 타입의 인덱스를 3개 가지고 있는 배열 ]을 가리키는 포인터.
											( = 크기가 3인 )

					char * pArr[3];
					-	길이가 3인 char형 포인터 배열.

*/
//======================================================
/*
int main(void)
{
	//	배열 포인터..
	printf("===============================\n");
	printf("-- 배열 포인터 --\n");
	printf("===============================\n");
	char(*pArr)[3] = { 0, };					//	크기가 3인 배열을 가리키는 포인터.
	printf("(*pArr)[3]의 크기 : %d\n",  sizeof(pArr));

	printf("-----------------------\n");
	char tmp1[3] = {'s', 'k', 'y'};
	char tmp2[3] = { 't', 'r', '\0' };			//	문자열의 끝을 알리는 '\0' 추가..
	char tmp3[5] = { 's', 't', 'u', 'd', 'y'};	//	배열의 사이즈가 다름..
		
	printf("tmp1[3]의 주소 : %p\n", tmp1);
	printf("tmp2[3]의 주소 : %p\n", tmp2);
	printf("tmp3[5]의 주소 : %p\n", tmp3);
	printf("\n");

	printf("-----------------------\n");
	pArr = tmp1;
	printf("pArr( tmp1 )의 주소 : %p\t\t 문자열 : ", pArr);
	int size = (int)sizeof(*pArr);
	for (int cur = 0; cur < size; ++cur)
		printf("%c", (*pArr)[cur]);
	printf("\n");

	printf("-----------------------\n");
	pArr = tmp2;
	printf("pArr( tmp2 )의 주소 : %p\t\t 문자열 : ", pArr);
	size = (int)sizeof(*pArr);
	for (int cur = 0; cur < size; ++cur)
		printf("%c", (*pArr)[cur]);
	printf("\n");

	printf("-----------------------\n");
	pArr = tmp3;
	printf("pArr( tmp3 )의 주소 : %p\t\t 문자열 : ", pArr);
	size = (int)sizeof(*pArr);
	for (int cur = 0; cur < size; ++cur)
		printf("%c", (*pArr)[cur]);
	printf("\n");

	printf("===============================\n");
	printf("-- 포인터 배열 --\n");
	printf("===============================\n");
	//	포인터 배열...
	char* pArr2[3] = { 0, };
	printf("pArr2[3]의 크기 : %d\n", sizeof(pArr2));
	pArr2[0] = tmp1;
	printf("pArr의 주소 : %p\t\t 문자열 : ", pArr2[0]);
	int length = (int)sizeof(pArr2[0]);
	for (int cur = 0; cur < length; ++cur)
		printf("%c", pArr2[0][cur]);
	printf("\n");

	return 0;
}
//*/
//======================================================//