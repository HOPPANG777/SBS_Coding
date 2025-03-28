//=================================================
#include<iostream>
using namespace std;
#pragma warning( disable : 4996 )
//=================================================
//	클래스 (고급)
//	
//	[3 - 5]	상속과 다형성..
//=================================================
/* 
	-----------------------
	1.	상속이 적절한 상황..
	-----------------------

		-	클래스 사이의
			논리적 관계..

			----------------------
			관계 1)	HAS - A 관계..
			----------------------

				ㄴ	소유 관계..

				ㄴ	"Police has a gun"

				ㄴ	예제 소스 - 1) 참고..
*/
//=================================================
/*	예제 소스 - 1)
class CGun
{
public :
	void Shot() { cout<<"탕탕!!"<<endl; }
};

class CPolice : public CGun
{
public :
	void UseWeapon() { Shot(); }
};

int main()
{
	CPolice police;

	police.UseWeapon();

	return 0;
}
//*/
/*
	-	[ 소유 관계 ]로 표현해야 할
		클래스를 [ 상속 ]으로
		구현하게 되면 [ 필요없는 속성 ]이
		[ 자식 클래스 ]에 들어갈 수 있음..

		ㄴ	대안은 ? ? ?

			-	예제 소스 - 2) 참고
*/
//=================================================
/*	예제 소스 - 2)
class CGun
{
public:
	void Shot() { cout << "탕탕!!" << endl; }
};

class CPolice
{
	CGun* _pGun;

public :
	CPolice() { _pGun = new CGun; }
	~CPolice() { delete _pGun; }
	void UseWeapon() { if(_pGun!=NULL) _pGun->Shot(); }
};

int main()
{
	CPolice police;
	police.UseWeapon();

	return 0;
}
//*/
//=================================================
/*
	---------------------
	관계 2)	IS - A 관계..
	---------------------

		-	상속을 디자인 할때
			가장 기본적인 관계..

		-	"Student is Person" ( O )
				예)	class CStudent : public CPerson ( O )

			"Person is Student" ( X )
				예)	class CPerson : public CStudent ( X )

			-	논리적으로 [ 사람 ]의 범위가
				[ 학생 ]이라는 범위보다
				크기 때문에 [ 학생 ]이 [ 사람 ]을
				상속받는 것이 자연스러움..

			-	클래스 디자인은 현실 세계에 맞게
				디자인 할 것..

				ㄴ	논리적으로도
					모순이 없어야 함..


*/
//=================================================
/*
	- 결론..

		-	대부분의 상속은 [ Is - A 관계 ]를
			표현하기 위한 수단이어야 함..
			
*/
//=================================================
/*
	2.	상속된 객체와
		포인터..

		-	레퍼런스도 마찬가지..

		1)	부모 클래스의 포인터 객체는
			자식 클래스 객체를 가르킬수 있음..

			예)	class CParent;
				class CChild : public CParent;

				CParent* pPar;
				CChild child;

				pPar = &child;



		2)	자식 클래스의 포인터 객체는
			부모 클래스의 멤버 함수를
			호출 가능..

			-	[ 참고 : CPerson_CStudent_CPartTimeStudent 상속관계.png ]
*/
//=================================================
/*
class CPerson
{
public :
	void Sleep() { cout << "Zzz.." << endl; }
};

class CStudent : public CPerson
{
public:
	void Study() { cout << "Study!!" << endl; }
};

class CPartTimeStudent : public CStudent
{
public:
	void Work() { cout << "Work!!" << endl; }
};

int main()
{
	//--------------------------
	//	1)	부모 객체의 포인터로
	//		본인과 자식 객체의
	//		주소값을 관리 가능..
	CPerson* p1 = new CPerson;
	CPerson* p2 = new CStudent;
	CPerson* p3 = new CPartTimeStudent;	
	//--------------------------

	p1->Sleep();
	p2->Sleep();
	p3->Sleep();

	//--------------------------
	//	2)	CPerson*이 가리키는 대상은
	//		컴파일러 입장에선
	//		CPerson 객체로 인식..	
	//p2->Study();
	//p3->Study();
	//p3->Work();

	
	CPartTimeStudent* pPartStu = ( CPartTimeStudent* )p3;
	pPartStu->Study();
	pPartStu->Work();
	

	CStudent* student = new CStudent;
	student->Sleep();
	student->Study();
	delete student;
	//--------------------------
		
	delete p1;
	delete p2;
	delete p3;

	return 0;
}
//*/
//=================================================
/*
	고찰)	[ RCP Game - Adv ]의
			CPlayer, CComputer 클래스의 
			공통적인 속성을 묶어
			부모 클래스를 만든뒤 적용해봅니다..
*/
//=================================================