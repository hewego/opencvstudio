
#include "pch.h"
#include "opencvstudio.h"
#include "OpencvstudioDlg.h"
#include "afxdialogex.h"
#include "DlgFunUsbCamera.h"

IMPLEMENT_DYNAMIC(CDlgFunUsbCamera, CDialogEx)

CDlgFunUsbCamera::CDlgFunUsbCamera(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FUN_USBCAMERA, pParent)
{
	m_bShot = FALSE;
}

CDlgFunUsbCamera::~CDlgFunUsbCamera()
{
}

void CDlgFunUsbCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgFunUsbCamera, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_GRAB, &CDlgFunUsbCamera::OnBnClickedMfcbuttonGrab)
	ON_BN_CLICKED(IDC_MFCBUTTON_OPEN, &CDlgFunUsbCamera::OnBnClickedMfcbuttonOpen)
	ON_BN_CLICKED(IDC_MFCBUTTON_SHOT, &CDlgFunUsbCamera::OnBnClickedMfcbuttonShot)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MFCBUTTON_TO_IMAGE, &CDlgFunUsbCamera::OnBnClickedMfcbuttonToImage)
	ON_CBN_SELCHANGE(IDC_COMBO_EXPOSURE, &CDlgFunUsbCamera::OnCbnSelchangeComboExposure)
END_MESSAGE_MAP()


BOOL CDlgFunUsbCamera::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_hhImage.Init(GetDlgItem(IDC_STATIC_IMAGE), 1, 0);
	
	return TRUE;
}


void CDlgFunUsbCamera::OnBnClickedMfcbuttonOpen()
{
	int select = ((CComboBox*)GetDlgItem(IDC_COMBO_DEVICE))->GetCurSel();

	m_cam.open(select);
	if (!m_cam.isOpened()) {
		AfxMessageBox(_T("camera open fail"));
		return;
	}

	GetDlgItem(IDC_MFCBUTTON_OPEN)->EnableWindow(FALSE);
}


void CDlgFunUsbCamera::OnBnClickedMfcbuttonGrab()
{
	if (!m_cam.isOpened()) {
		AfxMessageBox(_T("camera not open"));
		return;
	}

	if (!m_bShot) {
		GetDlgItem(IDC_MFCBUTTON_GRAB)->SetWindowText(_T("Stop"));
		SetTimer(0, 10, NULL);
		m_bShot = TRUE;
	}
	else {
		GetDlgItem(IDC_MFCBUTTON_GRAB)->SetWindowText(_T("Grab"));
		KillTimer(0);
		m_bShot = FALSE;
	}
}


void CDlgFunUsbCamera::OnBnClickedMfcbuttonShot()
{
	if (!m_cam.isOpened()) {
		AfxMessageBox(_T("camera not open"));
		return;
	}

	m_matImg = cv::Scalar(0);
	m_cam >> m_matImg;
	if (m_cam.read(m_matImg))
	{
		m_hhImage.SetImage(m_matImg);
		//cv::imshow("image", m_matImg);
		_debugLog(LOG_MAIN, _T("grab ok"));
	}
}


void CDlgFunUsbCamera::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0)
	{
		KillTimer(0);

		OnBnClickedMfcbuttonShot();

		SetTimer(0, 25, NULL);
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CDlgFunUsbCamera::OnBnClickedMfcbuttonToImage()
{
	if (!m_cam.isOpened()) {
		AfxMessageBox(_T("camera not open"));
		return;
	}

	cv::Mat matImg = m_hhImage.GetImage();
	theDlg->m_DlgImg[0].SetImage(matImg);
	theDlg->m_DlgImg[0].ShowWindow(SW_SHOW);
}


BOOL CDlgFunUsbCamera::SetExpousertime(int no)
{
	DOUBLE dbVal = 0;
	switch (no)
	{
	case 0:	 dbVal = -1; break;
	case 1:	 dbVal = -2; break;
	case 2:	 dbVal = -3; break;
	case 3:	 dbVal = -4; break;
	case 4:	 dbVal = -5; break;
	case 5:	 dbVal = -6; break;
	case 6:	 dbVal = -7; break;
	case 7:	 dbVal = -8; break;
	case 8:	 dbVal = -9; break;
	case 9:	 dbVal = -10; break;
	case 10: dbVal = -11; break;
	case 11: dbVal = -12; break;
	case 12: dbVal = -13; break;
	default: return FALSE;
	}
	
	BOOL result = m_cam.set(CAP_PROP_EXPOSURE, dbVal);
	
	return result;
}

void CDlgFunUsbCamera::OnCbnSelchangeComboExposure()
{
	int select = ((CComboBox*)GetDlgItem(IDC_COMBO_EXPOSURE))->GetCurSel();
	SetExpousertime(select);
}