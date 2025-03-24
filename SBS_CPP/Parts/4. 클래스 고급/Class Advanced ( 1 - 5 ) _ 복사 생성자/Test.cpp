//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
//	클래스 (고급)
//	
//	[1 - 5]	복사 생성자..
//=================================================
/* 
	1.	변수의 초기화..

		-	int a = 10;

			int a(10);

			->	c++에선 모두 가능..

		-	객체의 초기화도
			같은 방법으로 가능할까???
*/
//=================================================
/*
class CTest
{
	int _x;

public:
	CTest( int a ) { _x = a; }
	
	void ShowData() { cout << _x << endl; }
};
int main()
{
	//int a = 10;
	int a(10);
	cout << a << endl;

	CTest _test1(10);
	_test1.ShowData();

	CTest _test2 = 20;	//	->	CTest _test2(10)으로
						//		묵시적 형변환..
	_test2.ShowData();

	CTest _test3 = _test2;
	//CTest _test3(_test2);
	_test3.ShowData();

	return 0;
}
//*/
//=================================================
/*
	2.	복사 생성자의 형태..

		-	복사 생성자..

			ㄴ	자신과 같은 형태의 객체를
						( 자료형 )
				인자로 받을수 있는 생성자..


			ㄴ	생성자( const 클래스타입& 매개변수이름 )

				ㄴ	const..

					ㄴ	생성자 안에서 매개 변수의 
									( 객체 )
						내용 변경을 허용치 않음..

					ㄴ	레퍼런스 타입이므로
						상수화 하지 않으면 생성자 내부에서
						외부로부터 전달된 데이터를
						수정할 수 있음..
						

				ㄴ	&..
					(레퍼런스)

					ㄴ	레퍼런스로 받지 않으면
						무한루프에 빠지게 됨..

						예)
							A b;
							A a = b;
							
							-	A 클래스가 참조가 아닌
								값으로 전달 받는 복사 생성자를
								정의한 클래스라면..

								예)	class A
									{
										public:
											A( A a );				-	( X )
											->	A( const A& a );	-	( O )
									}


									1)	A의 생성자가 호출..
										->	A( A a ) 호출 시도!!

									2)	1)의 생성자의 매개변수에
										b 대입 시도..
										->	A( A a = b );

									3)	매개변수 a의 생성자 호출..
										->	매개변수 a의 A( A a );

									4)	3)생성자의 매개변수에
										b 대입 시도..
										->	A( A a = b );

									5)	매개변수의 생성자 호출..

									6)	5)생성자의 매개변수에
										b 대입 시도..

									7)	.........

									-	다행히 컴파일러가
										에러로 처리해줌..
	*/
