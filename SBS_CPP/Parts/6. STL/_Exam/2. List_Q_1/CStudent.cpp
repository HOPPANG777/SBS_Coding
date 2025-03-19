//==================================================================
#pragma warning( disable : 4996 )
#include<iostream>
#include"CStudent.h"
using namespace std;
//==================================================================
CStudent::CStudent(char* pszName, int kor, int eng, int math)
{
	strcpy(_szName, pszName);
	_scores[KOR] = kor;
	_scores[ENG] = eng;
	_scores[MATH] = math;

	BuildScore();

}//	CStudent::CStudent(char* pszName, int kor, int eng, int math)
//----------------------------------
bool CStudent::SetScore(int idx, int score)
{
	if (KOR <= idx &&
		idx <= MATH)
	{
		_scores[idx] = score;
		BuildScore();
		return true;
	
	}//	if (KOR <= idx && ...

	return false;

}//	bool CStudent::SetScore(int idx, int score)
//----------------------------------
void CStudent::BuildScore()
{
	_scores[TOT] = 0;
	for (int curSubject = 0; curSubject < 3; ++curSubject)
		_scores[TOT] += _scores[curSubject];

	_avg = _scores[TOT] / 3.0f;

}//	void CStudent::BuildScore()
//----------------------------------
void CStudent::ShowInfo()
{
	cout << "이름 : " << _szName << endl;
	char* pszTitle[] = { "국어","영어","수학","총점","평균" };
	cout << "--------------------------------------" << endl;
	for (int cur = 0; cur < 5; ++cur)
		cout << pszTitle[cur] << '\t';
	cout << endl;

	for (int cur = 0; cur < 4; ++cur)
		cout << _scores[cur] << '\t';
	cout << _avg << '\t';

	cout << endl;
	cout << endl;
	
}//	void CStudent::ShowInfo()
//==================================================================