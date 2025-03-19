//==========================================
#pragma once
#ifndef _CCOMPUTER_H_
#define _CCOMPUTER_H_
//==========================================
#include "CPlayer.h"
class CComputer : public CPlayer
{
public:
	CComputer() {}
	int GetHand();
};
//==========================================
#endif