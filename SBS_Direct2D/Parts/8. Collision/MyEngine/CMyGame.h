/*=============================================================================
	[ 충돌 처리 ]
	[ 참고 : 
				//	개념 정리..
				https://blog.naver.com/jerrypoiu/221172549241
				//	응용..
				https://blog.naver.com/winterwolfs/10165506488 ]


	----------
	-	개요..
	----------

		-	정의..
			-	게임 오브젝트의 충돌 영역에 다른 게임 오브젝트의 충돌 영역이 
				닿거나 겹치는 경우 충돌로 인정..



	----------
	-	종류..
		[ 2D 게임에 제한.. ]
	----------

		-	[ 픽셀 충돌 ]
			-	이미지에 사용된 픽셀들을 일일이 비교하여 충돌 체크하는 방식..
			-	정밀도가 높지만 연산이 느림..


		-	[ 원 충돌 ]
			-	게임 오브젝트의 충돌 영역을 원으로 설정하여 충돌 체크..
			-	정밀도는 떨어지지만 연산은 제일 빠름..
			-	if( 두 원사이의 거리 <= 두 원의 반지름의 합 )
					return true;


		-	[ AABB ]
			-	Axis Aligned Bounding Box..
				-	축 조정 경계 상자..
			-	게임 오브젝트의 회전 상태와 상관없이 박스를 이루는 사각형의 축이 일치..
			

		-	[ OBB ]
			-	Oriented Bounding Box..
				-	방향 경계 상자..
			-	게임 오브젝트가 회전하면 같이 회전하는 경계 상자..


=============================================================================*/
//============================================
#pragma once
//============================================
#ifndef _MYGAME_H_
#define _MYGAME_H_
//============================================
#include "Global.h"
//============================================
class CMyGame :	public CDxCore
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

};// class CMyGame :	public CDxCore

extern CMyGame* g_pMyGame;
//============================================
#endif // _MYGAME_H_
//============================================