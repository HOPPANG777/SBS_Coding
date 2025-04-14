//====================================================================
#pragma once
#include <windows.h>
//====================================================================
class CHorse
{
	char _szName[50];
	int _speed;
	int _posX;
	int _posY;
	int _speedChangeTime;
	
public :
	CHorse(const char *pszName, int startX, int startY, int speed, int randomTime);
	void Run(HDC hdc);	
	void UpdateInfo(float curTime);
    char* GetName() { return _szName; }
	bool IsGoal( int goalDist )
	{
		if (_posX >= goalDist) return true;
		return false;
	}

};// class CHorse
//====================================================================