//=====================================================
/*
	레퍼런스와 함수..
		
		-	포인터 처럼 Call by Reference 구현 가능..
*/
//=====================================================
#include<iostream>
using namespace std;
//=====================================================
/*
void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
	int val1 = 10;
	int val2 = 20;

	cout << "--- before ---" << endl;
	cout << "val1 = " << val1 << endl;
	cout << "val2 = " << val2 << endl;

	Swap(val1, val2);

	cout << "--- after ---" << endl;
	cout << "val1 = " << val1 << endl;
	cout << "val2 = " << val2 << endl;

	return 0;
}
//*/
//=====================================================
/*
	레퍼런스를 이용한 성능 향상..
*/
//=====================================================
/*
typedef struct
{
	int _age;
	char _name[20];
	char _phoneNum[20];

} SPerson;


//	call by value 방식( 소스 파악 후 고찰할 것.. )
//	
//	-	매개변수 p에 값을 복사..
//	-	이 과정에서 복사되는 바이트의 수
//		= int(4byte) + char[20](20byte) + char[20](20byte) = 44byte.
void ShowInfo(SPerson p)

//	call by reference 방식(by 레퍼런스)
//
//		-	해당 변수에 이름만 하나 더
//			추가하는 방식이므로
//			값의 복사는 발생하지 않음..
//
//		-	하지만 함수 내부에서 여전히
//			레퍼런스를 변경할 가능성은 존재..
//
//			ㄴ	상수화를 통하여 해결 가능..

//void ShowInfo(SPerson &p)
//void ShowInfo(const SPerson &p)
{
	cout << "--- 개인 정보 ---" << endl;
	cout << "이름 : " << p._name << endl;
	cout << "전화번호 : " << p._phoneNum<< endl;
	cout << "나이 : " << p._age<< endl;
	//	앗!! 실수!!
	//cout << "나이 : " << p._age++ << endl;
}

int main()
{
	SPerson person;

	cout << "이름 : ";
	cin >> person._name;

	cout << "나이 : ";
	cin >> person._age;

	cout << "전화번호 : ";
	cin >> person._phoneNum;

	ShowInfo(person);
		
	cout << endl;
	cout << "나이 : " << person._age << endl;

	return 0;
}
//*/
//=====================================================
/*
	레퍼런스를 리턴하는 함수..
*/
//=====================================================
//	잘못된 형태..
//=====================================================
/*
int& Func(int val)
{
	val++;
	
	//	"지역 변수는 코드 블록과
	//	 수명을 함께한다!!!"
	//
	//	-	val은 Func함수의 종료와 함께
	//		메모리에서 사라짐..

	return val;
}

int main()
{
    int val1 = 10;

	//	ref라는 이름이 붙게 될
	//	메모리 공간이 사라져버림..
	int &ref = Func(val1);
	
	//	정상적으로 출력이 되었다 하더라도
	//	신뢰할 수 없는 값이 되버림..
	cout << ref << endl;

	return 0;
}
//*/
//=====================================================
//	적절한 형태..
//=====================================================
/*
int& Func(int& val);

int main()
{
	//	1]	val1 이라는
	//		메모리 공간 할당..
	int val1 = 10;
	int &ref = Func(val1);	//	4]	ref라는 이름이 추가..
	
	//cout << &val1 << "   " << &ref << endl;

	cout << "val1 = " << val1 << endl;
	cout << "ref = " << ref << endl;

	return 0;
}

int& Func(int& val)	//	2]	val1에 val이라는 이름이 추가됨..
{
	val++;
	return val;		//	3]	val이라는 이름이 사라짐..
					//	
					//		-	메모리 공간이 사라지는 것은 아님..
}
//*/
//=====================================================
/*

	[ 참고 ]

		[C++] 레퍼런스 함수 정리
		https://underground2.tistory.com/151
*/

//=====================================================



