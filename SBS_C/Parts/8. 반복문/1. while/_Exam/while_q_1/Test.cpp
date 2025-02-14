//======================================================
#pragma warning (disable : 4996)

#define _CPP_STYLE_

#ifdef _CPP_STYLE_
#include <iostream>
using namespace std;
#else
#include <stdio.h>
#endif
//======================================================
int main(void)
{
	int num = 0;

#ifdef _CPP_STYLE_
	cout << "-- 숫자를 입력하세요 : " << endl;
	cin >> num;
#else
	printf("-- 숫자를 입력하세요 : ");
	scanf("%d", &num);
#endif
	
	int count = 1;

	while (count <= 9)
	{
#ifdef _CPP_STYLE_
		cout << num << " x " << count << " = " << num * count << endl;
#else
		printf("%d x %d = %d\n", num, count, num * count );
#endif	
		++count;

	}//	while (count <= 9)

	return 0;
}
//======================================================