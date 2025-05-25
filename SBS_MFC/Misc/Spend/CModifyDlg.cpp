// CModifyDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Spend.h"
#include "SpendDlg.h"
#include "CModifyDlg.h"
#include "afxdialogex.h"


// CModifyDlg 대화 상자

IMPLEMENT_DYNAMIC(CModifyDlg, CDialog)

CModifyDlg::CModifyDlg(CSpendDlg* pParent /*=nullptr*/)
	: CDialog(IDD_MODIFY_DIALOG, pParent)
{
	m_pParentWnd = pParent;
}

CModifyDlg::~CModifyDlg()
{
}

void CModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SPEND_M, m_lcSpend_M);
	DDX_Control(pDX, IDC_COMBO_SPEND_INCOME_M, m_cbSpendIncome_M);
	DDX_Control(pDX, IDC_EDIT_MONEY_M, m_edMoney_M);
	DDX_Control(pDX, IDC_COMBO_MAIN_CATEGORY_M, m_cbMainCategory_M);
	DDX_Control(pDX, IDC_COMBO_SUB_CATEGORY_M, m_cbSubCategory_M);
	DDX_Control(pDX, IDC_EDIT_MEMO_M, m_edMemo_M);
	DDX_Control(pDX, IDC_DATETIMEPICKER_DATE_M, m_dtpDate_M);
	DDX_Control(pDX, IDC_STATIC_DISP_M, m_stDisp_M);
}


BEGIN_MESSAGE_MAP(CModifyDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_COMBO_SPEND_INCOME_M, &CModifyDlg::OnCbnSelchangeComboSpendIncomeM)
	ON_CBN_SELCHANGE(IDC_COMBO_MAIN_CATEGORY_M, &CModifyDlg::OnCbnSelchangeComboMainCategoryM)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_M, &CModifyDlg::OnBnClickedButtonDeleteM)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_M, &CModifyDlg::OnBnClickedButtonModifyM)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_M2, &CModifyDlg::OnBnClickedButtonTestModifyM)
END_MESSAGE_MAP()

// CModifyDlg 메시지 처리기

BOOL CModifyDlg::OnInitDialog()
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

	

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon_M, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon_M, FALSE);		// 작은 아이콘을 설정합니다.

	// List Control 초기화
	m_lcSpend_M.InsertColumn(0, _T("순서"), LVCFMT_CENTER, 50);
	m_lcSpend_M.InsertColumn(1, _T("날짜"), LVCFMT_CENTER, 100);
	m_lcSpend_M.InsertColumn(2, _T("지출/수입"), LVCFMT_CENTER, 100);
	m_lcSpend_M.InsertColumn(3, _T("금액"), LVCFMT_CENTER, 100);
	m_lcSpend_M.InsertColumn(4, _T("대분류"), LVCFMT_CENTER, 100);
	m_lcSpend_M.InsertColumn(5, _T("소분류"), LVCFMT_CENTER, 100);
	m_lcSpend_M.InsertColumn(6, _T("메모"), LVCFMT_CENTER, 400);
	m_lcSpend_M.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	// 지출/수입 콤보박스 초기화
	m_cbSpendIncome_M.InsertString(0, _T("지출"));
	m_cbSpendIncome_M.InsertString(1, _T("수입"));
	m_cbSpendIncome_M.SetCurSel(0);

	m_cbMainCategory_M.ResetContent();
	m_cbMainCategory_M.InsertString(0, _T("저축"));
	m_cbMainCategory_M.InsertString(1, _T("세금"));
	m_cbMainCategory_M.SetCurSel(0);

	m_cbSubCategory_M.ResetContent();
	m_cbSubCategory_M.InsertString(0, _T("월급"));
	m_cbSubCategory_M.InsertString(1, _T("상여금"));
	m_cbSubCategory_M.InsertString(2, _T("명절 보너스"));
	m_cbSubCategory_M.SetCurSel(0);

	
	RelocateLIsttoM();
	DisplaySumM();

	return TRUE;
}


void CModifyDlg::OnCbnSelchangeComboSpendIncomeM()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	int nIndex;

	nIndex = m_cbSpendIncome_M.GetCurSel();   //현재 선택된 항목의 인덱스 얻어옴
	m_cbSpendIncome_M.GetLBText(nIndex, str); //인덱스에 해당하는 문자열 얻어옴

	if (str == "지출")
	{
		m_cbMainCategory_M.ResetContent();
		m_cbMainCategory_M.InsertString(0, _T("저축"));
		m_cbMainCategory_M.InsertString(1, _T("세금"));
	}
	else
	{
		m_cbMainCategory_M.ResetContent();
		m_cbMainCategory_M.InsertString(0, _T("급여"));
	}
	m_cbMainCategory_M.SetCurSel(0);

}


