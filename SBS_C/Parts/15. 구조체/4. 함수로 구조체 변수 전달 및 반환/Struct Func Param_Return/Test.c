//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*
	1.	함수의 매개 변수를 통한
		구조체 변수의 전달 & 반환..

		-	일반 변수와 마찬가지..
		
			1)	함수의 인자로 전달..

			2)	반환될 때..
	
			[ 값의 복사 ]가 진행된다.
*/
//----------------
/*
typedef struct
{
	char _name[20];
	char _phoneNumber[20];
	int _age;
}SPerson;

//----------------
SPerson GetPersonInfo()
{
	SPerson tmpPerson;

	printf("이름 : "); scanf("%s", tmpPerson._name);
	printf("전화번호 : "); scanf("%s", tmpPerson._phoneNumber);
	printf("나이 : "); scanf("%d", &tmpPerson._age);

	return tmpPerson;
}
//----------------
void ShowPersonIfo(SPerson person)
{
	printf("---- show info ----\n");
	printf("이름 : %s \n", person._name);
	printf("전화번호 : %s \n", person._phoneNumber);
	printf("나이 : %d \n", person._age);
		
}
//----------------
int main()
{
	SPerson person = GetPersonInfo();

	ShowPersonIfo(person);

	return 0;
}
//----------------
//*/
//======================================================
/*
	1-2.	함수의 매개 변수를 통한
			구조체 변수의 전달 & 반환..
			( call by reference )
*/
//======================================================
/*
//----------------
typedef struct
{
	int _xPos;
	int _yPos;

}SPoint;
//----------------
//	원점 대칭..
void OriginSymmetry(SPoint *pPtr)
{
	pPtr->_xPos *= -1;
	pPtr->_yPos *= -1;
}
//----------------
void ShowPoint(SPoint pt) {	printf("[%d, %d]\n", pt._xPos, pt._yPos); }
//----------------
int main()
{
	SPoint pos = { 1,-2 };
	ShowPoint(pos);

	OriginSymmetry(&pos);
	ShowPoint(pos);

	OriginSymmetry(&pos);
	ShowPoint(pos);

	return 0;
}
//----------------
//*/
//======================================================
/*
	2.	구조체 변수를 대상으로
		가능한 연산..

		-	매우 제한된 형태의
			연산만 허용..

			-	대입( = )
			-	주소값 반환( & )
			-	구조체 변수의 크기( sizeof )

		-	그외 산술 등의 연산은
			적용되지 않음..
*/
//======================================================

//-------------------------
//	대입 연산, sizeof 연산..
//-------------------------
//*
typedef struct
{
	int _xPos;
	int _yPos;

}SPoint;

int main()
{
	SPoint pos1 = { 1, 2 };
	SPoint pos2 = pos1;	//	멤버간의 복사..

	printf("크기 : %d\n", sizeof(pos1));
	printf("[%d, %d]\n", pos1._xPos, pos1._yPos);

	printf("크기 : %d\n", sizeof(pos2));
	printf("[%d, %d]\n", pos2._xPos, pos2._yPos);

	/*	그외 연산은 허용되지 않음..
	
		-	why???

			-	4칙 연산을 정형화하는데
				무리가 있음..

				-	구조체의 멤버로 배열이나
					포인터 변수, 다른 구조체 등의
					변수가 선언될 수 있음..

					ㄴ	멤버 변수들을 어떤 식으로
						세팅할 지 미리 파악 불가..

				-	함수를 정의하여 사용 할 것..
	*/
	
	/*
	SPoint pos3;
	pos3 = pos1 + pos2;
	pos3 = pos1 - pos2;
	pos3 = pos1 * pos2;
	pos3 = pos1 >> 1;
	
	printf("크기 : %d\n", sizeof(pos3));
	printf("[%d, %d]\n", pos3._xPos, pos3._yPos);
	//*/

	//return 0;
//}
//*/


/*
//------------
//	함수 적용..
//------------
typedef struct
{
	int _xPos;
	int _yPos;

}SPoint;
//----------------
SPoint AddPoint(SPoint pos1, SPoint pos2)
{
	SPoint tmpPos = { pos1._xPos + pos2._xPos, pos1._yPos + pos2._yPos };
	return tmpPos;
}
//----------------
SPoint MinusPoint(SPoint pos1, SPoint pos2)
{
	SPoint tmpPos = { pos1._xPos - pos2._xPos, pos1._yPos - pos2._yPos };
	return tmpPos;
}
//----------------
int main()
{
	SPoint pos1 = { 10, 20 };
	SPoint pos2 = { 5, 15 };
	SPoint tmpPos;

	tmpPos = AddPoint(pos1, pos2);
	printf("[%d, %d]\n", tmpPos._xPos, tmpPos._yPos);

	tmpPos = MinusPoint(pos1, pos2);
	printf("[%d, %d]\n", tmpPos._xPos, tmpPos._yPos);

	return 0;
}
//----------------
//*/
//======================================================
/*
	quiz)

		두개의 벡터..
		SVector2 pos1 = {1,2}
		SVector2 pos2 = {5,-1}

		가 있을때..

		pos2 -> pos1 으로 향하는
		단위 방향 벡터를 구하는
		프로그램을 만든다..

		[ 참고 : https://m.blog.naver.com/kimjw1218/70178130823 ]

		방향 벡터..
		=	목표 지점 - 시작 지점
			( Target.x - Start.x, Target.y - Start.y )

		단위 벡터..
		=	크기 1인 벡터..
		
*/
//======================================================