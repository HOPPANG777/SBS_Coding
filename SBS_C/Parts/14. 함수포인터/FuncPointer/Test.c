//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	함수 포인터
	
	-	반환형	(*함수 포인터 이름) ( 매개변수 리스트 )
*/
//======================================================
/*
void Add(int a, int b)		{ printf("%d + %d = %d\n", a, b, a + b); }
void ShowString(char* psz)	{ printf("%s\n", psz); }

void (*funcPtr1)(int, int);
void (*funcPtr2)(char*);

int main(void)
{
	char *psz = "Func Pointer";
	int num1 = 10, num2 = 20;

	funcPtr1 = Add;
	funcPtr2 = ShowString;

	funcPtr1(num1, num2);
	funcPtr2(psz);

	Add(num1, num2);
	ShowString(psz);
	
	return 0;
}
//*/
//======================================================
/*
2.	함수 포인터와 typedef
	
	-	위 소스에 typedef 적용.

	-	일반적인 방식..

		unsigned int a;
		typedef unsigned int UINT;
		unsigned int a;
		->	UINT a;


	-	치환 방식
	
		typedef void (*FPtr1)(int, int);
		
		.....

		FPtr1 pFPtr1	==>		void (*pFPtr1)(int, int);

		-	함수 포인터에서의 typedef문은
			일반적인 방법과 약간 다르지만
			결국 사용되는 목적은 같음.
*/
//======================================================
/*
void Add(int a, int b)		{ printf("%d + %d = %d\n", a, b, a + b); }
void ShowString(char* psz)	{ printf("%s\n", psz); }

typedef void (*FPtr1)(int, int);
typedef void (*FPtr2)(char*);

int main(void)
{
	char* psz = "Func Pointer";
	int num1 = 10, num2 = 20;

	FPtr1 pFPtr1 = Add;
	FPtr2 pFPtr2 = ShowString;

	pFPtr1(num1, num2);
	pFPtr2(psz);

	Add(num1, num2);
	ShowString(psz);

	return 0;
}
//*/
//======================================================
/*
3.	매개변수의 선언으로 사용되는 함수 포인터

	-	[ 함수포인터.txt3 ] 
		
		>> 3. 함수 포인터의 용도
	
		>> 1>	개발자에게는
				인터페이스만 제공하고
				알고리즘은
				상황에 따라 선택해야하는 경우.
*/
//======================================================
/*
int OlderFirst(int age1, int age2)
{
	if (age1 > age2)
		return age1;
	else if (age1 < age2)
		return age2;
	else
		return 0;
}

int YoungerFirst(int age1, int age2)
{
	if (age1 < age2)
		return age1;
	else if (age1 > age2)
		return age2;
	else
		return 0;
}

typedef int (*FPtr1)(int, int);

//int WhoIsFirst(int age1, int age2, int(*compare)(int n1, int n2))
int WhoIsFirst(int age1, int age2, FPtr1 compare)
{
	return compare(age1, age2);
}

int main()
{
	int age1 = 10;
	int age2 = 20;

	int result = 0;

	printf("대인 순 \n");
	result = WhoIsFirst(age1, age2, OlderFirst);
	printf("%d살과 %d살 중 %d살이 먼저입장!!\n",age1,age2,result);


	printf("소인 순 \n");
	result = WhoIsFirst(age1, age2, YoungerFirst);
	printf("%d살과 %d살 중 %d살이 먼저입장!!\n", age1, age2, result);

	return 0;
}

//*/
//======================================================
/*
	quiz)
		두 정수의 입력을 받아
		실수를 반환하는 사칙 연산 함수를 각각 만들고
		( Add, Sub, Multi, Divide )			
		함수포인터를 이용하여 사칙연산을 실행한다.
		(*pCalculate)

		예)
			2개의 숫자를 입력하세요 : 10 20 ( 두 숫자가 -1 이면 종료.. )

			연산		: 1
				1.합		2.차		3.곱		4.몫

			결과
				10 + 20 = 30


			2개의 숫자를 입력하세요 : 10 20 ( 두 숫자가 -1 이면 종료.. )
			......
*/
//======================================================