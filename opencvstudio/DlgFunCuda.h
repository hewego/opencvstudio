#pragma once
#include "afxdialogex.h"


class CDlgFunCuda : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFunCuda)

public:
	CDlgFunCuda(CWnd* pParent = nullptr);
	virtual ~CDlgFunCuda();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FUN_CUDA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMfcbuttonRotate();
	afx_msg void OnBnClickedMfcbuttonRotateCuda();
	afx_msg void OnBnClickedMfcbuttonRotate2();
	afx_msg void OnBnClickedMfcbuttonRotate3();
	afx_msg void OnBnClickedMfcbuttonMorp();

private:
	static const int STREAM_COUNT = 2;

private:
	static UINT Thread1(LPVOID pParam);
	static UINT Thread2(LPVOID pParam);
	void RunMorph2(int nStream);
	void RunMorph3(int nStream);
};
