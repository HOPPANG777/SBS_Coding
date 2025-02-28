//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	반환값과 매개변수에 따른
		함수의 분류..
*/
//======================================================
/*
//-----------------------------
//	반환값 O, 매개변수 O
int Add(int num1, int num2) { return num1 + num2; }
//-----------------------------
//	반환값 X, 매개변수 X
//	-	void 타입으로 반환하는 경우
//		return 생략 가능..
void ShowInfo() { printf("두 개의 정수를 입력하면 덧셈결과 출력.\n"); }
//-----------------------------
//	반환값 X, 매개변수 O
void ShowAddResult(int num) { printf("덧셈결과 : %d\n", num); return;}
//-----------------------------
//	반환값 O, 매개변수 X
int ReadNum()
{
	int num;
	scanf("%d", &num);
	return num;
}
//-----------------------------
int main(void)
{
	int result, num1, num2;

	ShowInfo();

	num1 = ReadNum();

	num2 = ReadNum();

	result = Add(num1, num2);

	ShowAddResult(result);

	return 0;
}
//-----------------------------
//*/
//======================================================
/*	Q - 1)
	
	3개의 정수를 입력받아
	가장 작은 수(1)와 가장 큰 수(2)를 
	반환하는 함수를 만들자.


	int GetMinimum( int a, int b, int c )
	int GetMaximum( int a, int b, int c )
	
*/
//======================================================
/*
	----------------
	2.	[ return ]의
		두가지 용도..
	----------------

		1)	값을 반환..

		2)	함수를 종료..

			-	반환 형이 void인 함수에서도
				return 문을 이용하여
				함수를 강제 종료 가능..

			예)
				void NoReturnFunction( int num )
				{
					......

					if( num < 0 )
						return;

					......
						
				}

*/

/*

void TestFunc()
{
	int a;
	scanf("%d", &a);

	if (a < 10)
		return;

	printf("성공\n");
}


int main()
{
	TestFunc();

	return 0;
}

//*/
//======================================================
/*
	----------------
	3.	함수의 정의와
		선언..
	----------------

		-	[ 함수의 정의 ]가
			[ 함수의 호출문 ]보다
			먼저 등장하는 경우,
			컴파일러는 컴파일 과정을 통해
			해당 함수가 존재한다는 것을
			인지..

		-	호출문이 먼저 등장하는 경우
			컴파일러는 인지 불가..

			ㄴ	함수는 호출되기 전에
				미리 정의되어야 함..

		-	컴파일러에게 해당 함수가
			어딘가에서 정의되어있다고 미리
			알려 줌으로써 에러를 방지..

			ㄴ	함수의 선언..



	------------
	4.	함수 선언
		방식..
	------------


		-	1)		2)		 3)
			반환형	함수 이름 ( 매개변수 );
		

			예)	int TestFunc( int a, float b );
				또는
				int TestFunc( int, float );
*/	

/*
//void TestFunc( int b );
//int TestFunc(int b);

int main()
{
	//	함수가 선언이 되어 있지 않다면
	//	컴파일러는 리턴 타입을
	//	int로 간주..
	TestFunc( 10 );

	return 0;
}

int TestFunc(int b)
//void TestFunc( int b )
{
	if (b < 10)
		//return;
		return 0;

	printf("성공\n");
	return 0;
}
//*/
//======================================================
/*
	----------------
	5.	다양한 방식의
		함수 사용..
	----------------

		1)	하나의 함수 내에
			둘 이상의 return 문이
			존재하는 경우..

		2)	함수의 리턴 값으로
			연산하기..

		3)	함수 내에서
			다른 함수 사용..
*/
//======================================================
/*
//	1)	하나의 함수내에
//		둘 이상의 return 문이
//		존재하는 경우..
int Compare(int num1, int num2);
//	-	함수가 선언이 되어 있지 않다면
//		컴파일러는 리턴 타입을
//		int로 간주..
int main()
{
	int n1, n2;
	printf("두개의 숫자를 입력하세요 : ");
	scanf("%d %d", &n1, &n2);

	//	int res = Compare(n1, n2);
	//	printf("두개의 숫자 중 가장 큰 수는 %d 입니다. \n", res);
	printf("두개의 숫자 중 가장 큰 수는 %d 입니다. \n", Compare(n1, n2));
	return 0;
}

//void Compare(int a, int b)
int Compare(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}
//*/

/*
//	3)	함수 내에서 다른 함수 사용..
//------------------------------
int GetAbs(int num);
int CompareAbs(int num1, int num2);
//------------------------------
int main()
{
	int num1, num2;
	printf("두개의 정수 입력 : ");
	scanf("%d %d", &num1, &num2);

	printf("%d와 %d중 절대값이 큰 수 : %d\n", num1, num2, CompareAbs(num1, num2));

	return 0;
}
//------------------------------
//	매개변수로 전달된 값의
//	절대값을 반환하는 함수..
int GetAbs(int num)
{
	if (num < 0)
		return num * (-1);
	else
		return num;
}
//------------------------------
//	2)	전달된 두 값의 절대값의
//		크기를 비교하는 함수..
int CompareAbs(int num1, int num2)
{
	if (GetAbs(num1) > GetAbs(num2))
		return num1;
	else
		return num2;
}
//*/
//======================================================
/*	quiz 2)

	섭씨 온도 -> 화씨 온도 
	화씨 온도 -> 섭씨 온도로
	변환하는 함수를 만들어 호출해본다..

		섭씨(Celsius)	=	( 화씨(F) - 32 ) / 1.8
		화씨(Fahrenheit)	=	( 1.8 x 섭씨(C) ) + 32

예)
	섭씨온도를 입력하세요 : 10
	화씨로  50.000000 입니다.

	화씨온도를 입력하세요 : 50
	섭씨로  10.000000 입니다.

*/
//======================================================