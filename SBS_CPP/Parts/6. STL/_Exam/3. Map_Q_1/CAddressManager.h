//=================================================
#pragma once
using namespace std;
#include<iostream>
#include<map>
#include"CPerson.h"
//=================================================
typedef map<string, CPerson*> MapPerson;
typedef MapPerson::iterator ITER_CPERSON;
//=================================================
enum
{
	ADD = 1,
	DELETE,
	DELETEALL,
	SHOW,
	SHOWALL,
	FINISH
};
//=================================================
class CAddressManager
{
	MapPerson _list;
	int _select;

public:
	CAddressManager() { _select = 0; }
	~CAddressManager();
	//	실제 데이터에 추가, 삭제, 조회 기능을하는 함수들..
	void AddData(CPerson* pPerson);
	bool DeleteData(char* pszName);
	bool DeleteAllData();
	bool ShowData(char* pszName);
	bool ShowAllData();

	//	실제 데이터 처리를 위한 래퍼( Wrapper ) 함수들..
	void Add();
	void Delete();
	void DeleteAll();
	void Show();
	void ShowAll();

	//	데이터 처리와 상관없지만 시퀀스 처리를 담당하는 함수들..
	void ShowMenu();	//	메뉴 보여주기..
	void Process();		//	전체 프로세스 처리..
	void Finish();		//	프로그램 종료..
	void DoError();		//	잘못된 입력 처리..
};