void CModifyDlg::OnCbnSelchangeComboMainCategoryM()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str;
	int nIndex;

	nIndex = m_cbMainCategory_M.GetCurSel();   //현재 선택된 항목의 인덱스 얻어옴
	m_cbMainCategory_M.GetLBText(nIndex, str); //인덱스에 해당하는 문자열 얻어옴

	if (str == "급여")
	{
		m_cbSubCategory_M.ResetContent();
		m_cbSubCategory_M.InsertString(0, _T("월급"));
		m_cbSubCategory_M.InsertString(1, _T("상여금"));
		m_cbSubCategory_M.InsertString(2, _T("명절 보너스"));
	}
	else if (str == "저축")
	{
		m_cbSubCategory_M.ResetContent();
		m_cbSubCategory_M.InsertString(0, _T("적금"));
		m_cbSubCategory_M.InsertString(1, _T("일반예금"));
		m_cbSubCategory_M.InsertString(2, _T("주식"));
	}
	else if (str == "세금")
	{
		m_cbSubCategory_M.ResetContent();
		m_cbSubCategory_M.InsertString(0, _T("전기세"));
		m_cbSubCategory_M.InsertString(1, _T("수도세"));
		m_cbSubCategory_M.InsertString(2, _T("도시가스비"));
		m_cbSubCategory_M.InsertString(3, _T("건강보험료"));

	}
	m_cbSubCategory_M.SetCurSel(0);
}


void CModifyDlg::DisplaySumM()
{
	//m_lcSpend_M = ((CSpendDlg*)GetParent())->m_lcSpend;
	
	CString sSum;
	int iSum = 0;
	int iCount = ((CSpendDlg*)GetParent())->m_lcSpend.GetItemCount();

	for (int i = 0; i < iCount; i++)
	{
		CString sSpendIncome;
		sSpendIncome = ((CSpendDlg*)GetParent())->m_lcSpend.GetItemText(i, 2);
		if (_T("") != sSpendIncome)
		{
			CString sMoney;
			sMoney = ((CSpendDlg*)GetParent())->m_lcSpend.GetItemText(i, 3);

			if (_T("지출") == sSpendIncome)
				iSum -= _ttoi(sMoney);
			else if (_T("수입") == sSpendIncome)
				iSum += _ttoi(sMoney);
		}
	}

	sSum.Format(_T("총합 %d원"), iSum);
	m_stDisp_M.SetWindowText(sSum);
}

void CModifyDlg::RelocateLIsttoM()
{
	CString sSpendIncome_M;
	CString sMoney_M;
	CString sMainCategory_M;
	CString sSubCategory_M;
	CString sMemo_M;
	CString sDate_M;

	((CSpendDlg*)GetParent())->m_cbSpendIncome.GetWindowText(sSpendIncome_M);
	((CSpendDlg*)GetParent())->m_edMoney.GetWindowText(sMoney_M);
	((CSpendDlg*)GetParent())->m_cbMainCategory.GetWindowText(sMainCategory_M);
	((CSpendDlg*)GetParent())->m_cbSubCategory.GetWindowText(sSubCategory_M);
	((CSpendDlg*)GetParent())->m_edMemo.GetWindowText(sMemo_M);
	((CSpendDlg*)GetParent())->m_dtpDate.GetWindowText(sDate_M);

	CString sNo;
	sNo.Format(_T("%d"), 0);
	m_lcSpend_M.InsertItem(0, sNo);
	m_lcSpend_M.SetItemText(0, 1, sDate_M);
	m_lcSpend_M.SetItemText(0, 2, sSpendIncome_M);
	m_lcSpend_M.SetItemText(0, 3, sMoney_M);
	m_lcSpend_M.SetItemText(0, 4, sMainCategory_M);
	m_lcSpend_M.SetItemText(0, 5, sSubCategory_M);
	m_lcSpend_M.SetItemText(0, 6, sMemo_M);


	//	날짜..
	m_dtpDate_M.SetFormat(sDate_M);

	//	수입 / 지출..
	int idx = m_cbSpendIncome_M.FindString(0, sSpendIncome_M);
	m_cbSpendIncome_M.SetCurSel(idx);

	//	대분류..
	if (sSpendIncome_M == "지출")
	{
		m_cbMainCategory_M.ResetContent();
		m_cbMainCategory_M.InsertString(0, _T("저축"));
		m_cbMainCategory_M.InsertString(1, _T("세금"));
	}
	else
	{
		m_cbMainCategory_M.ResetContent();
		m_cbMainCategory_M.InsertString(0, _T("급여"));
	}
	idx = m_cbMainCategory_M.FindString(0, sMainCategory_M);
	m_cbMainCategory_M.SetCurSel(idx);

	//	소분류..
	if (sMainCategory_M == "급여")
	{
		m_cbSubCategory_M.ResetContent();
		m_cbSubCategory_M.InsertString(0, _T("월급"));
		m_cbSubCategory_M.InsertString(1, _T("상여금"));
		m_cbSubCategory_M.InsertString(2, _T("명절 보너스"));
	}
	else if (sMainCategory_M == "저축")
	{
		m_cbSubCategory_M.ResetContent();
		m_cbSubCategory_M.InsertString(0, _T("적금"));
		m_cbSubCategory_M.InsertString(1, _T("일반예금"));
		m_cbSubCategory_M.InsertString(2, _T("주식"));
	}
	else if (sMainCategory_M == "세금")
	{
		m_cbSubCategory_M.ResetContent();
		m_cbSubCategory_M.InsertString(0, _T("전기세"));
		m_cbSubCategory_M.InsertString(1, _T("수도세"));
		m_cbSubCategory_M.InsertString(2, _T("도시가스비"));
		m_cbSubCategory_M.InsertString(3, _T("건강보험료"));

	}
	idx = m_cbSubCategory_M.FindString(0, sSubCategory_M);
	m_cbSubCategory_M.SetCurSel(idx);

	//	금액..
	m_edMoney_M.SetWindowText(sMoney_M);

	//	메모..
	m_edMemo_M.SetWindowText(sMemo_M);

	
	DisplaySumM();
}



