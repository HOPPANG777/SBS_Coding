//==============================================
#include<iostream>
#include"CCalculator.h"
//==============================================
void main()
{
	CCalculator cal;

	cal.Init();	//	멤버변수 초기화.

	cal.Sum(1, 2);
	cal.ShowResult();

	cal.Minus(5, 2);
	cal.ShowResult();

	cal.Multi(2, 3);
	cal.ShowResult();

	cal.Divide(4,3);
	cal.ShowResult();

}//	void main()
//==============================================