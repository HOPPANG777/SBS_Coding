//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
#define ADD 1
#define SUB 2
#define MULT 3
#define DIVID 4
*/
int main(void)
{
	const int ADD = 1;
	const int SUB = 2;
	const int MULT = 3;
	const int DIVID = 4;

	int select;
	printf("1. 덧셈   2. 뺄셈   3. 곱셈  4. 나눗셈\n");
	printf("연산방식을 선택하세요 : ");
	scanf("%d", &select);

	printf("두개의 정수를 입력하세요 :");
	int a, b;
	scanf("%d %d", &a, &b);

	if (select == ADD)
		printf("결과 : %d + %d = %d\n", a, b, a + b);
	else if (select == SUB)
		printf("결과 : %d - %d = %d\n", a, b, a - b);
	else if (select == MULT)
		printf("결과 : %d x %d = %d\n", a, b, a * b);
	else if (select == DIVID)
		printf("결과 : %d // %d = %d\n", a, b, a / b);
	else
		printf("잘못된 입력입니다.\n");

	return 0;
}
//======================================================