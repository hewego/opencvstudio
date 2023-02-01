#pragma once
#include "afxdialogex.h"


class CDlgFunCvtColor : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFunCvtColor)

public:
	CDlgFunCvtColor(CWnd* pParent = nullptr);
	virtual ~CDlgFunCvtColor();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FUN_CVTCOLOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedMfcbuttonApply();
};
