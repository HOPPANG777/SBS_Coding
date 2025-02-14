//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
float Add(int a, int b)		{ return a + b; }
float Sub(int a, int b)		{ return a - b; }
float Multi(int a, int b)	{ return a * b; }
float Div(int a, int b)		{ return (float)a / b; }
float Rest(int a, int b)	{ return a % b; }
//======================================================
float(*Calc)(int a, int b);
//======================================================
#define SUM 1
#define SUB 2
#define MULT 3
#define DIVIDE 4
#define REST 5
//======================================================
int main()
{	
	int num1, num2;
	do
	{	
		printf("2개의 숫자를 입력하세요 : ");
		scanf("%d %d", &num1, &num2);

		if (num1 == -1 && num2 == -1)
			break;

		printf("연산 방식을 선택하세요 : \n");
		printf("1. 합\t\t2. 차\t\t3. 곱\t\t4. 몫\t\t5. 나머지\n");

		int select;
		float result = 0;
		scanf("%d", &select);

		switch (select)
		{
			case SUM:		Calc = Add;		printf("%d + %d = ", num1, num2); break;
			case SUB:		Calc = Sub;		printf("%d - %d = ", num1, num2); break;
			case MULT:		Calc = Multi;	printf("%d * %d = ", num1, num2); break;
			case DIVIDE:	Calc = Div;		printf("%d / %d = ", num1, num2); break;
			case REST:		Calc = Rest;	printf("%d %% %d = ", num1, num2); break;

		}//	switch (select)

		result = Calc(num1, num2);

		printf("%f\n", result);

	} while (1);
		
	return 0;

}//	int main()
//======================================================//