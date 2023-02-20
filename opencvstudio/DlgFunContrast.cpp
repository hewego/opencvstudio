
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
	DDX_Control(pDX, IDC_SLIDER_BRIGHTNESS, m_SliderBrightness);
	DDX_Control(pDX, IDC_SLIDER_CONTRAST, m_SliderContrast);
}


BEGIN_MESSAGE_MAP(CDlgFunContrast, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_APPLY, &CDlgFunContrast::OnBnClickedMfcbuttonApply)
	ON_WM_HSCROLL()
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


	m_SliderBrightness.SetRange(0, 255);
	SetDlgItemText(IDC_EDIT_BRIGHTNESS, 0);

	int range = RANGE_SLIDER_CONTRAST;
	m_SliderContrast.SetRange(0, range);
	//m_SliderContrast.SetTicFreq(range/2);
	m_SliderContrast.SetPos(range / 2);

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgFunContrast::OnBnClickedMfcbuttonApply()
{
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}

	//cv::cvtColor(matSrc, matSrc, CV_BGR2GRAY);

	CString str;
	GetDlgItemText(IDC_EDIT_ALPHA, str);
	double dbAlpha = _str2db(str);
	int nBeta = GetDlgItemInt(IDC_EDIT_BETA);

	_debugLog(LOG_MAIN, _T("contrast begin"));

	cv::Mat matDst = cv::Mat::zeros(matSrc.size(), matSrc.type());

	if (matSrc.type() == CV_8UC1) 
	{
		for (int y = 0; y < matSrc.rows; y++) {
			for (int x = 0; x < matSrc.cols; x++) {
				matDst.at<uchar>(y, x) = saturate_cast<uchar>(dbAlpha * (matSrc.at<uchar>(y, x)) + nBeta);
			}
		}
	}
	else if (matSrc.type() == CV_8UC3)
	{
		for (int y = 0; y < matSrc.rows; ++y) {
			for (int x = 0; x < matSrc.cols; ++x) {
				for (int c = 0; c < matSrc.channels(); ++c)
				{
					matDst.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(dbAlpha * (matSrc.at<Vec3b>(y, x)[c]) + nBeta);
				}
			}
		}
	}

	_debugLog(LOG_MAIN, _T("contrast end"));

	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matDst);
	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].ShowWindow(SW_SHOW);
}


void CDlgFunContrast::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar)
	{
		if (pScrollBar == (CScrollBar*)&m_SliderBrightness)
		{
			int nPos = m_SliderBrightness.GetPos();
			SetDlgItemText(IDC_EDIT_BRIGHTNESS, _int2str(nPos));
			SetBrightness(nPos);
		}
		else if (pScrollBar == (CScrollBar*)&m_SliderContrast)
		{
			int nPos = m_SliderContrast.GetPos();

			DOUBLE dbVal = (DOUBLE)nPos / 100;
			SetDlgItemText(IDC_EDIT_CONTRAST, _db2str(dbVal));
			SetContrast(dbVal);
		}
	}
	else
	{
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CDlgFunContrast::SetBrightness(int val)
{
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}

	cv::Mat matDst = cv::Mat::zeros(matSrc.size(), matSrc.type());

	if (matSrc.type() == CV_8UC1)
	{
		for (int y = 0; y < matSrc.rows; y++) {
			for (int x = 0; x < matSrc.cols; x++) {
				matDst.at<uchar>(y, x) = saturate_cast<uchar>(matSrc.at<uchar>(y, x) + val);
			}
		}
	}
	else if (matSrc.type() == CV_8UC3)
	{
		for (int y = 0; y < matSrc.rows; ++y) {
			for (int x = 0; x < matSrc.cols; ++x) {
				for (int c = 0; c < matSrc.channels(); ++c) {
					matDst.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(matSrc.at<Vec3b>(y, x)[c] + val);
				}
			}
		}
	}

	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matDst);
	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].ShowWindow(SW_SHOW);
}


void CDlgFunContrast::SetContrast(DOUBLE val)
{
	/*
	# 영상의 밝고 어두움의 비율
	# 명암비가 크다 = 영상이 선명하다
	# 명암비가 작다 = 영상이 뿌옇다
	# g(x, y) = f(x, y) + a * (f(x, y) - 128)
		# -1 <= a <=0 명암비 감소
		# 0 <= a <= 1 명암비 증가
	*/

	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}

	cv::Mat matDst = cv::Mat::zeros(matSrc.size(), matSrc.type());

	if (matSrc.type() == CV_8UC1)
	{
		for (int y = 0; y < matSrc.rows; y++) {
			for (int x = 0; x < matSrc.cols; x++) {
				//matDst.at<uchar>(y, x) = saturate_cast<uchar>(matSrc.at<uchar>(y, x) + val);
				matDst.at<uchar>(y, x) = saturate_cast<uchar>(matSrc.at<uchar>(y, x) + (val * (matSrc.at<uchar>(y, x) - 128)));
			}
		}
	}
	else if (matSrc.type() == CV_8UC3)
	{
		for (int y = 0; y < matSrc.rows; ++y) {
			for (int x = 0; x < matSrc.cols; ++x) {
				for (int c = 0; c < matSrc.channels(); ++c) {
					matDst.at<Vec3b>(y, x)[c] = saturate_cast<uchar>(matSrc.at<Vec3b>(y, x)[c] + (val * (matSrc.at<Vec3b>(y, x)[c] - 128)));
				}
			}
		}
	}

	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matDst);
	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].ShowWindow(SW_SHOW);
}