//=====================================================================================
#include "CRaceManager.h"
//=====================================================================================
CRaceManager::CRaceManager( int goalDist )
{
	_goalDist = goalDist;
	_isFinish = false;
	_curTime = 0.0f;
	const char names[][2] = { "A", "B", "C", "D", "E" };
	srand(time(0));
	for (int cur = 0; cur < 5; ++cur)
	{
		int tmpSpeed = (rand() % 6)  + 5;	//	5 ~ 10
		int tmpRandTime = (rand() % 3) + 1;	//	1 ~ 3

		_pHorses[cur] = new CHorse(
			names[cur],
			10,
			10 + cur * 30,
			tmpSpeed,
			tmpRandTime );

	}//	for (int cur = 0; cur < 5; ++cur)

}//	CRaceManager::CRaceManager()
//----------------------------------------------------
CRaceManager::~CRaceManager()
{
	for (int cur = 0; cur < 5; ++cur)
	{
		delete _pHorses[cur];
		_pHorses[cur] = NULL;

	}//	for (int cur = 0; cur < 5; ++cur)

}//	CRaceManager::~CRaceManager()
//----------------------------------------------------
void CRaceManager::DoRace(HDC hdc, float elaspsedTime)
{
	if (_isFinish)
		return;

	_curTime += elaspsedTime;

	for (int cur = 0; cur < 5; ++cur)
	{
		if ( _pHorses[cur]->IsGoal( _goalDist ) )
		{
			_isFinish = true;
            TCHAR szTmp[100] = "";
            wsprintf(szTmp, "승자는 %s 입니다!!!", _pHorses[cur]->GetName());
            MessageBox(NULL, szTmp, "결과", MB_OK);
			return;

		}//	if (_pHorses[cur]->GetPosX() >= 1000)

		_pHorses[cur]->Run(hdc);
		_pHorses[cur]->UpdateInfo(_curTime);

	}//	for (int cur = 0; cur < 5; ++cur)

}//	void CRaceManager::DoRace(HDC hdc, float elaspsedTime)
//=====================================================================================