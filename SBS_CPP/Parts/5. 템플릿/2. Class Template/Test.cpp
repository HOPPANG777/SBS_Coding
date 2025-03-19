//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	클래스 템플릿
	---------------

		-	형식

			template< typename Type >  class  클래스_이름
			--> ( typename 대신 class도 가능 )
			{
				....
			};
*/
//=================================================
/*
class CDataInt
{
	int _data;
public:
	CDataInt(int d) { _data = d; }
	void SetData(int d) { _data = d;  }
	int GetData() { return _data; }
};


class CDataDouble
{
	double _data;
public:
	CDataDouble(double d) { _data = d; }
	void SetData(double d) { _data = d; }
	double GetData() { return _data; }
};

int main()
{
	CDataInt d1(0);
	d1.SetData(10);

	CDataDouble d2(100.5);

	cout << d1.GetData() << endl;
	cout << d2.GetData() << endl;
	
	return 0;
}
//*/
//=================================================
/*	위 소스를 템플릿화.
template <typename T>
class CData
{
	 T _data;

public:
	CData(T d) { _data = d; }
	void SetData(T d) { _data = d; }
	T GetData() { return _data; }
};


int main()
{
	CData<int> d1(0);
	d1.SetData(10);

	CData<double> d2(100.5);
	d2.SetData(30.3);

	cout << d1.GetData() << endl;
	cout << d2.GetData() << endl;

	return 0;
}
//*/
//=================================================
/*
	함수 템플릿과는 달리
	클래스 템플릿을 기반으로
	객체 생성시
	자료형을 명시적으로
	선언해줘야 함..

	-	이유

		-	일반적인 객체 생성시..

			1)	메모리 공간 할당..
				-	멤버변수나
					내부 구조를 참고하여
					메모리 공간 할당..

			2)	생성자 호출..


		-	클래스 템플릿으로
			객체 생성시 발생하는 문제..

			-	메모리 공간 할당시
				최소 한개의 멤버변수의 타입을
				알수 없으므로 에러 발생..
				-	클래스의
					객체 생성방식으로 인해
					[ 생성자 ]를 통해서
					[ T의 타입 ]에 대한 정보를
					전달할 수밖에 없음..
					-	[ 메모리 공간의 할당 ]이
						[ 생성자 ] 호출보다 먼저 발생..
						->	[ T의 자료형 ]을
							[ 메모리 공간의 할당 ] 이전에
							명시적으로 알려줘야 함..

*/
//=================================================
/*
	---------------------------------------
	2.	클래스 템플릿의 선언과
		정의의 분리..
	---------------------------------------
*/
//=================================================
//*
template <typename T>
class CData
{
	T _data;

public:
	CData(T d);
	void SetData(T d);
	T GetData();
};

template <typename T>
CData<T>::CData(T d)
{
	_data = d;
}

template <typename T>
void CData<T>::SetData(T d)
{
	_data = d;
}

template <typename T>
T CData<T>::GetData()
{
	return _data;
}

//*/

/*
	1)	CData<T>::
		-	" T 타입에 대해
			  템플릿으로 정의되어 있는
			  CData 클래스 템플릿 "

	2)	template <typename T>
		-	클래스 선언부에서
			이미 선언후
			계속 중복 선언..
		-	멤버 함수를
			정의할 때마다
			반드시 붙여줘야함..

	-	템플릿 클래스의
		선언과 정의를
		하나의 파일에서
		( 주로 *.h )
		해줘야 함..
		-	분리된 파일의
			연관관계를 찾아주는 것은
			링커의 역할..
		-	템플릿은
			컴파일러에 의해 처리됨..
		-	빌드 순서상
			컴파일이 먼저 처리됨..
			-	[ 참고 : [ 1. C언어 소개 ] > [ C언어를 시작하기 전에.txt ] > [ 3. 빌드 과정 ] ]
		
*/
//=================================================
/*
	Quiz)	다음 스택 클래스를 템플릿화 한다.

		스택

		-	자료구조의 일종

		-	LIFO( Last Input, First Out ) / FILO( First Input, Last Out )

		-	push
			-	데이터 저장

			pop
			-	데이터 꺼내기

*/

/*
class CStack
{
	int _topIdx;
	char* _pStack;
	
public:
	CStack(int size = 10);
	~CStack();
	void Push(const char value);
	char Pop();
};

CStack::CStack(int size)
{
	_topIdx = -1;
	_pStack = new char[size];
}

CStack::~CStack()
{
	delete[] _pStack;
	_pStack = NULL;
}

void CStack::Push(const char value)
{
	_pStack[++_topIdx] = value;
}

char CStack::Pop()
{
	return _pStack[_topIdx--];
}

int main()
{
	CStack tmpStack(10);

	tmpStack.Push('a');
	tmpStack.Push('b');
	tmpStack.Push('c');

	for (int i = 0; i < 3; ++i)
		cout << tmpStack.Pop() << endl;

	return 0;
}
//*/

/*
int main()
{
	CStack< char > stackChar(10);
	stackChar.Push('a');
	stackChar.Push('b');
	stackChar.Push('c');


	CStack< int > stackInt(10);
	stackChar.Push(10);
	stackChar.Push(20);
	stackChar.Push(30);


	........

	return 0;
}
*/
//=================================================