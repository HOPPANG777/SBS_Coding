//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	sizeof 연산자.
*/
/*
int main(void)
{
	char cNum = 1;
	int nNum = 1000;
	double dNum = 3.14;

	printf("-----------------------\n");
	printf(" cNum 의 크기 : %d \n", sizeof(cNum) );
	printf(" nNum 의 크기 : %d \n", sizeof(nNum) );
	printf(" dNum 의 크기 : %d \n", sizeof(dNum) );

	printf("-----------------------\n");
	printf(" char 의 크기 : %d \n", sizeof(char) );
	printf(" int 의 크기 : %d \n", sizeof(int));
	printf(" long 의 크기 : %d \n", sizeof(long));
	printf(" long long 의 크기 : %d \n", sizeof(long long));
	printf(" float 의 크기 : %d \n", sizeof(float));
	printf(" double 의 크기 : %d \n", sizeof(double));
	printf("-----------------------\n\n");

	return 0;
}
//*/
//======================================================



//======================================================
/*
	2.	정수 자료형의 선택
*/

/*
int main(void)
{
	char chNum1 = 1, chNum2 = 2, chResult = 0;
	short shNum1 = 300, shNum2 = 400, shResult = 0;
	printf("-----------------------\n");
	printf("chNum1 과 chNum2의 크기 : %d, %d\n", sizeof(chNum1), sizeof(chNum2));
	printf("shNum1 과 shNum2의 크기 : %d, %d\n", sizeof(shNum1), sizeof(shNum2));
	printf("-----------------------\n");

	//	int 형보다 작은 크기의 데이터는
	//	int형 데이터로 바꿔서 연산이 진행된다.
	printf("char형 데이터의 합의 크기 : %d\n", sizeof(chNum1 + chNum2));
	printf("short형 데이터의 합의 크기 : %d\n", sizeof(shNum1 + shNum2));
	printf("-----------------------\n");
	chResult = chNum1 + chNum2;
	shResult = shNum1 + shNum2;
	printf("-----------------------\n\n");
	printf("chResult 과 shResult의 크기 : %d, %d\n", sizeof(chResult), sizeof(shResult));

	return 0;
}
//*/
//======================================================



//======================================================
/*
3.	실수 자료형의 선택.

	-	가장 보편적으로
		double형을 사용하라고 권장..
		-	float보다 정밀도가 높으며
			long double 보다는
			용량의 부담이
			덜하기 때문..
		-	실제로 실무에서는
			float을 많이 사용..
*/
//======================================================
/*
int main()
{
	double dRad;
	double dArea;

	printf("원의 반지름 : ");
	scanf("%lf", &dRad);

	dArea = dRad * dRad * 3.141592;
	printf("원의 넓이 : %lf\n", dArea);

	return 0;
}
//*/
//======================================================