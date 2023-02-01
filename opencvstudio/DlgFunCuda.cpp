
#include "pch.h"
#include "opencvstudio.h"
#include "OpencvstudioDlg.h"
#include "afxdialogex.h"
#include "DlgFunCuda.h"


IMPLEMENT_DYNAMIC(CDlgFunCuda, CDialogEx)

CDlgFunCuda::CDlgFunCuda(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FUN_CUDA, pParent)
{

}

CDlgFunCuda::~CDlgFunCuda()
{
}

void CDlgFunCuda::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgFunCuda, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_ROTATE, &CDlgFunCuda::OnBnClickedMfcbuttonRotate)
	ON_BN_CLICKED(IDC_MFCBUTTON_ROTATE_CUDA, &CDlgFunCuda::OnBnClickedMfcbuttonRotateCuda)
	ON_BN_CLICKED(IDC_MFCBUTTON_ROTATE2, &CDlgFunCuda::OnBnClickedMfcbuttonRotate2)
	ON_BN_CLICKED(IDC_MFCBUTTON_ROTATE3, &CDlgFunCuda::OnBnClickedMfcbuttonRotate3)
	ON_BN_CLICKED(IDC_MFCBUTTON_MORP, &CDlgFunCuda::OnBnClickedMfcbuttonMorp)
END_MESSAGE_MAP()


BOOL CDlgFunCuda::OnInitDialog()
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

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgFunCuda::OnBnClickedMfcbuttonRotate()
{
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}

	_debugLog(LOG_MAIN, _T("Rotate begin"));
	RotatedRect rotateBox;
	rotateBox.center.x = matSrc.cols / 2;
	rotateBox.center.y = matSrc.rows / 2;
	rotateBox.angle = 1;
	Mat matRot = getRotationMatrix2D(rotateBox.center, rotateBox.angle, 1);
	cv::Rect2f bbox = cv::RotatedRect(cv::Point2f(), matSrc.size(), rotateBox.angle).boundingRect2f();

	cv::Mat matDst;
	cv::warpAffine(matSrc, matDst, matRot, matSrc.size());
	_debugLog(LOG_MAIN, _T("Rotate end"));

	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matDst);
}


void CDlgFunCuda::OnBnClickedMfcbuttonRotateCuda()
{
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}

#ifdef USE_CUDA

	m_gmatSrc.upload(matLoad);
	//_DebugLog(_T("Mat->GMat"));

	RotatedRect rotateBox;
	rotateBox.center.x = matLoad.cols / 2;
	rotateBox.center.y = matLoad.rows / 2;
	rotateBox.angle = 1;
	Mat matRot = getRotationMatrix2D(rotateBox.center, rotateBox.angle, 1);
	//_DebugLog(_T("getRotationMatrix2D"));

	cv::cuda::warpAffine(m_gmatSrc, m_gmatDst, matRot, m_gmatSrc.size());
	//_DebugLog(_T("warpAffine"));

	cv::Mat matDst(m_gmatDst);
	_DebugLog(_T("end"));

	//Output
	theView->m_DlgMatView[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetMat(matDst);

#endif
}


void CDlgFunCuda::OnBnClickedMfcbuttonRotate2()
{
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}

	_debugLog(LOG_MAIN, _T("Bilateral begin"));
	int d = 31;
	double sigmaColor = 9;
	double sigmaspace = 7;
	int borderType = 4;
	cv::Mat matResult;
	cv::bilateralFilter(matSrc, matResult, d, sigmaColor, sigmaspace, borderType);
	_debugLog(LOG_MAIN, _T("Bilateral end"));

	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matResult);
}


void CDlgFunCuda::OnBnClickedMfcbuttonRotate3()
{
#ifdef USE_CUDA
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}
	_DebugLog(_T("Mat Load"));
	CQueryPerformanceTime time;
	_DebugLog(_T("Start [%04d]"), time.End());

	m_gmatLoad[0].upload(matSrc);

	int d = 31; //filtersize
	double sigmaColor = 9;
	double sigmaspace = 7;
	int borderType = 4;
	cv::cuda::bilateralFilter(m_gmatLoad[0], m_gmatLoad[1], d, sigmaColor, sigmaspace, borderType);
	_DebugLog(_T("End [%04d]"), time.End());

	cv::Mat matResult(m_gmatLoad[1]);

	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matResult);
#endif
}


