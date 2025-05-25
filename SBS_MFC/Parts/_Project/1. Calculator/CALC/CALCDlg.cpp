
// CALCDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "CALC.h"
#include "CALCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCALCDlg::CCALCDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCALCDlg::IDD, pParent)
	, _szInput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCALCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT, _szInput);
}

BEGIN_MESSAGE_MAP(CCALCDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_Number0, &CCALCDlg::OnBnClickedNumber0)

	ON_BN_CLICKED(IDC_Number1, &CCALCDlg::OnBnClickedNumber1)
	ON_BN_CLICKED(IDC_Number2, &CCALCDlg::OnBnClickedNumber2)
	ON_BN_CLICKED(IDC_Number3, &CCALCDlg::OnBnClickedNumber3)
	ON_BN_CLICKED(IDC_Number4, &CCALCDlg::OnBnClickedNumber4)
	ON_BN_CLICKED(IDC_Number5, &CCALCDlg::OnBnClickedNumber5)
	ON_BN_CLICKED(IDC_Number6, &CCALCDlg::OnBnClickedNumber6)
	ON_BN_CLICKED(IDC_Number7, &CCALCDlg::OnBnClickedNumber7)
	ON_BN_CLICKED(IDC_Number8, &CCALCDlg::OnBnClickedNumber8)
	ON_BN_CLICKED(IDC_Number9, &CCALCDlg::OnBnClickedNumber9)
	ON_BN_CLICKED(IDC_BACKS, &CCALCDlg::OnBnClickedBacks)
	ON_BN_CLICKED(IDC_CLEAR, &CCALCDlg::OnBnClickedClear)
	
	ON_BN_CLICKED(IDC_PLUS, &CCALCDlg::OnBnClickedPlus)
	ON_BN_CLICKED(IDC_MUL, &CCALCDlg::OnBnClickedMul)
	ON_BN_CLICKED(IDC_MINUS, &CCALCDlg::OnBnClickedMinus)
	ON_BN_CLICKED(IDC_DIV, &CCALCDlg::OnBnClickedDiv)
	ON_BN_CLICKED(IDC_EQ, &CCALCDlg::OnBnClickedEq)
END_MESSAGE_MAP()


// CCALCDlg 메시지 처리기

BOOL CCALCDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CCALCDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CCALCDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트

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
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CCALCDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCALCDlg::OnBnClickedNumber0()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	_szInput +="0";
	UpdateData(false);
}

void CCALCDlg::OnBnClickedNumber1()
{
	_szInput +="1";
	UpdateData(false);
}

void CCALCDlg::OnBnClickedNumber2()
{
	_szInput +="2";
	UpdateData(false);
}

void CCALCDlg::OnBnClickedNumber3()
{
	_szInput +="3";
	UpdateData(false);
}

void CCALCDlg::OnBnClickedNumber4()
{
	_szInput +="4";
	UpdateData(false);
}

void CCALCDlg::OnBnClickedNumber5()
{
	_szInput +="5";
	UpdateData(false);
}

void CCALCDlg::OnBnClickedNumber6()
{
	_szInput +="6";
	UpdateData(false);
}

void CCALCDlg::OnBnClickedNumber7()
{
	_szInput +="7";
	UpdateData(false);
}

void CCALCDlg::OnBnClickedNumber8()
{
	_szInput +="8";
	UpdateData(false);
}

void CCALCDlg::OnBnClickedNumber9()
{
	_szInput +="9";
	UpdateData(false);
}

void CCALCDlg::OnBnClickedBacks()
{
	CString back;
	UpdateData(true);
	back.Format(_T("%s"), _szInput);
	if(back != "")
	{
		back.Delete( back.GetLength()-1, 1 );
		if(back.GetLength() == 0)
			back = "";
		_szInput = back;
		UpdateData(false);
	} 
}

void CCALCDlg::OnBnClickedClear()
{
	_szInput = "";
	_inputNumber = 0;
	UpdateData(false);
}

void CCALCDlg::OnBnClickedPlus()
{
	UpdateData(true);
	_inputNumber = _tstoi(_szInput);
	_operator = PLUS;
	_szInput = "";
	UpdateData(false);
}

void CCALCDlg::OnBnClickedMinus()
{
	UpdateData(true);
	_inputNumber = _tstoi(_szInput);
	_operator = MINUS;
	_szInput = "";
	UpdateData(false);
}


void CCALCDlg::OnBnClickedMul()
{
	UpdateData(true);
	_inputNumber = _tstoi(_szInput);
	_operator = MULTI;
	_szInput = "";
	UpdateData(false);
}


void CCALCDlg::OnBnClickedDiv()
{
	UpdateData(true);
	_inputNumber = _tstoi(_szInput);
	_operator = DIVIDE;
	_szInput = "";
	UpdateData(false);
}

void CCALCDlg::OnBnClickedEq()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString szTmp;
	int result;
	UpdateData(true);

	switch(_operator)
	{
		case PLUS:
			result = _inputNumber + _tstoi(_szInput);
			szTmp.Format(_T("%d"), result);
			_szInput = szTmp;
			UpdateData(false);
			_inputNumber = result;
			break;


		case MINUS:
			result = _inputNumber - _tstoi(_szInput);
			szTmp.Format(_T("%d"), result);
			_szInput = szTmp;
			UpdateData(false);
			_inputNumber = result;
			break;
	
		
		case MULTI:
			result = _inputNumber * _tstoi(_szInput);
			szTmp.Format(_T("%d"), result);
			_szInput = szTmp;
			UpdateData(false);
			_inputNumber = result;
			break;
	
		
		case DIVIDE:
			result = _inputNumber / _tstoi(_szInput);
			szTmp.Format(_T("%d"), result);
			_szInput = szTmp;
			UpdateData(false);
			_inputNumber = result;
			break;

	}//	switch(_operator)

}//	void CCALCDlg::OnBnClickedEq()