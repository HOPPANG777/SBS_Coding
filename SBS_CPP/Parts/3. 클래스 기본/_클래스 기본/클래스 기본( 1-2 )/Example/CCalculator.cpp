//=======================================================
#include "CCalculator.h"
//=======================================================
void CCalculator::Init()
{
	m_fResult = 0.0f;
}
void CCalculator::Sum(float num1, float num2)
{
	m_fResult = num1 + num2;
}
void CCalculator::Minus(float num1, float num2)
{
	m_fResult = num1 - num2;
}
void CCalculator::Multi(float num1, float num2)
{
	m_fResult = num1 * num2;
}
void CCalculator::Divide(float num1, float num2)
{
	m_fResult = num1 / num2;
}
void CCalculator::ShowResult()
{
	cout << "Result is " << m_fResult << endl;
}
//=======================================================