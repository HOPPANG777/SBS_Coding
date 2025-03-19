//================================================
#pragma once
#pragma warning( disable : 4996 )
//================================================
#include<iostream>
using namespace std;
//================================================
class CAnimal
{
protected:
	char _szName[30];

public:
	CAnimal(char* pszName) { strcpy(_szName, pszName); }
	const char* GetName() { return _szName; }
	virtual void MakeVoice() = 0;		// 순수 가상함수.
};
//================================================
class CCat : public CAnimal
{
public:
	CCat(char *pszName) : CAnimal(pszName) {}
	virtual void MakeVoice() { cout << "Meow" << endl; }
};
//================================================
class CDog : public CAnimal
{
public:
	CDog(char *pszName) : CAnimal(pszName) {}
	virtual void MakeVoice() { cout << "BowWow" << endl; }
};
//================================================
class CRooster : public CAnimal
{
public:
	CRooster(char *pszName) : CAnimal(pszName) {}
	virtual void MakeVoice() { cout << "Cock-a-doodle-doo" << endl; }
};
//================================================