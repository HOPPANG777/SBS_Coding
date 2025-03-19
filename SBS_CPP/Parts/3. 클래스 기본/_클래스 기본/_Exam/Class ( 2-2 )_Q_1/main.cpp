#include<iostream>
#include"CRectangle.h"
#include"CCircle.h"

void main()
{
	cout << "=========================" << endl;
	CRectangle rect(10, 20);
	rect.ShowArea();
	rect.ShowCircumference();
	cout << "=========================" << endl;
	CCircle	_circle(2);
	_circle.ShowArea();
	_circle.ShowCircumference();
	cout << "=========================" << endl;
}
