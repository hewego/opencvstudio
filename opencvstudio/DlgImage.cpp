#include "pch.h"
#include "opencvstudio.h"
#include "afxdialogex.h"
#include "DlgImage.h"

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_IMAGE, pParent)
{
}


CDlgImage::~CDlgImage()
{
}


void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
END_MESSAGE_MAP()


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_hhImage.Init(GetDlgItem(IDC_STATIC_IMAGE), 1, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
}


BOOL CDlgImage::PreTranslateMessage(MSG* pMsg)
{

	return CDialogEx::PreTranslateMessage(pMsg);
}
