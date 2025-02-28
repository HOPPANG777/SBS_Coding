//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	Forced Type Conversion..

		-	연산 결과의 자료형은
			피연산자의 자료형과 일치..

		-	소괄호()로 변환시키고자 하는
			타입을 설정..

			ㄴ	이때 소괄호는 [ 형변환 연산자 ]로
				사용됨..

			ㄴ	타입을 명시해줌으로써
				[ 자동 형변환 ]이 되도록 유도..
*/


int main(void)
{
	int num1 = 3, num2 = 4;
    //float divResult = num1 / num2;
	//	다음과 같이 수정..
	float divResult = (float)num1 / num2;
	//float divResult = num1 / (float)num2;

	/* 과정..
	
	    1)  num1 / num2 = 0.75..

        2)  연산결과 0.75를
			피연산자의 자료형 int와
			일치시킴..

        3)	소수점 이하는 [ int ]가
			관리못하여 제거됨..

		4)  float divResult = 0;

		5)	결과..
		
			ㄴ	divResult = 0.000000f;
	*/	
	
	printf("%d / %d = %f\n", num1, num2, divResult);

	
	return 0;
}
//======================================================