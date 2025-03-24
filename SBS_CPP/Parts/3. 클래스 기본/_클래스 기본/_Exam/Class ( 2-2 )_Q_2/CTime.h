//=================================================
#pragma once
//=================================================
#ifndef _CCIRCLE_H_
#define _CCIRCLE_H_
//=================================================
#include<iostream>
using namespace std;
//=================================================
class CTime
{
	int m_nHour;
	int m_nMinute;
	int m_nSecond;

public:
	//*	생성자 오버로딩..
	CTime(int hour);
	CTime(int hour, int minute);
	CTime(int hour, int minute, int second);
	//*/

	/*	디폴트 매개변수..
	CTime(int hour = 0, int minute = 0, int second = 0);
	//*/

	void ShowTime();
	void ShowTimeInSec();


};	//	class CCircle
//=================================================
#endif 
//=================================================