//취소 버튼
void CModifyDlg::OnBnClickedButtonDeleteM()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (AfxMessageBox(_T("정말 취소하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		EndDialog(0);
	}

}



//최종 수정 버튼
void CModifyDlg::OnBnClickedButtonModifyM()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (AfxMessageBox(_T("수정하신 정보가 맞습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		//정보 반환.
		CString sSpendIncome_M;
		CString sMoney_M;
		CString sMainCategory_M;
		CString sSubCategory_M;
		CString sMemo_M;
		CString sDate_M;

		m_cbSpendIncome_M.GetWindowText(sSpendIncome_M);
		m_edMoney_M.GetWindowText(sMoney_M);
		m_cbMainCategory_M.GetWindowText(sMainCategory_M);
		m_cbSubCategory_M.GetWindowText(sSubCategory_M);
		m_edMemo_M.GetWindowText(sMemo_M);
		m_dtpDate_M.GetWindowText(sDate_M);

		((CSpendDlg*)GetParent())->m_lcSpend.SetItemText(((CSpendDlg*)GetParent())->m_iSelect, 1, sDate_M);
		((CSpendDlg*)GetParent())->m_lcSpend.SetItemText(((CSpendDlg*)GetParent())->m_iSelect, 2, sSpendIncome_M);
		((CSpendDlg*)GetParent())->m_lcSpend.SetItemText(((CSpendDlg*)GetParent())->m_iSelect, 3, sMoney_M);
		((CSpendDlg*)GetParent())->m_lcSpend.SetItemText(((CSpendDlg*)GetParent())->m_iSelect, 4, sMainCategory_M);
		((CSpendDlg*)GetParent())->m_lcSpend.SetItemText(((CSpendDlg*)GetParent())->m_iSelect, 5, sSubCategory_M);
		((CSpendDlg*)GetParent())->m_lcSpend.SetItemText(((CSpendDlg*)GetParent())->m_iSelect, 6, sMemo_M);

		EndDialog(0);
	}

}

//기본 수정
void CModifyDlg::OnBnClickedButtonTestModifyM()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString sSpendIncome_M;
	CString sMoney_M;
	CString sMainCategory_M;
	CString sSubCategory_M;
	CString sMemo_M;
	CString sDate_M;

	m_cbSpendIncome_M.GetWindowText(sSpendIncome_M);
	m_edMoney_M.GetWindowText(sMoney_M);
	m_cbMainCategory_M.GetWindowText(sMainCategory_M);
	m_cbSubCategory_M.GetWindowText(sSubCategory_M);
	m_edMemo_M.GetWindowText(sMemo_M);
	m_dtpDate_M.GetWindowText(sDate_M);

	m_lcSpend_M.SetItemText(0, 1, sDate_M);
	m_lcSpend_M.SetItemText(0, 2, sSpendIncome_M);
	m_lcSpend_M.SetItemText(0, 3, sMoney_M);
	m_lcSpend_M.SetItemText(0, 4, sMainCategory_M);
	m_lcSpend_M.SetItemText(0, 5, sSubCategory_M);
	m_lcSpend_M.SetItemText(0, 6, sMemo_M);

	DisplaySumM();
}
