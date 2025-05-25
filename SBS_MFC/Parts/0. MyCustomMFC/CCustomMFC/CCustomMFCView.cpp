
// CCustomMFCView.cpp: CCCustomMFCView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "CCustomMFC.h"
#endif

#include "CCustomMFCDoc.h"
#include "CCustomMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCCustomMFCView

IMPLEMENT_DYNCREATE(CCCustomMFCView, CView)

BEGIN_MESSAGE_MAP(CCCustomMFCView, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CCCustomMFCView 생성/소멸

CCCustomMFCView::CCCustomMFCView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CCCustomMFCView::~CCCustomMFCView()
{
}

BOOL CCCustomMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CCCustomMFCView 그리기

void CCCustomMFCView::OnDraw(CDC* /*pDC*/)
{
	CCCustomMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CCCustomMFCView 진단

#ifdef _DEBUG
void CCCustomMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CCCustomMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCCustomMFCDoc* CCCustomMFCView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCCustomMFCDoc)));
	return (CCCustomMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CCCustomMFCView 메시지 처리기


int CCCustomMFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	MessageBox(TEXT("OnCreate()"), TEXT("CUSTOM MFC"), MB_OK | MB_ICONINFORMATION);

	return 0;
}


void CCCustomMFCView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	MessageBox(TEXT("OnDestroy()"), TEXT("CUSTOM MFC"), MB_OK | MB_ICONINFORMATION);
}


void CCCustomMFCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString str;
	str.Format(TEXT("OnLButtonDown %d, %d"), point.x, point.y);
	MessageBox(str, TEXT("CUSTOM MFC"), MB_OK | MB_ICONINFORMATION);
	CView::OnLButtonDown(nFlags, point);
}
