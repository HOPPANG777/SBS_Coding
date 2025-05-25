#pragma once


// CModifyDlg 대화 상자
class CSpendDlg;

class CModifyDlg : public CDialog
{
	DECLARE_DYNAMIC(CModifyDlg)

private:
	CSpendDlg* m_pParentWnd;
public:
	CModifyDlg(CSpendDlg* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CModifyDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MODIFY_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	HICON m_hIcon_M;
	DECLARE_MESSAGE_MAP()

public: 
	virtual BOOL OnInitDialog();


	CListCtrl m_lcSpend_M;
	CComboBox m_cbSpendIncome_M;
	CEdit m_edMoney_M;
	CComboBox m_cbMainCategory_M;
	CComboBox m_cbSubCategory_M;
	CEdit m_edMemo_M;
	CDateTimeCtrl m_dtpDate_M;
	CStatic m_stDisp_M;

	void DisplaySumM();
	void RelocateLIsttoM();

	afx_msg void OnCbnSelchangeComboSpendIncomeM();
	afx_msg void OnCbnSelchangeComboMainCategoryM();
	afx_msg void OnBnClickedButtonDeleteM();
	afx_msg void OnBnClickedButtonModifyM();
	afx_msg void OnBnClickedButtonTestModifyM();
};
