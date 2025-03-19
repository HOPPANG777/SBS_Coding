//============================================================
/*
	Quiz - 2)	시,분,초를 관리하는 CTime클래스를
				다음과 같이 사용할 수 있도록 구현한다.

					CTime _time(시);
					CTime _time(시,분);
					CTime _time(시,분,초);

					_time.ShowTime();		->	xx시 xx분 xx초
					_time.ShowTimeInSec();	->	xx초.
*/
//============================================================
#include<iostream>
#include"CTime.h"
//============================================================
void main()
{
	cout << "=========================" << endl;
	CTime time(1);
	time.ShowTime();
	time.ShowTimeInSec();

	CTime time2(1, 2);
	time2.ShowTime();
	time2.ShowTimeInSec();

	CTime time3(0, 2, 33);
	time3.ShowTime();
	time3.ShowTimeInSec();
	cout << "=========================" << endl;
}
//============================================================