//===========================================================================
// 참고 : 
//			https://3001ssw.tistory.com/21?category=939609
//===========================================================================
//	[ 과제.. ]
//	
//	본 프로젝트는 미완성 가게부 프로그램입니다 ㅠㅠ..
//	다음의 기능을 보완하도록 합니다!!
// 
//	1)	[ 대분류 ]에서 선택한 하위 목록이 [ 소분류 ]에 적용됩니다..
//		-	[ 대분류 ]		[ 소분류 ]
//			수입				월급 / 상여금 / 명절 보너스 / 기타
//			저축				적금 / 일반예금 / 주식
//			세금				전기세 / 가스비 / 수도세 / 건강 보험료
// 
//	2)	입력 / 수정 / 삭제 후 확인 메시지를 연출합니다..
//		-	"입력하신 정보가 맞습니까" / "예", "아니오"
// 
//	3)	수정 기능을 보완합니다..
// 
//		1)	수정하고자하는 셀을 선택..
// 
//		2)	더블 클릭 또는 수정 버튼 클릭..
// 
//		3)	편집 대화 상자 출력..
//		
//		4)	선택한 정보가 대화상자에 세팅..
// 
//		5)	편집 대화 상자의 정보 갱신..
// 
//		6)	확인 버튼 클릭..
// 
//		7)	최신 정보 갱신..
//	
//	4)	정렬 기능 추가..
//		ㄴ	타이틀을 누르면 정렬되도록 합니다..
// 
//	5)	저장 / 불러오기 기능 추가..
// 
//===========================================================================
// SpendDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Spend.h"
#include "SpendDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSpendDlg 대화 상자



CSpendDlg::CSpendDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SPEND_DIALOG, pParent)
	, m_iSelect( -1 )
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange( pDX );
	DDX_Control( pDX, IDC_LIST_SPEND, m_lcSpend );
	DDX_Control( pDX, IDC_COMBO_SPEND_INCOME, m_cbSpendIncome );
	DDX_Control( pDX, IDC_EDIT_MONEY, m_edMoney );
	DDX_Control( pDX, IDC_COMBO_MAIN_CATEGORY, m_cbMainCategory );
	DDX_Control( pDX, IDC_COMBO_SUB_CATEGORY, m_cbSubCategory );
	DDX_Control( pDX, IDC_EDIT_MEMO, m_edMemo );
	DDX_Control( pDX, IDC_DATETIMEPICKER_DATE, m_dtpDate );
	DDX_Control( pDX, IDC_STATIC_DISP, m_stDisp );
}

BEGIN_MESSAGE_MAP(CSpendDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED( IDOK, &CSpendDlg::OnBnClickedOk )
	ON_BN_CLICKED( IDCANCEL, &CSpendDlg::OnBnClickedCancel )
	ON_BN_CLICKED( IDC_BUTTON_MAKE, &CSpendDlg::OnBnClickedButtonMake )
	ON_BN_CLICKED( IDC_BUTTON_MODIFY, &CSpendDlg::OnBnClickedButtonModify )
	ON_BN_CLICKED( IDC_BUTTON_DELETE, &CSpendDlg::OnBnClickedButtonDelete )
	ON_NOTIFY( NM_CLICK, IDC_LIST_SPEND, &CSpendDlg::OnNMClickListSpend )
END_MESSAGE_MAP()


// CSpendDlg 메시지 처리기

BOOL CSpendDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// List Control 초기화
	m_lcSpend.InsertColumn( 0, _T( "순서" ), LVCFMT_CENTER, 50 );
	m_lcSpend.InsertColumn( 1, _T( "날짜" ), LVCFMT_CENTER, 100 );
	m_lcSpend.InsertColumn( 2, _T( "지출/수입" ), LVCFMT_CENTER, 100 );
	m_lcSpend.InsertColumn( 3, _T( "금액" ), LVCFMT_CENTER, 100 );
	m_lcSpend.InsertColumn( 4, _T( "대분류" ), LVCFMT_CENTER, 100 );
	m_lcSpend.InsertColumn( 5, _T( "소분류" ), LVCFMT_CENTER, 100 );
	m_lcSpend.InsertColumn( 6, _T( "메모" ), LVCFMT_CENTER, 400 );
	m_lcSpend.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );

	// 지출/수입 콤보박스 초기화
	m_cbSpendIncome.InsertString( 0, _T( "지출" ) );
	m_cbSpendIncome.InsertString( 1, _T( "수입" ) );
	m_cbSpendIncome.SetCurSel(0);

	// 대분류 콤보박스 초기화
	m_cbMainCategory.InsertString( 0, _T( "월급" ) );
	m_cbMainCategory.InsertString( 1, _T( "상여금" ) );
	m_cbMainCategory.InsertString( 2, _T( "저축" ) );
	m_cbMainCategory.InsertString( 3, _T( "공과금" ) );
	m_cbMainCategory.InsertString( 4, _T( "통신비" ) );
	m_cbMainCategory.InsertString( 5, _T( "교통비" ) );
	m_cbMainCategory.InsertString( 6, _T( "교육비" ) );
	m_cbMainCategory.SetCurSel( 0 );

	// 소분류 콤보박스 초기화
	m_cbSubCategory.InsertString( 0, _T( "명절상여금" ) );
	m_cbSubCategory.InsertString( 1, _T( "이월금액" ) );
	m_cbSubCategory.InsertString( 2, _T( "도시가스비" ) );
	m_cbSubCategory.InsertString( 3, _T( "보험비" ) );
	m_cbSubCategory.InsertString( 4, _T( "피아노학원" ) );
	m_cbSubCategory.InsertString( 5, _T( "태권도학원" ) );
	m_cbSubCategory.SetCurSel( 0 );


	DisplaySum();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSpendDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSpendDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSpendDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSpendDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
