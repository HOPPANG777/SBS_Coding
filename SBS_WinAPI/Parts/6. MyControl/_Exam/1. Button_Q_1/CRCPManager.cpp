//================================================================
#include "CRCPManager.h"
//================================================================
const int MAXPLAYCOUNT = 5;
//--------------------------------------
CRCPManager::CRCPManager() { Reset(); }
//--------------------------------------
void CRCPManager::Reset()
{
	_playCount = 0;
	_isFinish = false;
	_winCount = 0;
	_drawCount = 0;
	_loseCount = 0;
}
//--------------------------------------
int CRCPManager::GetCPUSelect()
{
	srand(time(NULL));
	int cpuSelect = rand() % 3;
	return cpuSelect;
}
//--------------------------------------
char* CRCPManager::GetRCPString(int rcp)
{
	char szTmp[10] = "";

	switch (rcp)
	{
		case 0: strcpy(szTmp, "가위"); break;
		case 1: strcpy(szTmp, "바위"); break;
		case 2: strcpy(szTmp, "보"); break;
	}

	return szTmp;
}
//--------------------------------------
int CRCPManager::GetResult(int player, int cpu)
{
	int result = DRAW;
	switch (player)
	{
	case 0:
		if (cpu == 1) result = LOSE;
		else if (cpu == 2) result = WIN;
		break;

	case 1:
		if (cpu == 0) result = WIN;
		else if (cpu == 2) result = LOSE;
		break;

	case 2:
		if (cpu == 0) result = LOSE;
		else if (cpu == 1) result = WIN;
		break;
	}

	return result;
}
//--------------------------------------
char* CRCPManager::GetResultString(int result)
{
	switch (result)
	{
		case WIN: return "승";
		case LOSE: return "패";
	}

	return "무";
}
//--------------------------------------
void CRCPManager::ShowTitle(HDC hdc)
{
	char szTmp[50] = "가위바위보 게임입니다. ^^";
	TextOut(hdc, 100, 100, szTmp, strlen(szTmp));
}
//--------------------------------------
void CRCPManager::ShowResult(HDC hdc)
{
	if (_isFinish == false)
		return;

	char szResult[100] = "";
	wsprintf(szResult, "승 : %d | 무 : %d | 패 : %d ", _winCount, _drawCount, _loseCount);
	TextOut(hdc, 100, 300, szResult, strlen(szResult));
}
//--------------------------------------
void CRCPManager::ProcessRCP(HWND hWnd, int myRCP)
{
	if (_isFinish)
		return;

	char szResult[10] = "";
	char szMyRCP[10] = "";
	char szCpuRCP[10] = "";
	char szDesc[50] = "";

	int cpuRCP = GetCPUSelect();
	int result = GetResult(myRCP, cpuRCP);
	strcpy(szMyRCP, GetRCPString(myRCP));
	strcpy(szCpuRCP, GetRCPString(cpuRCP));
	strcpy(szResult, GetResultString(result));

	wsprintf(szDesc, "Player : %s,  CPU : %s", szMyRCP, szCpuRCP);

	MessageBox(hWnd, szDesc, szResult, MB_OK);

	++_playCount;

	switch (result)
	{
		case WIN: ++_winCount; break;
		case LOSE: ++_loseCount; break;
		case DRAW: ++_drawCount; break;
	}

	if (_playCount >= MAXPLAYCOUNT)
	{
		_isFinish = true;
		InvalidateRect(hWnd, NULL, TRUE);
	}

}//	void CRCPManager::ProcessRCP(HWND hWnd, int myRCP)
//================================================================//