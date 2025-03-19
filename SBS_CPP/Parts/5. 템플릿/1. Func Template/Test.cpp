//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
/*
	---------------
	1.	템플릿
	---------------

		-	[ Template ]
			-	형판, 견본, 본보기..

		-	삼각 모형자 비유..
			-	삼각형을 그릴 수 있는
				틀이 준비되어 있다고 가정..
			-	어떤 색의 필기구를
				사용하느냐에 따라
				삼각형의 색이 결정 됨..

		-	삼각 모형자 개념을
			프로그래밍에 비유..
			-	틀은 준비되어 있지만
				색이 정해져 있지 않음..
				->	[ 로직 ]은 정해져 있지만
					[ 자료형 ]은 정해져 있지 않음..

			-	삼각형 틀..
				-	[ 기능 ], [ 역할 ], 
					[ 로직 ], [ 알고리즘 ]
				색연필..
				-	[ 데이터 ]
				색..
				-	[ 데이터 타입 ]

	------------------------------
	2.	템플릿의 선언 및 사용
	------------------------------

		-	선언

			0)	int     Add( int a, int b )           { return a + b; }
				float   Add( float a, float b )       { return a + b; }
				double  Add( double a, double b )     { return a + b; }
				byte	Add( byte a, byte b )		  { return a + b; }
				....
				-	Add 함수의 타입만 다를 뿐
					알고리즘은 같으니
					타입에 상관없이 사용..
					-	[ 템플릿 ] 적용..
			
			1)	____ Add(___ a, ___ b) { return a + b; }
				-	타입을 공란으로 처리..

			2)	[ 데이터 타입 ]을
				[ T ]로 치환..
				-	T Add(T a, T b) { return a + b; }

			3)	[ 컴파일러 ]는
				[ T ] 라는 자료형을
				인식 못하므로
				[ template ] 또는
				[ class ] 키워드를
				사용하여
				[ 템플릿 타입 ]임을 명시..

				-	template< typename T >  T Add(T a, T b) { return a + b; }
                -   template< class T >     T Add(T a, T b) { return a + b; }

		-	사용..
				template< typename T >
				T Add(T a, T b) { return a + b; }

				int main()
				{
					cout << Add(1, 3) << endl;
					->	T Add(T a, T b) { return a + b; }
						--> int Add(int a, int b) { return a + b; }

					cout << Add(1.1f, 3.2f) << endl;
					->	T Add(T a, T b) { return a + b; }
						--> float Add(float a, float b) { return a + b; }
					return 0;

				}

			->	템플릿으로 정의된
				함수의 자료형이
				결정되는 시점..
				-	인자가 전달되는 시점..
*/
//=================================================
/*
//	함수 템플릿.
template < typename T >
T Add(T a, T b) { return a + b; }

int main()
{
	//	템플릿 함수.
	cout << Add(10, 20) << endl;	//	템플릿으로 정의된
									//	함수의 자료형이
									//	결정되는 시점!!
	cout << Add(1.1f, 2.2f) << endl;	
		
	return 0;
}
//*/
//=================================================
/*
	-----------------------------------
	3.	둘 이상의 타입에 대한 템플릿화.
	-----------------------------------

		-	위 템플릿 함수 Add를
			다음과 같이 호출..

				cout << Add(1, 2.2f) << endl;

			에러의 원인은???

		-	선언

			template < typename T1, typename T2 >
*/
//=================================================
/*
template < typename T1, typename T2 >
void ShowData(T1 a, T2 b)
{
	cout << a << endl;
	cout << b << endl;
}

template < typename T1, typename T2, typename T3 >
T3 Add( T1 a, T2 b )
{
	return a + b;
}

int main()
{	
	ShowData(1, 2);
	ShowData(1, 2.5f);
	
	//float res = Add( 2, 3.3 );
	//cout << res << endl;


	return 0;
}
//*/
//=================================================
/*
	-------------------------
	4.	함수 템플릿의 특수화..    
	-------------------------
		-	특정타입에 대해서
			구별된 기능을 적용하는 것..
            -   먼저 선언된
				기본형 함수 템플릿에 대한
				특수화..

        -   명시적(explicit),
			부분(partial) 특수화가 있음..
            -   템플릿 함수에서는
				명시적 특수화만 가능..

		-	[ template<> ]으로 재정의..

        -   컴파일러는 먼저
			적절한 기본 템플릿을 선택하고 
			그런 후에 그 템플릿에 대한
			적절한 특수화가 존재한다면
			그 특수화를 선택..
            -   특수화는 오버로딩 되지 않음..
            -   함수 템플릿을
				특수화하지 말아야한다는
				의견도 있음..
                ( 출처 : Exceptional C++ Style )
*/
//=================================================
/*
	[ 함수 템플릿 ]은
	[ 템플릿이 아닌 함수 ]와
	[ 오버로딩 ] 가능..
	-   이때 [ 템플릿이 아닌 함수 ]가 선호됨.
*/
//------------------------------------------------
//  case 1
//------------------------------------------------
/*
	1)	적절한 기본 템플릿을 선택..
	2)	그 템플릿에 대한
		적절한 특수화가
		존재하는지 체크..
	3)	존재하면 그 특수화를 선택.
*/
/*
//  a)  기본 템플릿.
template <typename T>
int GetSize(T a) { return sizeof(a); }

//  b)  a)의 오버로딩.
template <typename T>
int GetSize(T* a) { return sizeof(a) + 100; }

//  c)  b)의 명시적 특수화.
template<>
int GetSize(char* a) { return sizeof(a) + 5; }
//  result : 4   8   9
//*/
//------------------------------------------------
//  case 2
//------------------------------------------------
/*
//  a)  기본 템플릿.
template <typename T>
int GetSize(T a) { return sizeof(a); }

//  c)  a)의 명시적 특수화.
template<>
int GetSize(char* a) { return sizeof(a) + 5; }

//  b)  a)의 오버로딩.
template <typename T>
int GetSize(T* a) { return sizeof(a) + 100; }

//  result : 4   8   104
//*/
//------------------------------------------------
/*
	1)	적절한 기본 템플릿을 선택..
	2)	그 템플릿에 대한
		적절한 특수화가
		존재하는지 체크..
	3)	존재하면 그 특수화를 선택.
*/
/*
int main()
{
	int a = 10;
	double b = 2.2;
	char* pStr = "Hello";

	cout << GetSize(a) << endl;
	cout << GetSize(b) << endl;
	cout << GetSize(pStr) << endl;

	return 0;
}
//*/
//=================================================
/*
	Quiz)	사칙 연산 프로그램을 함수 템플릿으로 만든다.
*/
//=================================================
/*
	[ 참고 ]

		https://wikidocs.net/487
		https://wikidocs.net/652
		https://m.blog.naver.com/vjhh0712v/221553593414
		http://www.tcpschool.com/cpp/cpp_template_function
*/
//=================================================