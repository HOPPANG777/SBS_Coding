//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//  [ 참고 : https://twpower.github.io/91-how-to-use-map-in-cpp ]
//=================================================
//*
#include<map>
#include<string>
int main()
{
	//	[ 참고 1 ] 결과 비교...
	std::map<char*, int> mp;
	//std::map<string, int> mp;

    mp["abc"] = 1;
	mp["111"] = 2;

	cout << mp["abc"] << endl;
	cout << mp["111"] << endl;
	cout << endl;

	//	[ 참고 2 ]전체 요소에 미치는 영향은??
	cout << mp["123"] << endl;
	cout << endl;

	if (mp.count("abc") != 0)
		cout << "abc 있음!\n";

	if (mp.count("aaa") != 0)
		cout << "aaa 있음!\n";
	else
		cout << "aaa 없음!\n";

	cout << endl;

	//	[ 참고 1 ]
	std::map<char*, int>::iterator iter;
	//std::map<string, int>::iterator iter;
	for (iter = mp.begin(); iter != mp.end(); iter++)
		cout << (*iter).first << ": " << (iter->second) << endl;
    

	//	[ 참고 3 ]
	//	"aaa"는 동일한 메모리????
	//	참고 - https://gpgstudy.com/forum/viewtopic.php?t=25224
	//	cout << endl;
	//	char* ptmp1 = "aaa";
	//	char* ptmp2 = "aaa";
	//	printf("ptmp1 = %p    ptmp2 = %p\n", ptmp1, ptmp2);
    //  -   gpgstudy 발췌
    //      -   "aaa"와 같은 순수 문자열(?)은
	//			상수 메모리(?)에 먼저 등록되고
    //          그 주소값을 리턴하기 때문에
	//			ptmp1의 주소값과 ptmp2의 주소값이
	//			같은 것으로 됩니다

	return 0;
}
//*/
//=================================================