
#include "pch.h"
#include "opencvstudio.h"
#include "OpencvstudioDlg.h"
#include "afxdialogex.h"
#include "DlgFunContrast.h"


IMPLEMENT_DYNAMIC(CDlgFunContrast, CDialogEx)

CDlgFunContrast::CDlgFunContrast(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FUN_CONTRAST, pParent)
{

}

CDlgFunContrast::~CDlgFunContrast()
{
}

void CDlgFunContrast::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgFunContrast, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_APPLY, &CDlgFunContrast::OnBnClickedMfcbuttonApply)
END_MESSAGE_MAP()


BOOL CDlgFunContrast::OnInitDialog()
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

	SetDlgItemText(IDC_EDIT_ALPHA, _T("1.0"));
	SetDlgItemInt(IDC_EDIT_BETA, 0);

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgFunContrast::OnBnClickedMfcbuttonApply()
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

	double dbAlpha = GetDlgItemInt(IDC_EDIT_ALPHA);
	int nBeta = GetDlgItemInt(IDC_EDIT_BETA);

	cv::Mat matDst = cv::Mat::zeros(matSrc.size(), matSrc.type());
	_debugLog(LOG_MAIN, _T("contrast begin"));
	for (int y = 0; y < matSrc.rows; y++) {
		for (int x = 0; x < matSrc.cols; x++) {
			matDst.at<uchar>(y, x) = saturate_cast<uchar>(dbAlpha * (matSrc.at<uchar>(y, x)) + nBeta);
		}
	}
	_debugLog(LOG_MAIN, _T("contrast end"));

	//Output
	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matDst);
}
