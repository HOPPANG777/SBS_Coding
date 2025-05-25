//==============================================
#include <windows.h>
#include "CObject.h"
#include "CView.h"
//==============================================
int WINAPI WinMain( HINSTANCE hInstance,HINSTANCE hPrevInstance, PSTR szCmdLine,int iCmdShow )
{
	g_pObject = &g_View;
    
	if (g_pObject->InitInstance( TEXT("CUSTOM MFC STEP 1"), hInstance, szCmdLine, iCmdShow) == true)
	{
		g_pObject->Run();

		return g_pObject->ExitInstance();
	}

	return 0;

}//	int WINAPI WinMain( HINSTANCE hInstance,HINSTANCE hPrevInstance, PSTR szCmdLine,int iCmdShow )
//==============================================