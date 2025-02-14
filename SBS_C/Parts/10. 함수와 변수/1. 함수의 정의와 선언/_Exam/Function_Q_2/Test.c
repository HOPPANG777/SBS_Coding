//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
//======================================================
float GetCels(float Fah)	{ return (Fah - 32) / 1.8f; }
float GetFahr(float Cels)	{ return (1.8f * Cels) + 32; }
//======================================================
int main()
{
	float Cel, Fah;

	printf("섭씨온도를 입력하세요 : ");
	scanf("%f", &Cel);
	Fah = GetFahr(Cel);
	printf("화씨로 %f 입니다.\n",Fah);


	printf("화씨온도를 입력하세요 : ");
	scanf("%f", &Fah);
	Cel = GetCels(Fah);
	printf("섭씨로 %f 입니다.\n", Cel);

	return 0;

}//	int main()
//======================================================