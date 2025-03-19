//==========================================
#pragma once
#ifndef _CCOMPUTER_H_
#define _CCOMPUTER_H_
//==========================================
class CComputer
{
	int _myHand;

public:
	CComputer() { _myHand = 0; }
	int GetHand();
};
//==========================================
#endif