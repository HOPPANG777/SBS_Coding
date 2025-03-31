//====================================================
#pragma warning ( disable : 4996 )
#include<iostream>
#include<time.h>
#include<stdlib.h>
#include"CRSPManager.h"
using namespace std;
//====================================================
void CRSPManager::ShowMenu()
{
	system("cls");
	cout << "- 가위바위보 게임입니다. --" << endl;
	cout << "                   현재 결과 " << _winCount << "승 " << _drawCount << "무 " << _loseCount << "패" << endl;
	cout << "  번호를 선택해주세요" << endl;
	cout << "  1) 가위     2) 바위     3) 보   4) 종료" << endl;	

}//	void CRSPManager::ShowMenu()
//---------------------------------------
int CRSPManager::GetResult( int player, int cpu )
{
	if (player == cpu) { ++_drawCount; return DRAW; }

	if (player == ROCK && cpu == SCISSOR) { ++_winCount; return WIN; }
	if (player == SCISSOR && cpu == PAPER) { ++_winCount; return WIN; }
	if (player == PAPER && cpu == ROCK) { ++_winCount; return WIN; }

	++_loseCount; return LOSE;

}//	int CRSPManager::GetResult( int player, int cpu )
//---------------------------------------
const char* CRSPManager::GetHandToString(int card)
{
	switch (card)
	{
		case SCISSOR: return "가위";
		case ROCK: return "바위";
		case PAPER: return "보";
		default: return "오타???";

	}//	switch (card)

	return NULL;

}//	char* CRSPManager::GetHandToString(int card)
//---------------------------------------
void CRSPManager::ShowResult( int player, int cpu, int result )
{
	char szPlayer[10], szCpu[10];
	strcpy(szPlayer, GetHandToString(player));
	strcpy(szCpu, GetHandToString(cpu));

	cout << "플레이어 : " << szPlayer << "     cpu : " << szCpu << endl;
	switch (result)
	{
		case WIN:	cout << "이겼습니다." << endl; break;
		case LOSE:	cout << "졌습니다." << endl; break;
		case DRAW:	cout << "무승부 입니다." << endl; break;
	
	}//	switch (result)

	system("pause");

}//	void CRSPManager::ShowResult( int player, int cpu, int result )
//---------------------------------------
void CRSPManager::Process()
{
	while (1)
	{
		ShowMenu();
				
		int player = GetPlayerHand();
		if (player == FINISH) exit(1);

		int cpu = GetComHand();
		int result = GetResult(player, cpu);

		ShowResult(player, cpu, result);

		if (_winCount >= 3 || _loseCount >= 3)
		{
			cout << "- 최종 결과.. --" << endl;
			cout << _winCount << "승 " << _drawCount << "무 " << _loseCount << "패" << endl;
			exit(1);
		}

	}//	while (1)

}//	void CRSPManager::Process()
//====================================================
//*
int CRSPManager::GetPlayerHand()
{
	return _human.GetHand();
}
//---------------------------------------
int CRSPManager::GetComHand()
{
	return _com.GetHand();
}
//*/
//====================================================