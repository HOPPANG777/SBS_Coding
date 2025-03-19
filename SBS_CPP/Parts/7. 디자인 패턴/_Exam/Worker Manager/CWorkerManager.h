//=============================================================
#pragma once
#include<iostream>
#include<list>
#include "CWorker.h"
#include "CWorkerFactory.h"
//=============================================================
enum
{
	ADD = 1,
	DELETE,
	DELETEALL,
	SHOW,
	SHOWALL,
	EDIT,
	FINISH
};
typedef list<CWorker*>::iterator ITER_WORKER;
//=============================================================
class CWorkerManager
{
	//	메모리를 좀더 절약하기 위해 포인터를 사용..

	list<CWorker*> _list;
	int _select;
	CWorkerFactory* _pFactory;

	//	실제 데이터에 추가, 삭제, 조회 기능을하는 함수들..
	void AddData(CWorker* pPerson);
	bool DeleteData(char* pszName);
	bool DeleteAllData();
	bool ShowData(char* pszName);
	bool ShowAllData();
	bool EditData(char* pszName);

	//	실제 데이터 처리를 위한 래퍼( Wrapper ) 함수들..
	void Add();
	void Delete();
	void DeleteAll();
	void Show();
	void ShowAll();
	void Edit();

	//	데이터 처리와 상관없지만 시퀀스 처리를 담당하는 함수들..
	void ShowMenu();	//	메뉴 보여주기..	
	void Finish();		//	프로그램 종료..
	void DoError();		//	잘못된 입력 처리..

public:
	CWorkerManager() { 
		_select = 0;
		_pFactory = new CWorkerFactory();
	}
	~CWorkerManager();
	void Process();		//	전체 프로세스 처리..
};
//=============================================================