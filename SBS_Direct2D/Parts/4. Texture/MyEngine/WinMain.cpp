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
	Q)	LPDIRECT3DTEXTURE9를 이용하며 다음과 같은 인터페이스를 제공하는
		클래스를 만듭니다.

		Create()	-	LPDIRECT3DTEXTURE9 객체 생성..
		Draw()		-	이미지 그리기..
		Destroy()	-	LPDIRECT3DTEXTURE9 객체 정리..
*/
//================================================