//=================================================
/*
class CTest
{
public:
	CTest()
	{
		cout << "-- CTest() --" << endl;
	}
	CTest(int a)
	{
		cout << "-- CTest(int a) --" << endl;
	}

	CTest(const CTest& test)
	//CTest(CTest test)
	{
		cout << "-- CTest(const CTest& test) --" << endl;
	}
};

int main()
{
	CTest test1;
	CTest test2(10);
	CTest test3(test2);

	return 0;
}
//*/
//=================================================
/*
	3 - 1.	디폴트 복사 생성자..
		
			-	디폴트 생성자..

				ㄴ	클래스에서 별도의 구현이 없으면
					컴파일러에 의해 자동으로
					삽입되는 생성자..

					예)	class CTest
						{
							public :
								CTest() {};
								~CTest() {};
						}


			-	복사 생성자도 따로 정의해주지 않으면
				기본적으로 컴파일러가 제공함..

			-	다른 디폴트 생성자 / 소멸자와 달리
				특정한 기능을 처리함..

			
			================================
							|	기능	
			================================
			디폴트 생성자..	|		X
			--------------------------------
			디폴트 소멸자	..	|		X
			--------------------------------
			디폴트			|	멤버 변수간의
			복사 생성자..	|	복사..
			================================

*/
//=================================================
/*
class CTest
{
	int _x, _y;

public:
	CTest(int x, int y)	{ _x = x,	_y = y; }
	
	CTest( const CTest& test )
	{
		_x = test._x;
		_y = test._y;
	}

	void ShowData()		{ cout << _x << " " << _y << endl; }
};


int main()
{
	CTest test1(10, 20);
	CTest test2(test1);

	test1.ShowData();
	test2.ShowData();

	return 0;
}
//*/
//=================================================
/*
	3 - 2.	디폴트 복사 생성자의
			문제점..

		-	얕은 복사..
			( Shallow Copy )

			ㄴ	객체가 가진 멤버들의 값을
				새로운 객체로 복사하려고 하는데
				만약 객체가 참조 타입의 멤버 변수를
							( 포인터형 )
				가지고 있다면 참조 값만 복사..
				( 주소 )


			<--->	깊은 복사..
					( Deep Copy )

					ㄴ	전체 복사..

					ㄴ	객체가 가진 모든 멤버를 복사..

						ㄴ	값과 참조형식 모두..
					
					ㄴ	객체가 참조 타입의 멤버를
						포함하는 경우, 참조값의 복사가 아닌
						참조된 객체 자체가 복사되는 것..

				출처: http://wonjayk.tistory.com/256

*/
//=================================================
//*
class CPersonInfo
{
	char* _pszName;
	char* _pszPhone;
	int _age;

public:
	CPersonInfo(char* pszName, char* pszPhone, int age)
	{
		_pszName = new char[strlen(pszName) + 1];
		_pszPhone = new char[strlen(pszPhone) + 1];

		strcpy(_pszName, pszName);
		strcpy(_pszPhone, pszPhone);
		_age = age;
	}

	//CPersonInfo( const CPersonInfo& test )
	//{
	//	_pszName = test._pszName;
	//	_pszPhone = test._pszPhone;
	//	_age = test._age;
	//}

	~CPersonInfo()
	{
		delete[] _pszName;
		delete[] _pszPhone;
	}

	void ShowData()
	{
		cout << _pszName << endl;
		cout << _pszPhone << endl;
		cout << _age << endl;
	}
};

int main()
{
	CPersonInfo Kim("Kim", "010xxxxxxxx", 20);
	CPersonInfo Kim2 = Kim;

	Kim.ShowData();
	Kim2.ShowData();

	return 0;

//	에러발생!!!!!
//		원인은 ? ? ? ?
}

//*/
//=================================================
/*
	Quiz)	위의 문제를 복사생성자와
			깊은 복사를 이용해서 해결한다..
*/
//=================================================
/*
	4.	복사 생성자의 호출 시점..
			
		=	복사가 진행되는 시점!!

		=	대입이 진행되는 시점!!



		1)	기존에 생성된 객체로
			새로운 객체를 초기화..

			예)	CTest test1;
				CTest test2 = test1;
				->	test2(test1); 묵시적 변환..



		2)	함수 호출시 객체를
			값에 의해 전달하는 경우..
			
			예)	
				void Func( CTest test )	{ .... }

				int main()
				{
					CTest _test;

					Func( _test );
					=>	CTest test = _test

					....
				}

				1)	매개 변수 test를 위한
					메모리 공간 할당..

				2)	test에 _test 복사..


		3)	함수 내에서 객체를
			값에 의해 리턴..


			예)	
				int GetValue()
				{
					int val = 10;
					.....
					return val;
				}

				int main()
				{
					cout<< GetValue()<<endl;
					....
				}

				1)	함수를 호출한 영역으로
					값이 복사되어 전달..

				2)	호출한 영역에서 리턴 타입으로
					묵시적 메모리 할당 발생..


				CTest Func()
				{
					CTest test(10);
					....
					return test;
				}

				int main()
				{
					CTest tmp = Func();
					....
				}
*/
//=================================================