//=============================================================
#pragma once
//=============================================================
//	전방 선언
//	-	참고 : https://ju3un.github.io/c++-forward-declaration/
class CWorker;
enum
{
	REGULAR,
	DAILY,
	PARTTIME
};
//=============================================================
class CWorkerFactory { 
public :
	CWorker* Create( int type, char* pszName );
};
//=============================================================