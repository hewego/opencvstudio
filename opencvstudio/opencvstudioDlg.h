#pragma once

#include "DlgImage.h"

class COpencvstudioDlg : public CDialogEx
{
public:
	COpencvstudioDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENCVSTUDIO_DIALOG };
#endif

private:
	CListBox m_ListboxLog;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnViewImage1();
	afx_msg void OnViewImage2();
	afx_msg void OnViewImage3();
	afx_msg void OnViewImage4();
	afx_msg void OnViewImage5();
	afx_msg void OnViewImage6();
	afx_msg void OnBnClickedMfcbuttonFunTh();
	virtual void OnCancel();

public:
	CDlgImage m_DlgImg[DEF_MAX_VIEW];
	CObList m_oblist_dlgTh;
	CObList m_oblist_dlgATh;
	void ResetDlg();
	void SetLog(CString sLog);
	afx_msg void OnBnClickedMfcbuttonFunAth();
};
