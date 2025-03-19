#include<iostream>
#include"CCalculator.h"

void main()
{
	CCalculator cal;

	cal.Init();	//	멤버변수 초기화.

	cal.Sum(1, 2);
	cal.Minus(5, 2);
	cal.Multi(2, 3);
	cal.Divide(4,3);
}
