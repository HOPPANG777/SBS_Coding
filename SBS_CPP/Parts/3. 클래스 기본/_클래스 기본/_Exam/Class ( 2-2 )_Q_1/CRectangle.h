//=================================================
#pragma once
//=================================================
#ifndef _CRECTANGLE_H_
#define _CRECTANGLE_H_
//=================================================
#include<iostream>
using namespace std;
//=================================================
class CRectangle
{
	int m_nWidth;
	int m_nHeight;

public:
	CRectangle(int wid, int hei);
	void ShowArea();
	void ShowCircumference();

};	//	class CRectangle
//=================================================
#endif 
//=================================================