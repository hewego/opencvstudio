#pragma once
#include "afxdialogex.h"


class CDlgFunMatch : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFunMatch)

public:
	CDlgFunMatch(CWnd* pParent = nullptr);
	virtual ~CDlgFunMatch();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FUN_MATCH };
#endif

private:
	CGridCtrl m_GridResult;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMfcbuttonLoad();
	afx_msg void OnBnClickedMfcbuttonApply();

private:
	struct stFind_t {
		cv::Point pt;
		DOUBLE socore;
	};

private:
	hhLibImageControlUI m_hhImage;
	cv::Mat m_matMark;
	cv::Mat m_matSrc;
	UINT m_nTestType;
	vector<stFind_t> vFind;

private:
	void InitGrid(int nRowCount);
};
