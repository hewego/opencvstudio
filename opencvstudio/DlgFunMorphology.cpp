
#include "pch.h"
#include "opencvstudio.h"
#include "OpencvstudioDlg.h"
#include "afxdialogex.h"
#include "DlgFunMorphology.h"


IMPLEMENT_DYNAMIC(CDlgFunMorphology, CDialogEx)

CDlgFunMorphology::CDlgFunMorphology(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FUN_MORPHOLOGY, pParent)
{

}

CDlgFunMorphology::~CDlgFunMorphology()
{
}

void CDlgFunMorphology::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgFunMorphology, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_APPLY, &CDlgFunMorphology::OnBnClickedMfcbuttonApply)
END_MESSAGE_MAP()


BOOL CDlgFunMorphology::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString str;
	for (int i = 0; i < DEF_MAX_VIEW; i++) {
		str.Format(_T("%02d"), i);
		((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->AddString(str);
		((CComboBox*)GetDlgItem(IDC_COMBO_DST))->AddString(str);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_DST))->SetCurSel(1);

	SetDlgItemInt(IDC_EDIT_K_SIZE, 1);

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgFunMorphology::OnBnClickedMfcbuttonApply()
{
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}

	int nMethod;
	if (((CButton*)GetDlgItem(IDC_RADIO_METHOD_1))->GetCheck())		nMethod = MorphTypes::MORPH_ERODE;
	else if (((CButton*)GetDlgItem(IDC_RADIO_METHOD_2))->GetCheck())	nMethod = MorphTypes::MORPH_DILATE;
	else if (((CButton*)GetDlgItem(IDC_RADIO_METHOD_3))->GetCheck())	nMethod = MorphTypes::MORPH_OPEN;
	else if (((CButton*)GetDlgItem(IDC_RADIO_METHOD_4))->GetCheck())	nMethod = MorphTypes::MORPH_CLOSE;
	else if (((CButton*)GetDlgItem(IDC_RADIO_METHOD_5))->GetCheck())	nMethod = MorphTypes::MORPH_GRADIENT;
	else if (((CButton*)GetDlgItem(IDC_RADIO_METHOD_6))->GetCheck())	nMethod = MorphTypes::MORPH_TOPHAT;
	else if (((CButton*)GetDlgItem(IDC_RADIO_METHOD_7))->GetCheck())	nMethod = MorphTypes::MORPH_BLACKHAT;
	else if (((CButton*)GetDlgItem(IDC_RADIO_METHOD_8))->GetCheck())	nMethod = MorphTypes::MORPH_HITMISS;
	else {
		AfxMessageBox(_T("Error"));
		return;
	}

	cv::Mat matDst;

	try {
		int nK = GetDlgItemInt(IDC_EDIT_K_SIZE);
		Mat matKernel(nK, nK, CV_8U, Scalar(1));
		_debugLog(LOG_MAIN, _T("morphology begin"));
		cv::morphologyEx(matSrc, matDst, nMethod, matKernel);
		_debugLog(LOG_MAIN, _T("morphology end"));
	}
	catch (const std::exception&) {
		AfxMessageBox(_T("Thrown an exception"), MB_ICONSTOP);
	}

	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matDst);
}
