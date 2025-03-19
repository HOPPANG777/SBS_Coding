//========================================================
#include "CWorker.h"
#include "CWorkerFactory.h"
//========================================================
CWorker* CWorkerFactory::Create( int type, char* pszName )
{
	CWorker* pWorker  = NULL;
	switch (type)
	{
	case REGULAR: pWorker = new CRegularWorker(pszName); break;

	case DAILY: pWorker = new CDailyWorker(pszName); break;

	case PARTTIME: pWorker = new CPartimeWorker(pszName); break;
	}

	return pWorker;
}
//========================================================