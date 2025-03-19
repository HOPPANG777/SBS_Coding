#include "CCircle.h"
using namespace std;
CCircle::CCircle(float rad)	{ m_nRad = rad; }

void CCircle::ShowArea()
{
	float area = PHI * m_nRad * m_nRad;
	cout << "Circle Area is " << area << endl;
}

void CCircle::ShowCircumference()
{
	float circumference = 2 * PHI * m_nRad;
	cout << "Circle Circumference is " << circumference << endl;
}