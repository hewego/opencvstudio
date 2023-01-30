
#include "pch.h"
#include "opencvstudio.h"
#include "opencvstudioDlg.h"
#include "afxdialogex.h"
#include "DlgFunThreshold.h"

IMPLEMENT_DYNAMIC(CDlgFunThreshold, CDialogEx)

CDlgFunThreshold::CDlgFunThreshold(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FUN_THRESHOLD, pParent)
{

}


CDlgFunThreshold::~CDlgFunThreshold()
{
}


void CDlgFunThreshold::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgFunThreshold, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_APPLY, &CDlgFunThreshold::OnBnClickedMfcbuttonApply)
END_MESSAGE_MAP()


BOOL CDlgFunThreshold::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString str;
	for (int i = 0; i < DEF_MAX_VIEW; i++) {
		str.Format(_T("%02d"), i);
		((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->AddString(str);
		((CComboBox*)GetDlgItem(IDC_COMBO_DST))->AddString(str);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_DST))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(0, _T("CV_THRESH_BINARY"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(1, _T("CV_THRESH_BINARY_INV"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(2, _T("CV_THRESH_TRUNC"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(3, _T("CV_THRESH_TOZERO"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(4, _T("CV_THRESH_TOZERO_INV"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(5, _T("CV_THRESH_MASK"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(6, _T("CV_THRESH_OTSU"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(7, _T("CV_THRESH_TRIANGLE"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->SetCurSel(0);
	SetDlgItemInt(IDC_EDIT_TH, 10);
	SetDlgItemInt(IDC_EDIT_MV, 255);

	return TRUE;
}


void CDlgFunThreshold::OnBnClickedMfcbuttonApply()
{
	//Input
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}
	if (matSrc.type() != CV_8UC1) {
		cv::cvtColor(matSrc, matSrc, CV_BGR2GRAY);
	}

	int threshold = GetDlgItemInt(IDC_EDIT_TH);
	int maxval = GetDlgItemInt(IDC_EDIT_MV);
	int nType;
	switch (((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->GetCurSel())
	{
	case 0:	nType = CV_THRESH_BINARY; break;
	case 1:	nType = CV_THRESH_BINARY_INV; break;
	case 2:	nType = CV_THRESH_TRUNC; break;
	case 3:	nType = CV_THRESH_TOZERO; break;
	case 4:	nType = CV_THRESH_TOZERO_INV; break;
	case 5:	nType = CV_THRESH_MASK; break;
	case 6:	nType = CV_THRESH_OTSU; break;
	case 7:	nType = CV_THRESH_TRIANGLE; break;
	default: break;
	}

	cv::Mat matDst;

	try {
		_debugLog(LOG_MAIN, _T("Threshold begin"));
		cv::threshold(matSrc, matDst, threshold, maxval, nType);
		_debugLog(LOG_MAIN, _T("Threshold end"));
	}
	catch (const std::exception&) {
		AfxMessageBox(_T("Thrown an exception"), MB_ICONSTOP);
		return;
	}

	//Output
	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matDst);
}
