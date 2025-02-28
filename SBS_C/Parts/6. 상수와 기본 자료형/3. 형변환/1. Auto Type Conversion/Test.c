//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	Auto Type Conversion
*/

int main(void)
{
	//	대입 연산 과정에서 발생하는 경우..
	double num1 = 153;
	printf("정수 153을 실수로 표현 : %lf\n", num1);

	int num2 = 3.1415;
	printf("실수 3.1415을 정수로 표현 : %d\n", num2);

	int num3 = 129;
	char ch = num3;
	printf("int 정수 129을 char타입으로 표현 : %d\n", ch);


	//	정수의 승격에 의한 경우..
	short num4 = 10;
	short num5 = 20;
	int size = sizeof(num4 + num5);
	printf("sizeof(num4 + num5) : %d\n", size);


	//	피연산자의 자료형이 불일치하는 경우..
	double num6 = 1.53 + 153;
	printf("num6 : %f\n", num6);

	return 0;
}
//======================================================