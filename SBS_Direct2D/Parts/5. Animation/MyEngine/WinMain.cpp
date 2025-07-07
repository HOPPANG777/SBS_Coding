//================================================
#include "Global.h"
//================================================
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	CMyGame	myGAme;

	g_pMyGame = &myGAme;

	if (FAILED(myGAme.Create(hInst)))
		return -1;

	return myGAme.Run();
}
//================================================
/*
	Q)	텍스쳐 클래스를 확장하여
		애니메이션이 가능한 텍스쳐 클래스를 만듭니다.
*/
//================================================