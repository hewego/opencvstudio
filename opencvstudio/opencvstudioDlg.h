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
	virtual void OnCancel();
	afx_msg void OnBnClickedMfcbuttonFunTh();
	afx_msg void OnBnClickedMfcbuttonFunAth();
	afx_msg void OnBnClickedMfcbuttonFunOperation();
	afx_msg void OnBnClickedMfcbuttonFunContrast();
	afx_msg void OnBnClickedMfcbuttonFunCvtcolor();
	afx_msg void OnBnClickedMfcbuttonFunFilter();
	afx_msg void OnBnClickedMfcbuttonFunMorp();
	afx_msg void OnBnClickedMfcbuttonFunCuda();
	afx_msg void OnBnClickedMfcbuttonFunMatch();

private:
	CString GetVer();
	CString GetDate();

public:
	CDlgImage m_DlgImg[DEF_MAX_VIEW];
	CObList m_oblist_dlg_th;
	CObList m_oblist_dlg_ath;
	CObList m_oblist_dlg_Operation;
	CObList m_oblist_dlg_Contrast;
	CObList m_oblist_dlg_CvtColor;
	CObList m_oblist_dlg_Filter;
	CObList m_oblist_dlg_Morp;
	CObList m_oblist_dlg_Cuda;
	CObList m_oblist_dlg_Match;

public:
	void ResetDlg();
	void SetLog(CString sLog);
};
