//==========================================
#pragma once
#ifndef _CPLAYER_H_
#define _CPLAYER_H_
//==========================================
#include "CPlayer.h"
class CHuman : public CPlayer
{
public:
	CHuman() { }
	int GetHand();
};
//==========================================
#endif