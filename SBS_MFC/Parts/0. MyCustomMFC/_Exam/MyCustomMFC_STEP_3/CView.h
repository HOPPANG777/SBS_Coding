//====================================================
#pragma once
#include "CObject.h"
//====================================================
//	메시지 맵 관련 매크로..
#define DECLARE_MESSAGE_MAP()          static MessageMap messageMap[];
#define BEGIN_MESSAGE_MAP(class_name)  MessageMap class_name::messageMap[] = {
#define END_MESSAGE_MAP()              {0,NULL} };
//====================================================
class CView;
typedef void (CView::*CViewFuncPt)();
//====================================================
struct MessageMap
{
	UINT iMsg;
	CViewFuncPt _fp;
};
//====================================================
class CView : public CObject
{	
public:
	void OnCreate();
	void OnDraw();
	void OnDestroy();
	void OnLButtonDown();
	
	DECLARE_MESSAGE_MAP()
};
extern CViewFuncPt fpCViewGlobal;
//====================================================
extern CView g_View;
//====================================================