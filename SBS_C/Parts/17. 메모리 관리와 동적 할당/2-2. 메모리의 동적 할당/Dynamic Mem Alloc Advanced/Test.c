//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include <stdlib.h>
//======================================================
/*
	1 - 1.	[ malloc ]의 반환형은 [ void* ]

		-	void형 포인터..

			-	형(Type)이 존재하지 않는 포인터..

				예) void* ptr;


			-	장점..

				ㄴ	어떠한 변수의 주소값이든 관리 가능..

					ㄴ	함수의 주소 값도 가능..


			-	단점..

				ㄴ	가리키는 대상의 타입에 대한
					정보가 없으므로...

					ㄴ	포인터 연산 불가..

					ㄴ	값의 변경이나 참조 불가..



			-	주로 주소값을 일단 저장한 뒤
				나중에 포인터 타입을 결정하는
				용도로 사용됨..
*/
//------------------------------------------------------
/*
void SimpleFunc() { printf("Simple Func!!\n"); }

int main()
{
	int num = 20;

	void* ptr;

	ptr = &num;
	printf("ptr = %p\n", ptr);

	//	단점 1>
	//	++ptr;

	//	단점 2>
	//	*ptr = 30;

	ptr = SimpleFunc;
	printf("ptr = %p\n", ptr);

	return 0;
}
//*/
//---------------------------
/*	
	1 - 2.	[ malloc ]의 반환형은
			[ void* ]..

		-	void* 타입인 이유..

			ㄴ	원하는 만큼 메모리 공간을 할당하고
				할당된 메모리의 주소를 반환하면
				프로그래머가 직접 포인터형의
				변환을 통해서 어떻게 사용할지 결정..
*/
//---------------------------
/*
int main()
{
	int* ptr1 = (int*)malloc(sizeof(int));
	int* ptr2 = (int*)malloc(sizeof(int) * 7);

	*ptr1 = 20;

	for (int i = 0; i < 7; ++i)
		ptr2[i] = i + 1;

	printf("*ptr1 = %d\n", *ptr1);

	printf("*ptr2 \n");
	for (int i = 0; i < 7; ++i)
		printf("%d ", ptr2[i]);
	printf("\n");

	free(ptr1);
	free(ptr2);

	return 0;
}
//*/
//---------------------------
/*
	2.	그 밖에...

		-	calloc

			-	원형

				void* calloc( size_t elementCount, size_t elementSize );

				-	elementCount
					-	할당할 블록의 갯수..

				-	elementSize
					-	블록 하나당 바이트 크기..

			-	malloc( 40 ) == calloc( 10, 4 )

			-	[ malloc ] vs [ calloc ]..

				-	메모리 공간의 모든 비트를 0으로 초기화.
					-	malloc의 경우
						초기화 하지 않음..
						-	쓰레기 값으로 채워짐..

		-	realloc
            [ 참고 : https://www.weezzle.net/1652 ]

			-	원형

				void* realloc( void *ptr, size_t size );

				-	ptr
					-	확장하고자 하는
						힙 메모리의 주소..

				-	size
					-	확장하고자 하는
						메모리의 전체 크기..

			-	예)

				int *pArr = (int*)malloc(sizeof( int ) * 3 );

				.......

				pArr = (int * )realloc(pArr, sizeof( int ) * 5 );

			-	[ malloc ]과 [ realloc ]의
				반환값..

				-	같은 경우..
					-	malloc로 할당한 메모리 공간뒤에
						확장할 영역이 넉넉한 경우..

				-	다른 경우..
					-	넉넉하지 않은 경우,
						새로 요구하는 크기의
						메모리 공간을 별도로 할당한뒤
						이전 데이터의 값을 복사..

*/
//---------------------------
/*
	Quiz)
		
		문제 1),2)의 상황을 malloc와 free를 이용해서
		해결한 코드입니다..
		
		...로 된 1), 2)를 작성하여
		프로그램을 완성해보세요..

		//---------------------------
		char* GetUserName()
		{
			1) .........
		}
		//---------------------------
		int main()
		{
			char* pszName1 = GetUserName();
			printf("이름 : %s\n", pszName1);

			char* pszName2 = GetUserName();
			printf("이름 : %s\n", pszName2);
		
			printf("=======================\n");

			printf("이름 : %s\n", pszName1);
			printf("이름 : %s\n", pszName2);

			2) .........

			return 0;

		}

*/
//---------------------------