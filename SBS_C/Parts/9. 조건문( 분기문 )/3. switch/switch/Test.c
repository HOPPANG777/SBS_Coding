//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
1.	switch..
*/
//======================================================
/*
int main(void)
{
	int num;

	printf("1 ~ 3 이하의 정수 입력 : ");
	scanf("%d", &num);

	switch (num)
	{
	case 1:		//	:	으로 마무리.
		printf("1 : 하나\n");
		break;	//	주석처리 한다면...?

	case 2:
		printf("2 : 둘\n");
		break;

	case 3:
		printf("3 : 셋\n");
		break;

	default:	//	필요없는 경우 생략 가능.
		printf("잘못된 수 입력\n");
		break;
	}

	return 0;
}
//*/

/*
int main(void)
{
	char word;

	printf("a ~ c 중 문자 하나 선택 : ");
	scanf("%c", &word);

	switch (word)
	{
	case 'a':	//	:	으로 마무리.
		printf("에이\n");
		break;

	case 'b':
		printf("비\n");
		break;

	case 'c':
		printf("씨\n");
		break;

	//	필요없는 경우 생략 가능..
	default:
		printf("잘못된 입력\n");
		break;
	}

	return 0;
}
//*/

//======================================================
/*	
	quiz 1)	
	
		영문자를 입력하세요 (A ~ C) : A(또는 a)
	
		한글로 에이

*/
//======================================================
/*
	2.	switch vs if ~ else
	
		-	switch 문이 if ~ else 문에 비해
			다소 깔끔함..

		-	하지만 switch 문으로 구현할 수 있는
			조건의 구성에는 한계가 있음..

			->	switch문으로 표현하기
				애매한 경우에 if ~ else를 사용..

*/
//======================================================
//	범위로 비교하는 경우
//	if ~ else 권장..
//======================================================
/*
int main(void)
{
	int num;
	printf("숫자를 입력하세요 : ");
	scanf("%d", &num);

	if (0 <= num && num < 10)
		printf("0 이상 10 미만\n");

	else if (10 <= num && num < 20)
		printf("10 이상 20 미만\n");

	else if (20 <= num && num < 30)
		printf("20 이상 30 미만\n");

	else
		printf("음수 또는 30 이상\n");
	
	return 0;
}
//*/
//======================================================
//	quiz 2) 위 예제의 if ~ else 문을
//			약간만 수정하면
//			switch 문으로 변경이 가능하다.
//======================================================
/*
	
	----------
	참고..
	----------

		----------
		-	goto..
		----------

			ㄴ	프로그램의 흐름을
				원하는 위치로 이동..


			ㄴ	goto의 사용에 대한 논쟁이 있었으나
				현재는 거의 부정적인 의견이 다수..

				ㄴ	일부 책에서는 언급도 하지 않음..


			ㄴ	단점..

				ㄴ	프로그램의 자연스런 흐름을 방해..

				ㄴ	반드시 goto문을 써야만
					해결할 수 있는 상황이
					있는 것도 아님..
	

			ㄴ	결론..
		
				ㄴ	쓰지 말자..

					ㄴ	안티 패턴..


			ㄴ	형식..

				int main
				{
					.....

					레이블:			//	위치지정에 사용.


					......

					goto 레이블;	//	레이블의 위치로 이동.

				}

*/



/*
int main(void)
{
	int num;

	printf("숫자를 입력 : ");
	scanf("%d", &num);

	if (num == 1)
		goto ONE;
	else if (num == 2)
		goto TWO;
	else
		goto OTHER;


ONE:
	printf("1 입력\n");
	goto END;

TWO:
	printf("2 입력\n");
	goto END;

OTHER:
	printf("3 또는 다른값 입력\n");

END:
	return 0;
}
//*/
//======================================================