//===========================================================
#include "CTime.h"
//===========================================================
using namespace std;
//----------------------------------------------
/*
CTime::CTime(int hour)
{
	m_nHour = hour;
	m_nMinute = 0;
	m_nSecond = 0;
}
CTime::CTime(int hour, int minute) : CTime( hour )
{
	m_nMinute = minute;
}
CTime::CTime(int hour, int minute, int second) : CTime( hour, minute )
{
	m_nSecond = second;
}
//*/
//----------------------------------------------
//*
CTime::CTime(int hour, int minute, int second)
{
	m_nHour = hour;
	m_nMinute = minute;
	m_nSecond = second;
}
//*/
//----------------------------------------------
void CTime::ShowTime()
{
	cout	<< "일반시간 : "
			<< m_nHour << " : "
			<< m_nMinute << " : "
			<< m_nSecond << endl;
}
//----------------------------------------------
void CTime::ShowTimeInSec()
{
	int totalSec = m_nSecond + m_nMinute * 60 + m_nHour * 60 * 60;
	cout << "초시간 : " << totalSec << endl;
}
//===========================================================