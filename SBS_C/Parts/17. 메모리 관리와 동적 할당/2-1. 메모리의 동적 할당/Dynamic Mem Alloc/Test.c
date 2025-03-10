//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <math.h>
//======================================================
/*
	-----------------------------
	1 - 1.	전역변수와 지역변수로
			해결이 되지 않는 상황..
	-----------------------------

		-	지역변수, 전역변수의 특성..

		-	10. 함수와 변수..

			ㄴ	2. 변수의 생명과 접근범위 참고..
*/
//======================================================
//	문제 1)
/*
char* ReadUserName()
{
	char name[30];
	printf("이름 ? ");
	scanf("%s", name);

	return name;
}
int main()
{
	char *pszName1;
	char *pszName2;

	pszName1 = ReadUserName();
	printf("이름 : %s\n", pszName1);

	pszName2 = ReadUserName();
	printf("이름 : %s\n", pszName2);
	
	return 0;
}
//*/
//---------------------------
//	문제 2)
/*
//	전역변수..
char g_szName[30];

char * ReadUserName()
{
	//	정적 지역 변수..
	//static char g_szName[30];
	printf("이름 ? ");
	scanf("%s", g_szName);

	return g_szName;
}

int main()
{
	char *pszName1;
	char *pszName2;

	pszName1 = ReadUserName();
	printf("이름 : %s\n", pszName1);

	pszName2 = ReadUserName();
	printf("이름 : %s\n", pszName2);
	
	printf("pszName1 : %s\n", pszName1);
	printf("pszName2 : %s\n", pszName2);	

	return 0;
}

//*/
//======================================================
/*
	---------------
	1 - 2.	해결책..
	---------------

		-	생성과 소멸의 시기가
			지역변수나 전역변수와
			다른 유형의 변수가 필요..

			ㄴ	함수 호출시 매번 할당 되거나
				( 지역변수 )
				할당 후 함수가 종료되어도
				메모리가 유지되는 변수..
				( 전역변수 )

				ㄴ	C언어에서는 이를 위해
					[ malloc ] 와 [ free ] 를 제공..
*/
//======================================================
/*
	-------------------
	2.	malloc & free..
	-------------------

		-	원형..

			-	#include <stdlib.h>

				1)	void* malloc( size_t size );

					ㄴ	힙 영역에 메모리 공간 할당..

					ㄴ	성공..
						ㄴ	할당된 메모리 공간의
							주소값 반환..

						실패..					
						ㄴ	NULL 반환..


				2)	void free( void * ptr );

					ㄴ	힙 영역에 할당된
						메모리 공간을 해제..



		-	힙 영역..

			ㄴ	[ malloc ] 함수로 할당된 메모리 공간은
				프로그래머가 [ free ]로 직접 해제하지 않으면
				할당된 상태로 계속 남아있음..

				ㄴ	프로그래머가 관리하는 메모리 공간..

*/
//======================================================
#include <stdlib.h>
int main()
{
	//	[ 힙 영역 ]에 4바이트의 메모리 공간을
	//	할당한 후 첫번째 바이트의 주소를 반환..
	void* ptr1 = malloc(4);

	void* ptr2 = malloc(10);


	//	ptr1이 가리키는
	//	메모리 공간이 소멸..
	free(ptr1);
	free(ptr2);

	return 0;
}
//======================================================