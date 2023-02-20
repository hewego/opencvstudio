#pragma once
#include "afxdialogex.h"


class CDlgFunContrast : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFunContrast)

public:
	CDlgFunContrast(CWnd* pParent = nullptr);
	virtual ~CDlgFunContrast();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FUN_CONTRAST };
#endif

private:
	static const int RANGE_SLIDER_CONTRAST = 200;

private:
	CSliderCtrl m_SliderBrightness;
	CSliderCtrl m_SliderContrast;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMfcbuttonApply();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

private:
	void SetBrightness(int val);
	void SetContrast(DOUBLE val);
};
