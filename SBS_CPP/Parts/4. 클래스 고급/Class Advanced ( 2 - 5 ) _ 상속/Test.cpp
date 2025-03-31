//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
//	클래스 (고급)
//	
//	[2 - 5]	상속 기본개념..
//=================================================
/* 
	1.	기본 개념..

		------------
		-	[ 상속 ]
		------------

			ㄴ	기존의 클래스를 이용해서
				새로운 클래스를 만드는 것..


			---------------------
			-	상속 되는 클래스..
			---------------------

				ㄴ	기존 클래스..

				ㄴ	Super, Base,
					부모, 상위 클래스 등..

			--------------------
			-	상속받는 클래스..
			--------------------

				ㄴ	새로 생성되는 클래스..

				ㄴ	Sub, Derived,
					자식, 하위 클래스 등..


		--------------
		-	기본 원리..
		--------------

			-	기존 클래스의 멤버를
				새로 정의하는 클래스의
				멤버로 포함..

			-	기존 클래스의 기능
				+ 새로운 기능..

*/
//=================================================
/*
class CPerson
{
	char _szName[20];
	int _age;

public:
	CPerson()
	{
		strcpy(_szName, "None");
		_age = 0;
	}

	char* GetName() { return _szName; }
	int GetAge()	{ return _age; }
};

class CStudent : public CPerson
{
	char _szMajor[30];

public :
	CStudent( const char* pszMajor ) { strcpy(_szMajor, pszMajor); }
	char* GetMajor() { return _szMajor; }

	void ShowData()
	{
		cout << "이름 : " << GetName() << endl;
		cout << "나이 : " << GetAge() << endl;
		cout << "전공 : " << GetMajor() << endl;
	}
};

int main()
{
	CStudent Kim("국어");
	Kim.ShowData();

	return 0;
}
//*/
/*
	소스 설명

	1)	class CStudent : public CPerson

		-	[ CStudent 클래스 ]가
			[ CPerson 클래스 ]를
			상속 받음..( public 상속 )


	2)	CStudent 클래스는
		CPerson에 있는 멤버를
		모두 포함..
*/

