//================================================================
#pragma once
#include <windows.h>
#include <stdlib.h>
#include <time.h>
//================================================================
enum
{
	WIN,
	LOSE,
	DRAW
};
//================================================================
class CRCPManager
{	
	int _playCount;
	bool _isFinish;
	int _winCount;
	int _drawCount;
	int _loseCount;

	int GetCPUSelect();
	char* GetRCPString(int rcp);
	int GetResult(int player, int cpu);
	char* GetResultString(int result);	
	
public:
	CRCPManager();
	void ProcessRCP(HWND hWnd, int myRCP);
	void Reset();
	int GetWinCount() { return _winCount; }
	int GetDrawCount() { return _drawCount; }
	int GetLoseCount() { return _loseCount; }
	bool IsFinish() { return _isFinish; }
	void ShowTitle(HDC hdc);
	void ShowResult(HDC hdc);
	
};
//================================================================