//	CDialogEx::OnOK();
}


void CSpendDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CSpendDlg::OnBnClickedButtonMake()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sSpendIncome;
	CString sMoney;
	CString sMainCategory;
	CString sSubCategory;
	CString sMemo;
	CString sDate;
	
	m_cbSpendIncome.GetWindowText( sSpendIncome );
	m_edMoney.GetWindowText( sMoney );
	m_cbMainCategory.GetWindowText( sMainCategory );
	m_cbSubCategory.GetWindowText( sSubCategory );
	m_edMemo.GetWindowText( sMemo );
	m_dtpDate.GetWindowText( sDate );

	CString sNo;
	int iCount = m_lcSpend.GetItemCount();
	sNo.Format( _T("%d"), iCount );
	m_lcSpend.InsertItem( iCount, sNo );
	m_lcSpend.SetItemText( iCount, 1, sDate );
	m_lcSpend.SetItemText( iCount, 2, sSpendIncome );
	m_lcSpend.SetItemText( iCount, 3, sMoney );
	m_lcSpend.SetItemText( iCount, 4, sMainCategory );
	m_lcSpend.SetItemText( iCount, 5, sSubCategory );
	m_lcSpend.SetItemText( iCount, 6, sMemo );

	DisplaySum();
}


void CSpendDlg::OnBnClickedButtonModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	int iCount = m_lcSpend.GetItemCount();
	if ( (-1 < m_iSelect) && (m_iSelect < iCount) )
	{
		CString sSpendIncome;
		CString sMoney;
		CString sMainCategory;
		CString sSubCategory;
		CString sMemo;
		CString sDate;

		m_cbSpendIncome.GetWindowText( sSpendIncome );
		m_edMoney.GetWindowText( sMoney );
		m_cbMainCategory.GetWindowText( sMainCategory );
		m_cbSubCategory.GetWindowText( sSubCategory );
		m_edMemo.GetWindowText( sMemo );
		m_dtpDate.GetWindowText( sDate );

		m_lcSpend.SetItemText( m_iSelect, 1, sDate );
		m_lcSpend.SetItemText( m_iSelect, 2, sSpendIncome );
		m_lcSpend.SetItemText( m_iSelect, 3, sMoney );
		m_lcSpend.SetItemText( m_iSelect, 4, sMainCategory );
		m_lcSpend.SetItemText( m_iSelect, 5, sSubCategory );
		m_lcSpend.SetItemText( m_iSelect, 6, sMemo );		
	}

	DisplaySum();
}


void CSpendDlg::OnBnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int iCount = m_lcSpend.GetItemCount();
	if ( (-1 < m_iSelect) && (m_iSelect < iCount) )
	{
		m_lcSpend.DeleteItem( m_iSelect );

		DisplaySum();
	}
}


void CSpendDlg::OnNMClickListSpend( NMHDR *pNMHDR, LRESULT *pResult )
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if ( IDC_LIST_SPEND == pNMItemActivate->hdr.idFrom )
	{
		int iItemCnt = m_lcSpend.GetItemCount();
		int iSelItem = pNMItemActivate->iItem;

		if ( (0 <= iSelItem) && (iSelItem < iItemCnt) )
		{
			m_iSelect = iSelItem;
		}
	}

	*pResult = 0;
}


void CSpendDlg::DisplaySum()
{
	CString sSum;
	int iSum = 0;
	int iCount = m_lcSpend.GetItemCount();

	for ( int i = 0 ; i < iCount ; i++ )
	{
		CString sSpendIncome;
		sSpendIncome = m_lcSpend.GetItemText( i, 2 );
		if ( _T("") != sSpendIncome )
		{
			CString sMoney;
			sMoney = m_lcSpend.GetItemText( i, 3 );

			if ( _T("지출") == sSpendIncome )
				iSum -= _ttoi(sMoney);
			else if ( _T( "수입" ) == sSpendIncome )
				iSum += _ttoi( sMoney );
		}
	}

	sSum.Format( _T( "총합 %d원" ), iSum );
	m_stDisp.SetWindowText( sSum );
}
