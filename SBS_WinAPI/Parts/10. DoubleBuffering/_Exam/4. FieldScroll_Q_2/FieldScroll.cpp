//======================================================
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include "resource.h"

#include "CFighter.h"
#include "CEnemyManager.h"
#include "CDrawManager.h"
//======================================================
LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);
HINSTANCE g_hInst;
HWND g_hWndMain;
LPCTSTR lpszClass=TEXT("FieldScroll");
//======================================================
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance
					 ,LPSTR lpszCmdParam,int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst=hInstance;
	
	WndClass.cbClsExtra=0;
	WndClass.cbWndExtra=0;
	WndClass.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	WndClass.hCursor=LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance=hInstance;
	WndClass.lpfnWndProc=WndProc;
	WndClass.lpszClassName=lpszClass;
	WndClass.lpszMenuName=NULL;
	WndClass.style=CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);
	
	hWnd=CreateWindow(lpszClass,lpszClass,WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,CW_USEDEFAULT,1000,480,
		NULL,(HMENU)NULL,hInstance,NULL);
	ShowWindow(hWnd,nCmdShow);
	
	while (GetMessage(&Message,NULL,0,0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
//======================================================
int srcX = 0;

CBitMap*	g_pBGBitmap;
CFighter*	g_pPlayer;
CEnemyManager* g_pEnemyManager;
CDrawManager *g_pDrawManager;
//======================================================
LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
{
	int destWidth;
	HDC hMemDC;	
	
	switch (iMessage)
	{
		case WM_CREATE:

			//	플레이어 생성..
			g_pPlayer = new CFighter(hWnd, g_hInst, IDB_BABY, 100, 100, 3);
			g_pPlayer->SetBulletBmID(IDB_TOILET);
			g_pPlayer->Create();

			//	적 생성..
			g_pEnemyManager = new CEnemyManager();
			g_pEnemyManager->Create(hWnd, g_hInst, g_pPlayer);
			g_pPlayer->SetTargets(g_pEnemyManager->GetEnemies(), g_pEnemyManager->GetEnemyCount());

			//	배경 생성..
			g_pBGBitmap = new CBitMap(hWnd, g_hInst);
			g_pBGBitmap->Load(IDB_FIELD);
		
			//	그래픽 출력 관리..
			g_pDrawManager = new CDrawManager(1000, 480);
			g_hWndMain = hWnd;

			//	타이머 생성..
			//	ID : 1	-	플레이어, 적 정보, 배경 스크롤 관리..
			SetTimer(hWnd, 1, 50, NULL);

			//	ID : 2	-	적 생성 관리..
			SetTimer(hWnd, 2, ENEMYSPAWNTIME, NULL);
			return 0;

		case WM_TIMER:
			switch (wParam)
			{
			case 1:
				{
					//	플레이어 정보 갱신.	
					g_pPlayer->OnUpdate();
				
					//	적 정보 갱신.
					g_pEnemyManager->OnUpdate();

					//	배경 스크롤..
					srcX += 30;
					if (srcX > 2048) srcX = 0;

					InvalidateRect(hWnd, NULL, FALSE);
				}
				break;

			case 2:
				//	2초마다 적 생성.
				g_pEnemyManager->Spawn();
				break;

			}		
			return 0;
	
		case WM_PAINT:
			hMemDC = g_pDrawManager->BeginDraw(hWnd);

			//	배경 애니 적용.
			destWidth = min(2048 - srcX, 1000);
			g_pBGBitmap->DrawForDBuff(hMemDC, 0, 0, destWidth, 480, srcX, 0);
			if (destWidth < 1000)
				g_pBGBitmap->DrawForDBuff(hMemDC, destWidth, 0, 1000 - destWidth, 480, 0, 0);
				
			//	플레이어 그리기.
			g_pPlayer->OnRender(hMemDC);

			//	적 그리기.
			g_pEnemyManager->OnRender(hMemDC);
		
			g_pDrawManager->EndDraw(hWnd);
			return 0;

		case WM_DESTROY:

			delete g_pPlayer;
			g_pPlayer = NULL;

			delete g_pEnemyManager;
			g_pEnemyManager = NULL;

			delete g_pBGBitmap;		
			delete g_pDrawManager;

			PostQuitMessage(0);
			return 0;

	}//	switch (iMessage)

	return(DefWindowProc(hWnd,iMessage,wParam,lParam));

}//	LRESULT CALLBACK WndProc(HWND hWnd,UINT iMessage,WPARAM wParam,LPARAM lParam)
//======================================================