#pragma once
#include "afxdialogex.h"

class CDlgFunThreshold : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFunThreshold)

public:
	CDlgFunThreshold(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgFunThreshold();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FUN_THRESHOLD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
