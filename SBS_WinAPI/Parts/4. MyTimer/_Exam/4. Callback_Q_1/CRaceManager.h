//====================================================================
#pragma once
#include "CHorse.h"
#include <time.h>
#include <stdlib.h>
#include <Windows.h>
//====================================================================
class CRaceManager
{
	CHorse* _pHorses[5];
	bool _isFinish;
	float _curTime;
	int _goalDist;

public :
	CRaceManager(int goalDist);
	~CRaceManager();
	void DoRace(HDC hdc, float elaspsedTime);

};// class CRaceManager
//====================================================================