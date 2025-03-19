//=============================================
#include "CComputer.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
//=============================================
int CComputer::GetHand()
{
	srand(time(0));
	_myHand = rand() % 3 + 1;
	return _myHand;
}
//=============================================
