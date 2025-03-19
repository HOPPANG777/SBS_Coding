//======================================================
#pragma once
#include<iostream>
#include"CHuman.h"
#include"CComputer.h"
#include"CPlayer.h"
//======================================================
const int SCISSOR = 1;
const int ROCK = 2;
const int PAPER = 3;
const int FINISH = 4;

const int WIN = 0;
const int LOSE = 1;
const int DRAW = 2;
//======================================================
class CRSPManager
{
	int _winCount;
	int _loseCount;
	int _drawCount;
	char _szHand[20];
	char* GetHandToString(int card);

	void ShowMenu();
	//int GetPlayerHand();
	//int GetComHand();
	int GetResult(int player, int cpu);
	void ShowResult(int player, int cpu, int result);

	CPlayer* _players[2];
	CHuman _human;
	CComputer _com;
	
public:
	CRSPManager()
	{
		_winCount = 0;
		_loseCount = 0;
		_drawCount = 0;
		_players[0] = &_human;
		_players[1] = &_com;
	}

	
	void Process();
};