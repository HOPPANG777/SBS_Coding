//====================================================
#pragma once
#include "CObject.h"
//====================================================
class CView;
//	CView클래스의 멤버 함수를 가리킬수 있는 함수 포인터..
typedef void (CView::*CViewFuncPt)();
//====================================================
//	메시지 맵을 다룰 구조체 선언.
struct MessageMap
{
	UINT iMsg;
	CViewFuncPt _fp;
};
//====================================================
class CView : public CObject
{
public:		
	static MessageMap messageMap[];

	void OnCreate();
	void OnDraw();
	void OnDestroy();
	void OnLButtonDown();

	/*
		예)
			1)	void (*CViewFuncPt)()			==		void (*CView::CViewFuncPt)()
				-	외부 함수를 가리킬수 있는 함수 포인터..
							
			2)	void (CView::*CViewFuncPt)()	!=		void (*CView::CViewFuncPt)()
				-	CView클래스의 멤버 함수를 가리킬수 있는 함수 포인터..
	*/
};
extern CViewFuncPt fpCViewGlobal;
//====================================================
extern CView g_View;
//====================================================