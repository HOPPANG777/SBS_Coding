//=================================================
#pragma once
//=================================================
#ifndef _CCIRCLE_H_
#define _CCIRCLE_H_
//=================================================
#include<iostream>
using namespace std;
//=================================================
const float PHI = 3.14f;
//=================================================
class CCircle
{
	float m_nRad;

public:
	CCircle(float rad);
	void ShowArea();
	void ShowCircumference();

};	//	class CCircle
//=================================================
#endif 
//=================================================