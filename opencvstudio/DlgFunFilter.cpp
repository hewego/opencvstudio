
#include "pch.h"
#include "opencvstudio.h"
#include "OpencvstudioDlg.h"
#include "afxdialogex.h"
#include "DlgFunFilter.h"

IMPLEMENT_DYNAMIC(CDlgFunFilter, CDialogEx)

CDlgFunFilter::CDlgFunFilter(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FUN_FILTER, pParent)
{

}

CDlgFunFilter::~CDlgFunFilter()
{
}

void CDlgFunFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgFunFilter, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_CANNY, &CDlgFunFilter::OnBnClickedButtonApplyCanny)
	ON_BN_CLICKED(IDC_BUTTON_APPLY_EROSION, &CDlgFunFilter::OnBnClickedButtonApplyErosion)
END_MESSAGE_MAP()


BOOL CDlgFunFilter::OnInitDialog()
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

	//Canny
	SetDlgItemText(IDC_EDIT_CANNY_TH1, _T("50"));
	SetDlgItemText(IDC_EDIT_CANNY_TH2, _T("200"));

	//Erosion
	SetDlgItemText(IDC_EDIT_EROSION_KERNAL1, _T("3"));
	SetDlgItemText(IDC_EDIT_EROSION_KERNAL2, _T("3"));
	SetDlgItemText(IDC_EDIT_EROSION_ITER, _T("1"));

	//Dilation
	SetDlgItemText(IDC_EDIT_DILATION_KERNAL1, _T("3"));
	SetDlgItemText(IDC_EDIT_DILATION_KERNAL2, _T("3"));
	SetDlgItemText(IDC_EDIT_DILATION_ITER, _T("1"));

	//GaussianBlur
	SetDlgItemText(IDC_EDIT_GAUSSIANBLUR_KSIZE, _T("3"));
	SetDlgItemText(IDC_EDIT_GAUSSIANBLUR_SIGMAX, _T("1"));
	SetDlgItemText(IDC_EDIT_GAUSSIANBLUR_SIGMAY, _T("1"));

	//MedianBlur
	SetDlgItemText(IDC_EDIT_MEDIANBLUR_KSIZE, _T("3"));

	//Gaber
	SetDlgItemText(IDC_EDIT_GABER_KSIZE, _T("11"));
	SetDlgItemText(IDC_EDIT_GABER_SIGMA, _T("3.12"));
	SetDlgItemText(IDC_EDIT_GABER_THETA, _T("4"));
	SetDlgItemText(IDC_EDIT_GABER_LAMBDA, _T("8"));
	SetDlgItemText(IDC_EDIT_GABER_GAMMA, _T("0.85"));
	SetDlgItemText(IDC_EDIT_GABER_PSI, _T("3.14"));
	(((CButton*)GetDlgItem(IDC_RADIO_GABER_KTYPE1))->SetCheck(1));

	//Sobel
	SetDlgItemText(IDC_EDIT_SOBEL_DEPTH, _T("-1"));
	SetDlgItemText(IDC_EDIT_SOBEL_SCALE, _T("1"));
	SetDlgItemText(IDC_EDIT_SOBEL_DELTA, _T("0"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SOBEL_DX))->InsertString(0, _T("0"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SOBEL_DX))->InsertString(1, _T("1"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SOBEL_DX))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_SOBEL_DY))->InsertString(0, _T("0"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SOBEL_DY))->InsertString(1, _T("1"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SOBEL_DY))->SetCurSel(1);
	((CComboBox*)GetDlgItem(IDC_COMBO_SOBEL_KSIZE))->InsertString(0, _T("1"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SOBEL_KSIZE))->InsertString(1, _T("3"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SOBEL_KSIZE))->InsertString(2, _T("5"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SOBEL_KSIZE))->InsertString(3, _T("7"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SOBEL_KSIZE))->SetCurSel(1);
	((CComboBox*)GetDlgItem(IDC_COMBO_SOBEL_BORDERTYPE))->InsertString(0, _T("BORDER_DEFAULT"));
	((CComboBox*)GetDlgItem(IDC_COMBO_SOBEL_BORDERTYPE))->SetCurSel(0);

	//Scharr
	(((CButton*)GetDlgItem(IDC_RADIO_SCHARR_AXIS_X))->SetCheck(1));

	//Prewitt
	(((CButton*)GetDlgItem(IDC_RADIO_PREWITT_AXIS_X))->SetCheck(1));

	//Roberts
	(((CButton*)GetDlgItem(IDC_RADIO_ROBERTS_AXIS_X))->SetCheck(1));

	return TRUE;
}


void CDlgFunFilter::OnBnClickedButtonApplyCanny()
{
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}

	cv::Mat matDst;
	_debugLog(LOG_MAIN, _T("Canny S"));
	double th1 = _getDlgItemDb(this, IDC_EDIT_CANNY_TH1);
	double th2 = _getDlgItemDb(this, IDC_EDIT_CANNY_TH2);
	cv::Canny(matSrc, matDst, th1, th2);
	_debugLog(LOG_MAIN, _T("Canny E"));

	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matDst);
}


void CDlgFunFilter::OnBnClickedButtonApplyErosion()
{
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}

	int nK1 = _makeOdd(_getDlgItemInt(this, IDC_EDIT_EROSION_KERNAL1));
	int nK2 = _makeOdd(_getDlgItemInt(this, IDC_EDIT_EROSION_KERNAL2));
	int nIterations = _getDlgItemInt(this, IDC_EDIT_EROSION_ITER);

	cv::Mat matDst;
	_debugLog(LOG_MAIN, _T("Erode S"));
	cv::Mat kernel(nK1, nK2, CV_8UC1, Scalar(255));
	cv::erode(matSrc, matDst, kernel, cv::Point(-1, -1), nIterations);
	_debugLog(LOG_MAIN, _T("Erode E"));

	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matDst);
}