void CDlgFunCuda::OnBnClickedMfcbuttonMorp()
{
	AfxBeginThread(Thread1, this);
	AfxBeginThread(Thread2, this);
}

UINT CDlgFunCuda::Thread1(LPVOID pParam)
{
	CDlgFunCuda* pParent = (CDlgFunCuda*)pParam;
	pParent->RunMorph2(0);
	return 0;
}

UINT CDlgFunCuda::Thread2(LPVOID pParam)
{
	CDlgFunCuda* pParent = (CDlgFunCuda*)pParam;
	pParent->RunMorph2(1);
	return 0;
}


void CDlgFunCuda::RunMorph2(int nStream)
{
#ifdef USE_CUDA

	theDlg->ResetLog();

	cv::Mat matLoad = theDlg->m_ImageView1.GetMat().clone();
	_DebugLog(_T("Morph Load"));

	for (int i = 0; i < STREAM_COUNT; i++) {
		m_gmatLoad[i].upload(matLoad);
	}
	_DebugLog(_T("Morph Upload"));

	CQueryPerformanceTime time;
	_DebugLog(_T("Morph Start [%04d]"), time.End());

	int nKSize = 21;
	cv::Mat element = cv::getStructuringElement(MORPH_RECT, cv::Size(nKSize, nKSize), cv::Point(-1, -1));
	_DebugLog(_T("Morph getStructuringElement"));

	for (int i = 0; i < STREAM_COUNT; i++) {
		if (m_gmatLoad[i].channels() == 3) {
			cuda::GpuMat src4ch;
			cuda::cvtColor(m_gmatLoad[i], src4ch, COLOR_BGR2BGRA);
			m_gmatLoad[i] = src4ch;
		}
	}
	_DebugLog(_T("Morph cvtColor"));

	Ptr<cuda::Filter>filterDilate = cuda::createMorphologyFilter(MORPH_DILATE, m_gmatLoad[nStream].type(), element);
	_DebugLog(_T("Morph Dilate"));

	Ptr<cuda::Filter>filterErode = cuda::createMorphologyFilter(MORPH_ERODE, m_gmatLoad[nStream].type(), element);
	_DebugLog(_T("Morph Erode"));


	if (nStream == 0)
	{
		for (int i = 0; i < 3; i++) {
			filterDilate->apply(m_gmatLoad[nStream], m_gmatLoad[nStream], stream0);

		}
		for (int i = 0; i < 3; i++) {
			filterErode->apply(m_gmatLoad[nStream], m_gmatLoad[nStream], stream0);
		}
		stream0.waitForCompletion();
		_DebugLog(_T("Morph apply"));
	}
	else
	{
		for (int i = 0; i < 3; i++) {
			filterDilate->apply(m_gmatLoad[nStream], m_gmatLoad[nStream], stream1);

		}
		for (int i = 0; i < 3; i++) {
			filterErode->apply(m_gmatLoad[nStream], m_gmatLoad[nStream], stream1);
		}
		stream1.waitForCompletion();
		_DebugLog(_T("Morph apply"));
	}


	cv::Mat matDisplay(m_gmatLoad[nStream]);
	_DebugLog(_T("Morph End [%04d]"), time.End());

	theDlg->m_ImageView1.SetMat(matDisplay);

#endif
}


void CDlgFunCuda::RunMorph3(int nID)
{
	//Input
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}

	_debugLog(LOG_MAIN, _T("Morph Load"));
	cv::Mat m_matLoad[2];
	for (int i = 0; i < STREAM_COUNT; i++) {
		m_matLoad[i] = matSrc.clone();
	}
	_debugLog(LOG_MAIN, _T("Morph Upload"));

	CQueryPerformanceTime time;
	_debugLog(LOG_MAIN, _T("Morph Start [%04d]"), time.End());

	int nKSize = 21;
	cv::Mat kernel(nKSize, nKSize, CV_8UC1, Scalar(255));
	for (int i = 0; i < 3; i++) {
		cv::dilate(m_matLoad[nID], m_matLoad[nID], kernel, cv::Point(-1, -1), 1);
	}
	for (int i = 0; i < 3; i++) {
		cv::erode(m_matLoad[nID], m_matLoad[nID], kernel, cv::Point(-1, -1), 1);
	}
	_debugLog(LOG_MAIN, _T("Morph apply"));
	_debugLog(LOG_MAIN, _T("Morph End [%04d]"), time.End());

	//Output
	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(m_matLoad[nID]);
}
