#include<iostream>
using namespace std;

class CPoint
{
	float _x, _y;
public:
	CPoint(float x = 0, float y = 0) { _x = x, _y = y; }

	CPoint operator + (int val)
	{
		CPoint tmp(_x + val, _y + val);
		return tmp;
	}

	CPoint operator - (int val)
	{
		CPoint tmp(_x - val, _y - val);
		return tmp;
	}

	CPoint operator * (int val)
	{
		CPoint tmp(_x * val, _y * val);
		return tmp;
	}

	CPoint operator / (float val)
	{
		CPoint tmp(_x / val, _y / val);
		return tmp;
	}

	CPoint operator + (CPoint val)
	{
		CPoint tmp(_x + val._x, _y + val._y);
		return tmp;
	}
	void ShowData() { cout << _x << " " << _y << endl; }
};

int main()
{
	CPoint pt(1, 2);
	//CPoint tmp = pt.operator+(10);
	CPoint tmp = pt + 10;
	tmp.ShowData();

	tmp = pt - 5;
	tmp.ShowData();

	tmp = pt * 10;
	tmp.ShowData();

	tmp = pt / 2;
	tmp.ShowData();

	CPoint pt2(2, 3);
	CPoint pt3 = pt + pt2;
	pt3.ShowData();

	return 0;
}