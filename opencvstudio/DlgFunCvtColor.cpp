
#include "pch.h"
#include "opencvstudio.h"
#include "OpencvstudioDlg.h"
#include "afxdialogex.h"
#include "DlgFunCvtColor.h"


IMPLEMENT_DYNAMIC(CDlgFunCvtColor, CDialogEx)

CDlgFunCvtColor::CDlgFunCvtColor(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FUN_CVTCOLOR, pParent)
{

}

CDlgFunCvtColor::~CDlgFunCvtColor()
{
}

void CDlgFunCvtColor::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgFunCvtColor, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_APPLY, &CDlgFunCvtColor::OnBnClickedMfcbuttonApply)
END_MESSAGE_MAP()


BOOL CDlgFunCvtColor::OnInitDialog()
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
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->AddString(_T("CV_BGR2GRAY"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->AddString(_T("CV_BGR2XYZ"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->AddString(_T("CV_BGR2HSV"));

	return TRUE;
}


void CDlgFunCvtColor::OnBnClickedMfcbuttonApply()
{
	//Input
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}

	cv::Mat matDst;

	try 
	{
		int nMethod;
		CString str;
		GetDlgItemText(IDC_COMBO_METHOD, str);
		if (str == _T("CV_BGR2GRAY"))		nMethod = CV_BGR2GRAY;
		else if (str == _T("CV_BGR2XYZ"))	nMethod = CV_BGR2XYZ;
		else if (str == _T("CV_BGR2HSV"))	nMethod = CV_BGR2HSV;
		else return;
		cv::cvtColor(matSrc, matDst, nMethod);
	}
	catch (const std::exception&) 
	{
		AfxMessageBox(_T("Thrown an exception"), MB_ICONSTOP);
		return;
	}

	//Output
	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matDst);
}
