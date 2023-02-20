
#include "pch.h"
#include "opencvstudio.h"
#include "OpencvstudioDlg.h"
#include "afxdialogex.h"
#include "DlgFunThresholdA.h"


IMPLEMENT_DYNAMIC(CDlgFunThresholdA, CDialogEx)

CDlgFunThresholdA::CDlgFunThresholdA(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FUN_THRESHOLDA, pParent)
{

}

CDlgFunThresholdA::~CDlgFunThresholdA()
{
}

void CDlgFunThresholdA::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgFunThresholdA, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_APPLY, &CDlgFunThresholdA::OnBnClickedMfcbuttonApply)
END_MESSAGE_MAP()


BOOL CDlgFunThresholdA::OnInitDialog()
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
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(0, _T("CV_ADAPTIVE_THRESH_MEAN_C"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(1, _T("CV_ADAPTIVE_THRESH_GAUSSIAN_C"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->InsertString(0, _T("CV_THRESH_BINARY"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->InsertString(1, _T("CV_THRESH_BINARY_INV"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->InsertString(2, _T("CV_THRESH_TRUNC"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->InsertString(3, _T("CV_THRESH_TOZERO"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->InsertString(4, _T("CV_THRESH_TOZERO_INV"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->InsertString(5, _T("CV_THRESH_MASK"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->InsertString(6, _T("CV_THRESH_OTSU"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->InsertString(7, _T("CV_THRESH_TRIANGLE"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->SetCurSel(0);
	SetDlgItemInt(IDC_EDIT_MV, 255);
	SetDlgItemInt(IDC_EDIT_BS, 55);
	SetDlgItemInt(IDC_EDIT_C, 10);

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgFunThresholdA::OnBnClickedMfcbuttonApply()
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

	double dbMaxVal = GetDlgItemInt(IDC_EDIT_MV);
	int nMethod;
	int nType;
	int nBlockSize = GetDlgItemInt(IDC_EDIT_BS);
	CString str;
	GetDlgItemText(IDC_EDIT_C, str);
	//double dbC = GetDlgItemInt(IDC_EDIT_C);
	double dbC = _ttof(str);

	//Block Size Interlock
	if (nBlockSize <= 1) {
		nBlockSize = 3;
		SetDlgItemInt(IDC_EDIT_BS, nBlockSize);
	}

	//Block Size 홀수
	int nOdd = nBlockSize % 2;
	if (nOdd == 0) {
		nBlockSize++;
		SetDlgItemInt(IDC_EDIT_BS, nBlockSize);
	}

	switch (((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->GetCurSel())
	{
	case 0:	nMethod = CV_ADAPTIVE_THRESH_MEAN_C; break;
	case 1:	nMethod = CV_ADAPTIVE_THRESH_GAUSSIAN_C; break;
	default: break;
	}

	switch (((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->GetCurSel())
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
		_debugLog(LOG_MAIN, _T("adaptiveThreshold begin"));
		cv::adaptiveThreshold(matSrc, matDst, dbMaxVal, nMethod, nType, nBlockSize, dbC);
		_debugLog(LOG_MAIN, _T("adaptiveThreshold end"));
	}
	catch (const std::exception&) {
		AfxMessageBox(_T("Thrown an exception"), MB_ICONSTOP);
	}

	//Output
	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matDst);
	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].ShowWindow(SW_SHOW);
}
