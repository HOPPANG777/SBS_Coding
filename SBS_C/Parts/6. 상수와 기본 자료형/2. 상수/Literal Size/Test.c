//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
/*

	1.	Literal Size..

		-	int 형으로 표현이 가능한
			정수형 상수는 int 형으로
			메모리 공간에 저장하기로 규정..

			ㄴ	정수형 상수는 int..


		-	double 형으로 표현이 가능한
			실수형 상수는 double 형으로
			메모리 공간에 저장하기로 규정..

			ㄴ	실수형 상수는 double..


		-	문자형 상수의 경우,
			컴파일러에 의해 정수로
			변환되므로 int형으로 표현..

*/
/*
int main(void)
{
	printf("literal int size : %d\n", sizeof(10));
	printf("literal double size : %d\n", sizeof(3.14));	
	printf("literal char size : %d\n", sizeof('A'));

	return 0;
}
//*/
//======================================================



//======================================================
/*
	2.	const, #define

*/
/*
#define BULLET_SPEED 20

const int EMPTY_BULLET = 0;
int g_nCurBulletCount = 10;

void Shoot()
{
	if (g_nCurBulletCount <= EMPTY_BULLET)
//	if (g_nCurBulletCount <= 0)
		return;

	--g_nCurBulletCount;
}

int main(void)
{
	const int BULLET_POW = 100;	

	printf("총알의 속도  : %d\n", BULLET_SPEED);
	printf("총알의 공격력  : %d\n", BULLET_POW);

	printf("현재 총알 갯수  : %d\n", g_nCurBulletCount);
	Shoot();
	printf("현재 총알 갯수  : %d\n", g_nCurBulletCount);
	
	return 0;
}

//*/
//======================================================
/*
	3.	열거형 상수 ( enum )
*/
//---------------------------------------

//*
enum DayOfWeek {
	Sunday = 5,
	Monday,
	Tuesday = 10,
	Wednesday,
	Thursday,
	Friday,
	Saturday
};
//---------------------------------------
void ShowDayOfWeek(enum DayOfWeek day) { printf("%d\n", day); }
//---------------------------------------
int main(void) {
	enum DayOfWeek week = Sunday;

	ShowDayOfWeek(week);

	ShowDayOfWeek(Monday);
	ShowDayOfWeek(Tuesday);
	ShowDayOfWeek(Wednesday);
	ShowDayOfWeek(Thursday);
	ShowDayOfWeek(Friday);
	ShowDayOfWeek(Saturday);

	return 0;
}
//*/
//======================================================