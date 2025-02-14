//======================================================
#pragma warning (disable : 4996)
#include <stdio.h>
#include "Calculate.h"
//======================================================
void main()
{
	int numberA;
	int numberB;
	printf("Input Number : ");
	scanf("%d", &numberA);

	printf("Input Number : ");
	scanf("%d", &numberB);

	printf("%d + %d = %d\n", numberA, numberB, Plus(numberA, numberB));
	printf("%d - %d = %d\n", numberA, numberB, Minus(numberA, numberB));
}
//======================================================//