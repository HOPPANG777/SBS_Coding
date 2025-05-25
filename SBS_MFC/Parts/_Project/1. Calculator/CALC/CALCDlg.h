
// CALCDlg.h : 헤더 파일
//

#pragma once


// CCALCDlg 대화 상자
class CCALCDlg : public CDialog
{
// 생성입니다.
public:
	CCALCDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_CALC_DIALOG };

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
	enum
	{
		PLUS,
		MINUS,
		MULTI,
		DIVIDE
	};
	
	int _inputNumber;
	int _operator;

	CString _szInput;
	afx_msg void OnBnClickedNumber0();
	afx_msg void OnBnClickedNumber1();
	afx_msg void OnBnClickedNumber2();
	afx_msg void OnBnClickedNumber3();
	afx_msg void OnBnClickedNumber4();
	afx_msg void OnBnClickedNumber5();
	afx_msg void OnBnClickedNumber6();
	afx_msg void OnBnClickedNumber7();
	afx_msg void OnBnClickedNumber8();
	afx_msg void OnBnClickedNumber9();
	afx_msg void OnBnClickedBacks();
	afx_msg void OnBnClickedClear();
	
	afx_msg void OnBnClickedPlus();
	afx_msg void OnBnClickedMul();
	afx_msg void OnBnClickedMinus();
	afx_msg void OnBnClickedDiv();
	afx_msg void OnBnClickedEq();
};
