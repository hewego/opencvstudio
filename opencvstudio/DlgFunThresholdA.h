#pragma once
#include "afxdialogex.h"

class CDlgFunThresholdA : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFunThresholdA)

public:
	CDlgFunThresholdA(CWnd* pParent = nullptr);
	virtual ~CDlgFunThresholdA();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FUN_THRESHOLDA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMfcbuttonApply();
};
