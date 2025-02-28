//======================================================
//#pragma warning (disable : 4996)
//#include <stdio.h>
//	문자열 관련 함수 헤더파일.
//#include <string.h>
//#include <stdlib.h>
#include "stdafx.h"
//======================================================
/*
	------------
	1.	strlen..
	------------

	1.	원형..
	
		size_t strlen( const char* s )
	
		-	전달된 문자열의
			길이 반환..



	2.	특징..

		-	널문자는 길이에
			포함하지 않음..

		-	size_t 타입으로
			길이를 관리..

			-	typedef unsigned int size_t;
				-	unsigned int를 size_t로 대신함..

			-	보통 int 형으로 관리함..


		-	영문자..
			-	글자당 1바이트..

			한글 등 아시아권 문자..
			-	글자당 2바이트..
*/
//======================================================
/*
int main()
{
	char szTmp[50];

	printf("문자열을 입력하세요 : ");
	scanf("%s", szTmp);

	int length = strlen(szTmp);

	printf("%s의 길이는 %d 입니다.\n", szTmp, length);
	printf("szTmp의 길이는 %d 입니다.\n", sizeof(szTmp));

	return 0;
}
//*/
//======================================================
/*
	Quiz)
		알파벳 10 글자를 넘지 않는 동안
		계속 입력 받는 프로그램을 만듭니다.

		예)
			문자열을 입력하세요 : abcd
			문자열을 입력하세요 : abcdefg
			문자열을 입력하세요 : 0123456789!
			10 글자를 넘겼습니다!!

*/
//======================================================
/*
	---------------
	2.	strcpy
		/ strncpy..
	---------------

		1.	원형..

			char* strcpy(
				char* dest,
				const char* src );

				-	dest로 src의 문자열 복사..
				-	dest가 src의 길이보다
					작지 않도록 주의..
		


			char* strncpy(
				char * dest,
				const char * src,
				size_t n	);

				-	dest로 src의 문자열을
					[ n ]개의 길이만큼 복사..
				-	복사할때 널문자는
					포함하지 않음..
					-	경우에 따라
						배열끝에 널문자를
						수동으로 삽입해야 함..

*/
//======================================================
/*
int main()
{
	char szOrigin[ 20 ] = "1234567890";
	char szTmp1[ 20 ];
	char szTmp2[ 5 ];

	// strcpy
	char *pRes = strcpy(szTmp1, szOrigin);
	printf("%s\n", szTmp1);
	printf("주소 값 비교..\n");
	printf("%p   %p\n\n", pRes, szTmp1);

	// strncpy 1
	pRes = strncpy(szTmp2, szOrigin, sizeof(szTmp2));
	printf("%s\n", szTmp2);
	printf("주소 값 비교..\n");
	printf("%p   %p\n\n", pRes, szTmp2);

	// strncpy 2
	pRes = strncpy(szTmp2, szOrigin, sizeof(szTmp2)-1);
	szTmp2[sizeof(szTmp2) - 1] = 0;
	printf("%s\n", szTmp2);
	printf("주소 값 비교..\n");
	printf("%p   %p\n\n", pRes, szTmp2);

	return 0;
}
//*/
//======================================================
/*
	---------------
	3.	strcat
		/ strncat..
	---------------

		1.	원형..

			char* strcat(
				char * dest,
				const char * src );

				-	dest에 src를 덧붙힘..


			char* strncat(
				char * dest,
				const char * src,
				size_t n );

				-	dest에 src를
					[ n ]개의 길이만큼
					덧붙힘..
				-	strncpy와는 달리
					문자열 끝에 자동으로
					널문자 삽입..
				-	덧붙힘이 시작되는 위치는
					널문자가 저장된 위치..
*/
//======================================================
/*
int main()
{
	char szTmp1[20] = "First~";
	char szTmp2[20] = "Second!!";

	char szTmp3[20] = "strncat : ";
	char szTmp4[20] = "1234567890";

	//	strcat
	strcat(szTmp1, szTmp2);
	printf("%s\n", szTmp1);

	//	strncat
	strncat(szTmp3, szTmp4, 1);
	printf("%s\n", szTmp3);

	return 0;
}
//*/
//======================================================
/*
	---------------
	4.	strcmp
		/ strncmp..
	---------------

		1.	실수..( fault!! )

			int main()
			{
				char str1[] = "My String";

				char str2[] = "My String";

				if( str1 == str2 )
				->	[ 배열의 이름 ]
					==	배열이 할당된
						[ 메모리의 주소값 ]을 관리하는
						[ 상수 ]..
						-	추후 [ 포인터 ]에서 설명..

					....

				else

					....

				return;

			}


		1.	원형..

			#include <string.h>

			int strcmp(
				const char * s1,
				const char *s2 );
			int strncmp(
				const char * s1,
				const char *s2,
				size_t n );

				-	n의 길이만큼만 문자 비교.

				-	두 문자열의 내용이 같다..
					-	0 반환..
					다르다
					-	0이 아닌 값 반환..

				===============================
					비교..		|	반환 값..
				===============================
					s1 > s2  	|	양수 반환.
					s1 < s2 	|	음수 반환.
					s1 == s2	|	0 반환.
				===============================

				-	문자열의 크고 작음은
					아스키 코드값을 기준으로 함..

*/
//======================================================
/*
int main()
{
	char szTmp1[30];
	char szTmp2[30];

	printf("첫번째 문자열 입력 : ");
	scanf("%s", szTmp1);

	printf("두번째 문자열 입력 : ");
	scanf("%s", szTmp2);

	printf("--- szTmp1 == szTmp2 ---\n");
	printf("szTmp1 : %p // szTmp2 : %p\n", szTmp1, szTmp2);
	if( szTmp1 == szTmp2 )
		printf("동일한 주소!!\n");
	else
		printf("다른 주소!!\n");

	printf("--- !strcmp(szTmp1, szTmp2) ---\n");
	if (!strcmp(szTmp1, szTmp2))
		printf("동일한 문자열!!\n");
	else
	{
		printf("다른 문자열!!\n");

		if( !strncmp(szTmp1, szTmp2, 3) )
			printf("하지만 앞 3글자는 동일!!\n");
	}

	return 0;
}
//*/
//======================================================
/*
	Quiz)
		글자를 입력하세요 ( 종료 : finish ) : seoul

		얼만큼 복사할까요 ? [ 1. 전부      2. 일부 ]1

		seoul

		글자를 입력하세요 ( 종료 : finish ) : korea

		얼만큼 복사할까요 ? [ 1. 전부      2. 일부 ]2

		몇글자만 복사할까요 ? 2

		ko

		글자를 입력하세요 ( 종료 : finish ) : finish

		끝!!!
*/
//======================================================
/*
	-----------
	5.	그 외..
	-----------

		1.	원형..

			#include <stdlib.h>

			int atoi( const char * str );
			-	문자열의 내용을 int형으로 반환.

			long atol( const char * str );
			-	문자열의 내용을 long형으로 반환.

			double atof( const char * str );
			-	문자열의 내용을 double형으로 반환.

			**	중간에 문자가 섞여 있으면
				문자앞의 숫자 까지만
				숫자 데이터로 처리..

			**	문자로 시작하면
				0으로 처리..
*/
//======================================================
/*
#include <stdlib.h>

int main()
{
	char szInt[20];
	char szDouble[20];

	printf("정수 입력 : ");
	scanf("%s", szInt);
	printf("%d\n", atoi(szInt));
	
	printf("실수 입력 : ");
	scanf("%s", szDouble);
	printf("%f\n", atof(szDouble));

	return 0;
}
//*/
//======================================================
/*
	Quiz)

		적당한 길이의 문자열을 입력받아
		그 안에 존재하는 숫자의 총합을
		계산하는 프로그램 작성...

		예)	ad8a9aadf0a12

			-> 8 + 9 + 0 + 1 + 2 = 20

		힌트)	아스키코드표 참고.
				https://blog.naver.com/kyuhgmi/220073551241
*/
//======================================================//