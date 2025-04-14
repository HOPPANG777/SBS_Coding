//====================================================================
#include "CHorse.h"
#include <iostream>
//====================================================================
CHorse::CHorse(const char *pszName, int startX, int startY, int speed, int speedChangeTime )
{
	strcpy(_szName, pszName);
	_posX = startX;
	_posY = startY;
	_speed = speed;
	_speedChangeTime = speedChangeTime;

}//	CHorse::CHorse(const char *pszName, int startX, int startY, int speed, int randomTime)
//----------------------------------------------
void CHorse::Run( HDC hdc )
{
	_posX += _speed;
	TextOut(hdc, _posX, _posY, _szName, strlen(_szName));

}//	void CHorse::Run( HDC hdc )
//----------------------------------------------
void CHorse::UpdateInfo(float curTime)
{
	if (((int)curTime % _speedChangeTime) == 0)
	{
		int tmpSpeed = (rand() % 6) + 5;	//	5 ~ 10
		int tmpRandTime = (rand() % 3) + 1;	//	1 ~ 3
		_speed = tmpSpeed;
		_speedChangeTime = tmpRandTime;

	}//	if (((int)_curTime % _pHorses[cur]->GetRandomTime()) == 0)

}//	void CHorse::UpdateInfo(float curTime)
//====================================================================