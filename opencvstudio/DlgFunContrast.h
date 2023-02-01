#pragma once
#include "afxdialogex.h"


class CDlgFunContrast : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFunContrast)

public:
	CDlgFunContrast(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgFunContrast();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FUN_CONTRAST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMfcbuttonApply();
};
