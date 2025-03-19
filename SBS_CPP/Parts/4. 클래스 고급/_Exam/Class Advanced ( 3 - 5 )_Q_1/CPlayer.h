#pragma once
class CPlayer
{
protected :
	int _myHand;

public :
	CPlayer() { _myHand = 0; }
	virtual int GetHand();
};

