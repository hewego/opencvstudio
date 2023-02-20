#pragma once
#include "afxdialogex.h"

class CDlgFunContours : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFunContours)

public:
	CDlgFunContours(CWnd* pParent = nullptr);
	virtual ~CDlgFunContours();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FUN_CONTOURS };
#endif

private:
	CGridCtrl m_GridContour;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMfcbuttonApply();
	afx_msg void OnGridClickContour(NMHDR* pNotifyStruct, LRESULT* pResult);

private:
	void InitGridContours(int nRowCount);

private:
	vector<vector<cv::Point>> m_vContours;
};
