#pragma once

enum
{
	KOR,
	ENG,
	MATH,
	TOT,

	SCORE_COUNT
};

class CStudent
{
	char _szName[50];
	int _scores[SCORE_COUNT];
	float _avg;
	void BuildScore();
public:
	CStudent(char* pszName, int kor, int eng, int math);
	bool SetScore(int idx, int score);
	
	void ShowInfo();
	char* GetName()		{ return _szName; }
};