#include <stdio.h>

/*
	
	---------------------------
	-	printf의 기본적인 이해..
	---------------------------

		-	문자열 외에도 다양한 출력이 가능..

			-	서식문자를 사용하여
				정수, 실수 등을 출력..

				ㄴ	서식문자..

					ㄴ	출력의 형태를 지정하는
						키워드( 예약된 단어 )..
			
*/

int main(void)
{
	//	1.	정수의 출력과 서식문자..
	//*

	printf("Hello World!!\n");	//	문자열 출력..

	printf("%d\n", 3);			//	정수 출력..
								//	ㄴ	%d : 정수형 10진수 서식문자..

	printf("%d %d\n", 52, 153);	//	출력의 대상이 순서대로
								//	서식문자에 적용..

	printf("\n");

	//*/



	//	2.	다양한 출력 형태의 조합
	//*
	
	printf("My age : %d \n", 20);

	printf("%d is my Lucky Number \n", 7);

	printf("SBS\nGame Academy\n");

	//*/

	return 0;
}