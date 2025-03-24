#include "CRectangle.h"
using namespace std;

CRectangle::CRectangle(int wid, int hei)
{
	m_nWidth = wid;
	m_nHeight = hei;
}

void CRectangle::ShowArea()
{
	int area = m_nWidth * m_nHeight;
	cout << "Rect Area is " << area << endl;
}

void CRectangle::ShowCircumference()
{
	int circumference = m_nWidth * 2 + m_nHeight * 2;
	cout << "Rect Circumference is " << circumference << endl;
}