#pragma once
#include "afxdialogex.h"


// CDlgFunFilter 대화 상자

class CDlgFunFilter : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFunFilter)

public:
	CDlgFunFilter(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgFunFilter();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FUN_FILTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonApplyCanny();
	afx_msg void OnBnClickedButtonApplyErosion();
};
