
// SpendDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxdtctl.h"
#include "CModifyDlg.h"


// CSpendDlg 대화 상자
class CSpendDlg : public CDialogEx
{
// 생성입니다.
public:
	CSpendDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SPEND_DIALOG };

#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	CListCtrl m_lcSpend;
	CComboBox m_cbSpendIncome;
	CEdit m_edMoney;
	CComboBox m_cbMainCategory;
	CComboBox m_cbSubCategory;
	CEdit m_edMemo;
	CDateTimeCtrl m_dtpDate;
	CStatic m_stDisp;

	int m_iSelect;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonMake();
	afx_msg void OnBnClickedButtonModify();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnNMClickListSpend( NMHDR *pNMHDR, LRESULT *pResult );

	void DisplaySum();

	afx_msg void OnCbnSelchangeComboSpendIncome();
	afx_msg void OnCbnSelchangeComboMainCategory();

	void ModifyDlgfix();

	void Save();
	void Load();

	int m_nSortColumn;
	BOOL m_bAscending;

	afx_msg void OnLvnColumnclickListSpend(NMHDR* pNMHDR, LRESULT* pResult);
	static int CALLBACK CompareFunc(LPARAM iParam1, LPARAM iParam2, LPARAM iParam);

	struct SORTPARAM
	{
		int iSortColumn;
		bool bSortDirect;
		CListCtrl* pList;
	};
};
