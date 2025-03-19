//=================================================
#pragma once
//=================================================
#ifndef _CCALCULATOR_H_
#define _CCALCULATOR_H_
//=================================================
#include<iostream>
using namespace std;
//=================================================
class CCalculator
{
	float m_fResult;

public:
	void Init();
	void Sum(float num1, float num2);
	void Minus(float num1, float num2);
	void Multi(float num1, float num2);
	void Divide(float num1, float num2);
	void ShowResult();

	/*	inline ¼±¾ð..
	void Init()							{ m_fResult = 0.0f; }
	void Sum(float num1, float num2)	{ m_fResult = num1 + num2; }
	void Minus(float num1, float num2)	{ m_fResult = num1 - num2; }
	void Multi(float num1, float num2)	{ m_fResult = num1 * num2; }
	void Divide(float num1, float num2) { m_fResult = num1 / num2; }
	void ShowResult()					{ cout << "Result is " << m_fResult << endl; }
	//*/

};	//	class CCalculator
//=================================================
#endif 
//=================================================