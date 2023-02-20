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
	ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString str;
	str.Format(_T("Image %d"), m_nNo);
	SetWindowText(str);

	m_hhImage.Init(GetDlgItem(IDC_STATIC_IMAGE), 1, 0);

	return TRUE;
}


BOOL CDlgImage::PreTranslateMessage(MSG* pMsg)
{

	return CDialogEx::PreTranslateMessage(pMsg);
}


cv::Mat CDlgImage::GetImage()
{
	return m_hhImage.GetImage();
}


void CDlgImage::SetImage(cv::Mat mImg)
{
	m_hhImage.SetImage(mImg);
}


void CDlgImage::OnSize(UINT nType, int cx, int cy)
{
	if (GetDlgItem(IDC_STATIC_IMAGE)->GetSafeHwnd() == NULL) {
		return;
	}

	CRect rt;
	GetWindowRect(rt);
	ScreenToClient(rt);

	CRect rcPic;
	GetDlgItem(IDC_STATIC_IMAGE)->GetClientRect(&rcPic);
	ScreenToClient(&rcPic);

	GetDlgItem(IDC_STATIC_IMAGE)->SetWindowPos(NULL, rcPic.left, rcPic.top, rt.Width() - 29, rt.Height() - 53, SWP_NOMOVE);
	m_hhImage.SendMessage(WM_SIZE);

	CDialogEx::OnSize(nType, cx, cy);
}


void CDlgImage::Init(int nNo)
{
	m_nNo = nNo;
}