//=================================================
/*
	2.	자식 클래스의
		객체 생성 과정..


		1)	메모리 공간의 할당..

			ㄴ	부모 클래스를 고려해서 할당..


		2)	자식 클래스 생성자 호출..

			ㄴ	호출은 되지만 구현부가
				실행되진 않음..

			ㄴ	호출된 자식 클래스의 생성자에 대하여
				부모 클래스의 특정 생성자가
				호출 되어야 한다는 선언이 없다면
				부모 클래스의 [ 기본 생성자 ] 또는
				[ 유사 기본 생성자 ]가 호출 및 실행됨..

				-	부모 클래스의 특정 생성자를
					호출하려면 해당 생성자를
					명시적으로 호출..

					-	부모 생성자 호출..
						-	CChild( int a ) : CParent( a )

					-	[ 멤버 이니셜라이저 ]
						[ 참고	:	https://blog.naver.com/dd1587/221103760389
									https://rieulpost.tistory.com/53 ]
						방식)

							생성자 () : 멤버변수( 초기값 ),...
							{
								...
							}

						-	[ 멤버 이니셜라이저 ]를
							반드시 써야하는 경우..

							-	객체의 멤버 초기화..

							-	const 상수 멤버 초기화..

							-	레퍼런스 멤버 초기화..

							-	부모 클래스의 특정 생성자 호출..



		3)	부모 클래스 생성자 호출 및
			구현부 실행..

		4)	자식 클래스 생성자의
			구현부 실행..


		-	목적..

			ㄴ	객체가 생성될 때,
				부모 클래스의 생성자에서
				동적인 메모리를 생성할 기회 제공..
*/
//=================================================
/*
class CParent
{
	int _hp;
	int _attack;

public:

	CParent()
	{
		_hp = 0;
		_attack = 0;
		cout << "CParent() 호출" << endl;
	}

	CParent(int hp, int attack)
	{
		_hp = hp;
		_attack = attack;
		cout << "CParent(int hp, int attack) 호출" << endl;
	}

	void ShowData()
	{
		cout << "_hp : " << _hp << endl;
		cout << "_attack : " << _attack << endl;
	}

	int GetHP() { return _hp; }
	int GetAttack() { return _attack; }
};

class CChild : public CParent
{
	int _def;
	
public :
	CChild() {
		_def = 0;
		cout << "CChild() 호출" << endl;
	}
	//CChild(int a) { cout << "CChild(int a) 호출" << endl; }
	//	멤버 이니셜라이저..
	CChild( int hp, int attack, int def ) : CParent( hp, attack )
	{
		_def = def;
		cout << "CChild( int hp, int attack, int def ) 호출" << endl;
	}

	void ShowData()
	{
		cout << "_hp : " << GetHP() << endl;
		cout << "_attack : " << GetAttack() << endl;
		cout << "_def : " << _def << endl;
	}
};

int main()
{
	CChild child1;
	CChild child2(100, 10, 10);

	child1.ShowData();
	child2.ShowData();

	return 0;
}
//*/
//=================================================
/*
	Q 1)	위의 CStudent 예제가
			이름과 나이도 설정할 수 있도록 수정..

		예)
			CStudent Kim("김철수", 20, "국어");
			Kim.ShowData();

			실행)
				이름 : 김철수
				나이 : 20
				전공 : 국어

*/
//=================================================
/*
	3.	객체 소멸 과정..

		-	자식 클래스의 소멸자가 호출된 뒤,
			부모 클래스의 소멸자가 호출 됨..

			ㄴ	자식 클래스는 부모 클래스의
				소멸자까지 호출..

			ㄴ	목적..
			
				ㄴ	객체가 소멸될 때,
					부모 클래스의 생성자에서 할당한
					메모리까지 해제할 기회를 제공..
*/
//=================================================
/*
class CParent
{
	int* _pInt;
public:
	CParent()
	{
		cout << "CParent() 호출" << endl;
		_pInt = new int;
	}
	~CParent()
	{
		cout << "~CParent() 호출" << endl;
		delete _pInt;
	}
};

class CChild : public CParent
{
public:
	CChild() { cout << "CChild() 호출" << endl; }
	~CChild() { cout << "~CChild() 호출" << endl; }
};

int main()
{
	CChild child;

	return 0;
}
//*/
//=================================================
/*
	4.	[ Protected ] 멤버..

		-	[ public ]과 [ private ]의
			중간 정도되는 접근 제한..

		-	외부에서는 [ private ],
			자식에게는 [ public ]으로
			처리..

			->	기본적으로 [ private ]과 같으나
				상속 관계에 놓여있는 경우
				( 자식 클래스 )
				접근을 허용..
*/
//=================================================
/*
class CParent
{
public:
	CParent() {}
	void PrintPublic() { cout << "Public" << endl; }
	int _pub;
private:
	void PrintPrivate() { cout << "Private" << endl; }
	int _priv;
protected:
	int _prot;
	void PrintProtected() { cout << "Protected" << endl; }
};

class CChild : public CParent
{	
public:	
	void SetData()
	{
		_pub = 0;	//	public
		_prot = 20;	//	protected,
					//	자식에게는 public !!
		_priv = 10;	//	private..
	}
};

int main()
{
	//	부모...
	CParent base;
	base._pub = 5;		//	public..
	base._priv = 10;	//	private..
	base._prot = 20;	//	protected,
						//	외부에서는 private !!

	base.PrintPublic();
	base.PrintPrivate();
	base.PrintProtected();

	
	//	자식...
	CChild child;
	
	child._pub = 5;		//	public..
	child._priv = 10;	//	private..
	child._prot = 20;	//	protected,
						//	외부에서는 private !!

	child.PrintPublic();
	child.PrintPrivate();
	child.PrintProtected();

	child.SetData();


	return 0;
}

//*/
//=================================================
/*
	5.	세가지 형태의 상속..

	======================================================================
		부모 클래스 멤버의 	|	public..	|	protected..	|	private..
		접근 권한..			|				|				|			
	======================================================================
		public 멤버..		|	public..	|	protected..	|	private..	
	----------------------------------------------------------------------
		protected 멤버..		|	protected..	|	protected..	|	private..	
	----------------------------------------------------------------------
		private 멤버	..		|	접근 불가..	|	접근 불가..	|	접근 불가..
	======================================================================

	->	private 멤버는
		무조건 접근 불가..

	->	멤버의 접근 권한보다
		상속의 접근 권한 범위가
		더 좁은 경우, 상속의 접근 권한으로
		변환됨..

		ㄴ	private은 접근 불가로
			변환..

			ㄴ	private vs 접근 불가..

				ㄴ	private..

					ㄴ	외부 / 자식 클래스에서 사용 불가,
						내부에서 사용 가능..


				ㄴ	접근 불가..

					ㄴ	외부 / 내부 / 자식 클래스 모두
						사용 불가..
				

		

//=================================================
/*
	Q 2)

		은행 계좌 정보를 관리하는 클래스

		class CAccount
		{
			int _money;
			char _accNum[20];

		public :

			CAccount(char* pszAccNum, int money )
			{
				strcpy(_accNum, pszAccNum);
				_money = money;
			}
		}

		CAccount를 상속받는
		CKoreaAccount, CKBAccount를 만들어
		다음과 같이 사용하는 프로그램 작성..

		추가 정보
			-	CKoreaAccount	:	이체한도..
			-	CKBAccount		:	이체한도, 이자율..

		int main()
		{
			CKoreaAccount korAcc("123-456-789", 100, 1000);
			korAcc.ShowData();

			CKBAccount kbAcc("111-222-333", 200, 3500, 3.6f);
			kbAcc.ShowData();

			return 0;
		}

		결과

			계좌 번호 : 123-456-789
			계좌 잔액 : 100
			이체 한도 : 1000

			계좌 번호 : 111-222-333
			계좌 잔액 : 200
			이체 한도 : 3500
			이자율 : 3.6
*/
//=================================================