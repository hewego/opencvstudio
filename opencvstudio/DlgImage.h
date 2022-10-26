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

	DECLARE_MESSAGE_MAP()

private:
	hhLibImageControlUI m_hhImage;
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
