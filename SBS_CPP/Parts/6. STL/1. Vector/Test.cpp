//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	------------
	1.	Vector..
	------------

		-	순차 컨테이너..

		-	배열 형식..

		-	임의 접근이 가능..
		
			ㄴ	[]..

		-	삽입, 삭제가 빈번한 경우에는
			비추..
			
			-	삽입, 삭제 후 자리 재정렬에
				다소의 시간 소요..

		-	reserve 함수로 크기를
			미리 할당 가능..
			
		-	#include< vector > 선언..

*/
//=================================================
#include<vector>
//*	참고 : 스택..
#include<stack>
//*/
//=================================================
int main()
{
	/*
	vector<int> vec;
	
	//----------------------------------------
	//	벡터의 크기와 할당된 메모리 용량..
	//	ㄴ	size		:	실제 데이터가 들어가 있는
	//						공간의 크기..
	//	ㄴ	capacity	:	해당 컨테이너에 할당된 용량..
	// 
	//	ㄴ	[ size ]가 일정 [ capacity ]를
	//		넘어서게 되면 [ capacity ]를
	//		증가시킴..
	cout << "[" << vec.size() << " , " << vec.capacity() << "]" << endl;



	//----------------------------------------
	//	추가..
	vec.push_back(1);
	cout << "[ size : " << vec.size() << " , capacity :  " << vec.capacity() << " ]" << endl;
	vec.push_back(2);
	cout << "[ size : " << vec.size() << " , capacity :  " << vec.capacity() << " ]" << endl;
	vec.push_back(3);
	cout << "[ size : " << vec.size() << " , capacity :  " << vec.capacity() << " ]" << endl;
	vec.push_back(4);
	cout << "[ size : " << vec.size() << " , capacity :  " << vec.capacity() << " ]" << endl;
	vec.push_back(5);
	cout << "[ size : " << vec.size() << " , capacity :  " << vec.capacity() << " ]" << endl;



	//----------------------------------------
	//	요소 접근 - 1..
	cout << "--- 요소 접근 ( 배열 인덱스 )---" << endl;
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << endl;

	//	요소 접근 - 2..
	cout << "--- 요소 접근 ( 이터레이터 )---" << endl;
	vector<int>::iterator iterBegin = vec.begin();
	vector<int>::iterator iterEnd = vec.end();
	vector<int>::iterator iterCur;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
		cout << (*iterCur) << endl;



	//----------------------------------------
	//	요소 삭제..
	cout << "--- 요소 삭제 ---" << endl;
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
	{
		if ((*iterCur) == 2)
		{
			vec.erase( iterCur );
			break;
		}
	}
	iterBegin = vec.begin();
	iterEnd = vec.end();
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
		cout << (*iterCur) << endl;



	//----------------------------------------
	//	전체 삭제..
	cout << "--- 전체 삭제 ---" << endl;
	vec.clear();
	iterBegin = vec.begin();
	iterEnd = vec.end();
	for (iterCur = iterBegin; iterCur != iterEnd; ++iterCur)
		cout << (*iterCur) << endl;



	//----------------------------------------
	//	capacity 참고..
	cout << "--- data size capacity ---" << endl;
	vec.reserve(20);	//	크기를 미리 할당..
	for (int i = 0; i <= 60; i++) {
		vec.push_back(i + 1);
		cout << "[ " << vec[i] << " [ size : " << vec.size() << " , capacity :  " << vec.capacity() << " ] ]" << endl;
	}
	//*/



	//----------------------------------------
	/*	참고 : 스택..
	stack<int> st;
	st.push(23);
	st.push(1);
	st.push(3);

	while( st.empty() == false )
	{
		cout << st.top() << endl;
		st.pop();
	}
	//*/


	return 0;

}//	int main()
//=================================================
/*
	Quiz)	주소록 관리 프로그램을
			vector로 만든다..

			이름, 나이, 주소,
			전화 번호를 관리..

			등록, 편집,
			조회 / 전체 조회,
			삭제 / 전체 삭제 기능만
			적용..
*/
//=================================================