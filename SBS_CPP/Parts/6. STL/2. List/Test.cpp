//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	----------
	1.	List..
	----------

		-	순차 컨테이너..


		-	이중 링크드 리스트 구조..

			ㄴ	https://m.blog.naver.com/justkukaro/220396848221


		-	삽입, 삭제가 빈번한 경우 추천..
			
			ㄴ	모든 컨테이너중 가장 빠름.


		-	임의 접근 반복자는 사용 불가..
			( at(), [].. )

*/
//=================================================
//*
#include<list>

bool IsRangeOK(int num) { return 100 <= num && num <= 200; }

int main()
{	
	list<int> lt;

	//	추가.
	lt.push_back(10);
	lt.push_back(20);
	lt.push_back(108);
	lt.push_back(60);
	lt.push_back(10);
	lt.push_back(100);
	lt.push_back(40);
	lt.push_back(50);
	lt.push_back(10);
	lt.push_back(109);
	lt.push_back(30);
	lt.push_back(220);
	lt.push_back(10);

	list<int>::iterator iterCur;

	cout << "--- 조회 ---" << endl;
	for (iterCur = lt.begin(); iterCur != lt.end(); iterCur++) cout << *iterCur << " ";
	cout << endl << endl;


	cout << "--- 조건부 삭제 1 ---" << endl;
	lt.remove_if(IsRangeOK);
	for (iterCur = lt.begin(); iterCur != lt.end(); iterCur++) cout << *iterCur << " ";
	cout << endl << endl;


	cout << "--- 조건부 삭제 2 ---" << endl;
	lt.remove(10);
	for (iterCur = lt.begin(); iterCur != lt.end(); iterCur++) cout << *iterCur << " ";
	cout << endl << endl;


	cout << "--- 정렬 ---" << endl;
	lt.sort();
	for (iterCur = lt.begin(); iterCur != lt.end(); iterCur++) cout << *iterCur << " ";
	cout << endl << endl;


	lt.clear();
	cout << "--- 전체 삭제 ---" << endl;
	for (iterCur = lt.begin(); iterCur != lt.end(); iterCur++) cout << *iterCur << " ";
	cout << endl << endl;


	return 0;

}//	int main()
//*/
//=================================================
/*
	Quiz)	성적 관리 프로그램을 list로 만듭니다.

			이름, 국, 영, 수, 총점, 평균을
			관리하도록 해주세요..

			등록, 편집,
			조회 / 전체 조회,
			삭제 / 전체 삭제 기능만
			적용..
*/
//=================================================