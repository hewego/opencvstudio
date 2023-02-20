#pragma once
#include "afxdialogex.h"


class CDlgFunLabel : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFunLabel)

public:
	CDlgFunLabel(CWnd* pParent = nullptr);
	virtual ~CDlgFunLabel();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FUN_LABEL };
#endif

private:
	CGridCtrl m_GridLabels;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonLabelReset();
	afx_msg void OnBnClickedMfcbuttonApply();
	afx_msg void OnBnClickedBlobInfo(NMHDR* pNotifyStruct, LRESULT* pResult);

private:
	cv::Mat m_matGray;
	cv::Mat m_matColor;
	cv::Mat m_MatLabel;
	int m_numOfLables;
	vector<cv::Vec3b> m_colors;

private:
	void InitGrid(int nRowCount);
};
