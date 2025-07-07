//============================================
#pragma once
//============================================
#ifndef _MYGAME_H_
#define _MYGAME_H_
//============================================
#include "Global.h"
//============================================
class CMyGame :	public CCore
{
public:
	CMyGame();
	virtual ~CMyGame();

	virtual INT		Init();
	virtual INT		Render();
	virtual INT		FrameMove();
	virtual void	Destroy();
	
	virtual LRESULT MsgProc(HWND, UINT, WPARAM, LPARAM);

	CDxTexture*		m_pDxTexture1;
	CDxTexture*		m_pDxTexture2;
	D3DXVECTOR3		m_vec3Pos1;
	D3DXVECTOR3		m_vec3Pos2;

	CDxFont			m_dxFont;
	CheckCollision* m_pCheckCollision1;
	CheckCollision* m_pCheckCollision2;

};// class CMyGame :	public CCore

extern CMyGame* g_pMyGame;
//============================================
#endif // _MYGAME_H_
//============================================
/*
	[ 다형성 ]
	[ 참고 : https://life-with-coding.tistory.com/485 ]
 
	----------
	-	개념..
	----------

		-	부모-자식 상속 관계에 있는 클래스에서
			상위 클래스가 동일한 메시지로
			하위 클래스들을 서로 다르게 동작시키는 객체 지향 원리..



	----------
	-	장점..
	----------

		1)	유지보수가 쉽다..
			-	개발자가 여러 객체를 하나의 타입으로 관리가 가능하기 때문에
				코드 관리가 편리해 유지보수가 용이..

		2)	재사용성 증가..
			-	객체를 재사용하기 쉬워지기 때문에 개발자의 코드 재사용성이 증가..

		3)	느슨한 결합..
			-	클래스간 의존성이 줄어들며 확장성이 높고 결합도가 낮아져
				안전성이 증가..

		
	--------------
	-	필수 조건..
	--------------
		
		1)	상속 관계
			-	부모-자식 간 클래스 상속..

		2)	오버라이딩 필수..
			-	부모 클래스의 다형성을 적용하려는 메소드를
				하위 클래스에서 반드시 재정의..

		3) 업캐스팅 ( 자식 클래스의 객체가 부모 클래스 타입으로 형변환 되는 것 )
			-	부모 타입으로 자식클래스를 업캐스팅하여 객체를 생성..
				또는, 부모 타입 객체로 자식클래스 객체에 접근..



	-------------
	-	활용 예..
	-------------

		-	처리 방식이나 알고리즘을 실시간으로 변형하고 싶을때..
			-	정렬 알고리즘의 정렬 방식, 충돌방식 등..

		-	일괄 처리..
			-	스타크래프트에서 특정 종족의 군인들을 일괄선택후
				공격처리..

		-	새로운 버전에 대한 대응..
			-	새로운 기능 또는 타입을 추가하더라도 부모 클래스가 같다면
				기능을 활용하는 입장에선 수정할 요소가 없음..
				예)
					다형성 적용 전...
						class CZooKeeper;
						class CDog;
						class CCat;
						class CLion;

						CZooKeeper::Wash( CDog animal ){ animal.Wash();}
						CZooKeeper::Wash( CCat animal ){ animal.Wash();}
						CZooKeeper::Wash( CLion animal ){ animal.Wash();}


					다형성 적용 후...
						class CZooKeeper;
						class CAnimal;
						class CDog : public CAnimal;
						class CCat : public CAnimal;
						class CLion : public CAnimal;

						CZooKeeper::Wash( CAnimal animal ){ animal.Wash(); }
						

*/
//============================================