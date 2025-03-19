//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//  [ 참고 : https://twpower.github.io/91-how-to-use-map-in-cpp ]
//=================================================
/*
	---------------
	1.	Map
	---------------

		-	연관 컨테이너..
		-	배열형식이 아닌
			이진 탐색 트리 구조 기반..
			-	레드 블랙 트리
				-	자가 균형 이진 트리..
			-	https://www.fun-coding.org/DS&AL4-9.html
		-	Key / Value 로 이루어짐..
		-	키 값의 중복을 불허..
			-	multimap은
				키의 중복을 허가..
		-	자료가 삽입이 되면
			자동으로 정렬 됨..
		-	키 값으로
			문자열 사용 가능..

*/
//=================================================
//*
#include<map>
#include<string>
int main()
{
	map<int, string> m;

	m.insert(pair<int, string>(40, "me"));
	m.insert(pair<int, string>(35, "Show"));
	m.insert(pair<int, string>(10, "Dok2"));
	m.insert(pair<int, string>(90, "6"));
	m.insert(pair<int, string>(65, "money"));
	m.insert(pair<int, string>(20, "ZICO"));
	m.insert(pair<int, string>(50, "the"));
	
	map<int, string>::iterator iterCur;

	//	접근방법 1 
	cout << "접근방법 1" << endl;
	for (iterCur = m.begin(); iterCur != m.end(); ++iterCur) {
		cout << "[" << iterCur->first << ", " << iterCur->second << "]" << " ";
	}
    cout << endl << "-----------------------------------------------------------------" << endl;

	//	접근방법 2 
	cout << "접근방법 2" << endl;
	for (iterCur = m.begin(); iterCur != m.end(); ++iterCur) {
		cout << "[" << (*iterCur).first << ", " << (*iterCur).second << "]" << " ";
	}
    cout << endl << "-----------------------------------------------------------------" << endl;

	//	검색.
	cout << "검색" << endl;
	if (m.find(30) != m.end())
		cout << m[30] << endl;
	else
		cout << "데이터가 없습니다." << endl;
	cout << endl << "-----------------------------------------------------------------" << endl;

    //  편집.
	cout << "편집" << endl;
    m[20] = "SeoTaiji";
    for (iterCur = m.begin(); iterCur != m.end(); ++iterCur) {
        cout << "[" << (*iterCur).first << ", " << (*iterCur).second << "]" << " ";
    }
    cout << endl << "-----------------------------------------------------------------" << endl;

    //  삭제.
	cout << "삭제" << endl;
    m.erase(10);
    for (iterCur = m.begin(); iterCur != m.end(); ++iterCur) {
        cout << "[" << (*iterCur).first << ", " << (*iterCur).second << "]" << " ";
    }
    cout << endl << "-----------------------------------------------------------------" << endl;


	return 0;

}//	int main()
//*/
//=================================================
/*
	Quiz)	vector로 구현했던
			주소록 관리 프로그램을
			map으로 만든다..

			등록, 편집,
			조회 / 전체 조회,
			삭제 / 전체 삭제 기능만
			적용..

			이름을 키값으로 사용..( string 사용 )

			등록시 같은 이름이 존재한다면
			중복 가입이 안되도록 한다..
            
*/
//=================================================