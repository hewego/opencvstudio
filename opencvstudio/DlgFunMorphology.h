#pragma once
#include "afxdialogex.h"

class CDlgFunMorphology : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFunMorphology)

public:
	CDlgFunMorphology(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgFunMorphology();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FUN_MORPHOLOGY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMfcbuttonApply();
};
