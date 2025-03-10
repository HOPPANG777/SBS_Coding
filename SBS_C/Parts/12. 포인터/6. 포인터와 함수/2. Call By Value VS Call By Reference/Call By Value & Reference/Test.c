//======================================================
#pragma warning (disable : 4996)
#include "stdafx.h"
//======================================================
/*
	-----------
	1.	Call By
		Value..
	-----------

		-	함수 호출시 매개 변수로
			[ 값 ]을 전달하는 호출 방식..

			ㄴ	값 전달 방식..



	---------------
	2.	Call By
		Reference..
	---------------

		-	함수 호출시 매개 변수로
			메모리 접근에 사용되는
			[ 주소값 ]을 전달하는 호출 방식..

			ㄴ	주소 전달 방식..
*/

//* 소스 분석 후 고찰하기...
//------------------
//	목적..
//	ㄴ	n1과 n2를 통해
//		외부에서 전달된 데이터를
//		바꾸기..
void Swap(int* n1, int* n2)
{
	int tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;

	printf("a = %d,   b = %d\n", *n1, *n2);
}

void Calculate(int num1, int num2, int* pSum, int* pSub, int* pMulti, float* pDiv)
{
	*pSum = num1 + num2;
	*pSub = num1 - num2;
	*pMulti = num1 * num2;
	*pDiv = (float)num1 / num2;
}

//======================================================
/*
	quiz 3)

		두 개의 숫자를 입력한 뒤
		두 숫자의 4칙 연산 결과를
		한 번에 받아오는 함수를
		포인터를 이용하여 만듭니다..

		예)
			void Calculate(
				int num1,
				int num2,
				int* pSum,
				int* pSub,
				int* pMulti,
				float* pDiv)
*/
//======================================================

int main(void)
{
	/*
	int a = 10;
	int b = 20;
	printf("a = %d,   b = %d\n", a, b);

	int* aPtr = &a;
	int* bPtr = &b;

	Swap(aPtr, bPtr);

	printf("a = %d,   b = %d\n", a, b);
	*/

	int num1 = 0, num2 = 0;
	int sum = 0, sub = 0, multi = 0;
	float div = 0;

	printf("숫자 2개를 입력해주세요. (예: 10 20) : ");
	scanf("%d %d", &num1, &num2);

	printf("\n");

	Calculate(num1, num2, &sum, &sub, &multi, &div);

	printf("진행하시려면 Enter를 입력해주세요.\n\n");

	system("pause");

	printf("\n더하기: %d, 빼기: %d, 곱하기: %d, 나누기: %f", sum, sub, multi, div);

	printf("\n\n");

	printf("프로그램을 종료합니다.\n\n");

	system("pause");

	return 0;	
}
//*/

//------------------
//	Q 1>
// 
//		1)	다음 예제의 문제점은?
//				- Swap 내부에서만 값이 바뀌고 출력해봤자 main에 있는 a,b의 값이 바뀌는 것이 아니라 복사된 값을 바꾸고 출력했기 때문
//		
//		2)	바르게 작동시키도록 하려면?
//				
//		
//------------------


//======================================================
/*
	------------------
	scanf의 원리 이해..
	------------------

		예)
			int num;
			scanf("%d", &num);

			-	scanf는 변수 num의 주소로
				접근하여 값을 채워넣음..



			char szTmp[30];
			scanf("%s", szTmp);			

			char c;
			scanf("%c", &c);
		
			-	scanf("%s", &szTmp);	( X )

			-	szTmp 자체가 주소값..
				
				ㄴ	배열의 이름..
					== 배열의 첫 요소의 주소..

*/
//======================================================
/*
	quiz 2) 과제

		세 변수에 값을 바꾸는 함수를 만들자.

		.......

		scanf("%d %d %d", &n1, &n2, &n3);

		printf("\n--- before\n");
		printf("%d,  %d,  %d\n", n1, n2, n3);

		Swap(&n1, &n2, &n3);

		printf("\n--- after\n");
		printf("%d,  %d,  %d\n", n1, n2, n3);
		
		.......
				
		 n1	->	n2
		 n2	->	n3
		 n3	->	n1
*/
//======================================================
/*
	quiz 3)

		두 개의 숫자를 입력한 뒤
		두 숫자의 4칙 연산 결과를
		한 번에 받아오는 함수를
		포인터를 이용하여 만듭니다..

		예)
			void Calculate(
				int num1,
				int num2,
				int* pSum,
				int* pSub,
				int* pMulti,
				float* pDiv)
*/
//======================================================