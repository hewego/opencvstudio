#pragma once
#include "afxdialogex.h"

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);
	virtual ~CDlgImage();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_IMAGE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()

private:
	hhLibImageControlUI m_hhImage;

public:
	cv::Mat GetImage();
	void SetImage(cv::Mat mImg);

	afx_msg void OnSize(UINT nType, int cx, int cy);
};
