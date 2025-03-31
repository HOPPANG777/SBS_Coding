#include<iostream>
#pragma warning( disable : 4996 )
using namespace std;

class CPerson
{
	int _age;
	char _szName[20];

public:
	CPerson(char *pszName = "None", int age = 1)
	{
		strcpy(_szName, pszName);
		_age = age;		
	}

	int GetAge() { return _age; }
	char* GetName() { return _szName; }
	//*
	void ShowData()
	{
		cout << "이름 : " << GetName() << endl;
		cout << "나이 : " << GetAge() << endl;
	}
	//*/
};

class CStudent : public CPerson
{
	char _szMajor[30];

public:	
	CStudent(char* pszMajor) { strcpy(_szMajor, pszMajor); }
	CStudent(char *pszName, char* pszMajor, int age = 1) : CPerson( pszName, age )
	{ strcpy(_szMajor, pszMajor); }
	char* GetMajor() { return _szMajor; }

	void ShowData()
	{
		CPerson::ShowData();

		//cout << "이름 : " << GetName() << endl;
		//cout << "나이 : " << GetAge() << endl;
		cout << "전공 : " << GetMajor() << endl;
	}
};

int main()
{
	CStudent Kim("홍길동","국어",20);
	Kim.ShowData();

	return 0;
}