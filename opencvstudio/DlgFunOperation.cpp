
#include "pch.h"
#include "opencvstudio.h"
#include "OpencvstudioDlg.h"
#include "afxdialogex.h"
#include "DlgFunOperation.h"

IMPLEMENT_DYNAMIC(CDlgFunOperation, CDialogEx)

CDlgFunOperation::CDlgFunOperation(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FUN_OPERATION, pParent)
{

}

CDlgFunOperation::~CDlgFunOperation()
{
}

void CDlgFunOperation::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgFunOperation, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_APPLY, &CDlgFunOperation::OnBnClickedMfcbuttonApply)
	ON_CBN_SELCHANGE(IDC_COMBO_METHOD, &CDlgFunOperation::OnCbnSelchangeComboMethod)
	ON_CBN_SELCHANGE(IDC_COMBO_METHOD2, &CDlgFunOperation::OnCbnSelchangeComboMethod2)
END_MESSAGE_MAP()


BOOL CDlgFunOperation::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString str;
	for (int i = 0; i < DEF_MAX_VIEW; i++) {
		str.Format(_T("%02d"), i);
		((CComboBox*)GetDlgItem(IDC_COMBO_SRC1))->AddString(str);
		((CComboBox*)GetDlgItem(IDC_COMBO_SRC2))->AddString(str);
		((CComboBox*)GetDlgItem(IDC_COMBO_DST))->AddString(str);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_SRC1))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_SRC2))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_DST))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(0, _T("Invert"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(1, _T("Add"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(2, _T("Subtract"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(3, _T("Multiply"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(4, _T("Divide"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(5, _T("Compare"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(6, _T("AddWeighted"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(7, _T("AdobeAddition"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(8, _T("AdobeSubtract"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(9, _T("AdobeMultiply"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(10, _T("AdobeDifference"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(11, _T("AdobeDivide"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(12, _T("Modulo"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(13, _T("MeanStdDev"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(14, _T("CountNonZero"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(15, _T("Integral"));

	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD2))->ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
}


BOOL CDlgFunOperation::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


CString CDlgFunOperation::ToString(eOperatorMethode val)
{
	CString str;

	switch (val)
	{
	case CDlgFunOperation::eOperatorMethode::Invert:			str = _T("Invert"); break;
	case CDlgFunOperation::eOperatorMethode::Add:				str = _T("Add"); break;
	case CDlgFunOperation::eOperatorMethode::Subtract:			str = _T("Subtract"); break;
	case CDlgFunOperation::eOperatorMethode::Multiply:			str = _T("Multiply"); break;
	case CDlgFunOperation::eOperatorMethode::Divide:			str = _T("Divide"); break;
	case CDlgFunOperation::eOperatorMethode::Compare:			str = _T("Compare"); break;
	case CDlgFunOperation::eOperatorMethode::AddWeighted:		str = _T("AddWeighted"); break;
	case CDlgFunOperation::eOperatorMethode::AdobeAddition:		str = _T("AdobeAddition"); break;
	case CDlgFunOperation::eOperatorMethode::AdobeSubtract:		str = _T("AdobeSubtract"); break;
	case CDlgFunOperation::eOperatorMethode::AdobeMultiply:		str = _T("AdobeMultiply"); break;
	case CDlgFunOperation::eOperatorMethode::AdobeDifference:	str = _T("AdobeDifference"); break;
	case CDlgFunOperation::eOperatorMethode::AdobeDivide:		str = _T("AdobeDivide"); break;
	case CDlgFunOperation::eOperatorMethode::MeanStdDev:		str = _T("MeanStdDev"); break;
	case CDlgFunOperation::eOperatorMethode::CountNonZero:		str = _T("CountNonZero"); break;
	case CDlgFunOperation::eOperatorMethode::Integral:			str = _T("Integral"); break;
	default:
		break;
	}

	return str;
}


BOOL CDlgFunOperation::Add(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst)
{
	cv::add(matSrc1, matSrc2, matDst);
	return TRUE;
}


BOOL CDlgFunOperation::Subtract(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst)
{
	cv::subtract(matSrc1, matSrc2, matDst);
	return TRUE;
}


BOOL CDlgFunOperation::Multiply(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst)
{
	cv::multiply(matSrc1, matSrc2, matDst);
	return TRUE;
}


BOOL CDlgFunOperation::Divide(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst)
{
	cv::divide(matSrc1, matSrc2, matDst);
	return TRUE;
}


BOOL CDlgFunOperation::Compare(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst, int nMethode)
{
	//cv::CmpTypes::CMP_EQ) : src1, src2 요소가 같음
	//cv::CmpTypes::CMP_GT) : src1, src2 요소가 큼
	//cv::CmpTypes::CMP_GE) : src1, src2 요소가 크거나 같음
	//cv::CmpTypes::CMP_LT) : src1, src2 요소가 작음g
	//cv::CmpTypes::CMP_LE) : src1, src2 요소가 작거나 같음
	//cv::CmpTypes::CMP_NE) : src1, src2 요소가 같지 않음
	cv::compare(matSrc1, matSrc2, matDst, nMethode);
	return TRUE;
}


BOOL CDlgFunOperation::AddWeighted(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst)
{
	//result = imgA * a + imgB * b + c
	cv::addWeighted(matSrc1, 1, matSrc2, 1, 0, matDst);
	return TRUE;
}


BOOL CDlgFunOperation::AdbAddition(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst)
{
	if (matDst.empty()) {
		matDst = cv::Mat::zeros(matSrc1.size(), matSrc1.type());
	}

	double a, b, r;
	double base, blend;
	int val;
	for (int y = 0; y < matSrc1.rows; y++) {
		for (int x = 0; x < matSrc1.cols; x++) {
			blend = matSrc1.at<uchar>(y, x);
			base = matSrc2.at<uchar>(y, x);
			b = blend;
			a = base;
			r = a + b;
			if (r > 255) {
				matDst.at<uchar>(y, x) = 255;
			}
			else {
				val = int(r);
				matDst.at<uchar>(y, x) = val;
			}
		}
	}

	return TRUE;
}


BOOL CDlgFunOperation::AdbSubtract(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst)
{
	double a, b, r;
	double base, blend;
	int val;

	for (int y = 0; y < matSrc1.rows; y++) {
		for (int x = 0; x < matSrc1.cols; x++) {
			blend = matSrc1.at<uchar>(y, x);
			base = matSrc2.at<uchar>(y, x);
			b = blend;
			a = base;
			r = a - b;

			if (blend == 255) {
				matDst.at<uchar>(y, x) = 0;
			}
			else if (r < 0) {
				matDst.at<uchar>(y, x) = 0;
			}
			else {
				val = int(r);
				matDst.at<uchar>(y, x) = val;
			}
		}
	}

	// 	for (int y = 0; y < matSrc1.rows; y++) {
	// 		for (int x = 0; x < matSrc1.cols; x++) {
	// 			blend = matSrc1.at<uchar>(y, x);
	// 			base = matSrc2.at<uchar>(y, x);
	// 			b = blend;
	// 			a = base;
	// 			r = a - b;
	// 			if ( r < 0 ) {
	// 				matDst.at<uchar>(y, x) = 0;
	// 			}
	// 			else if (blend == 0)
	// 			{
	// 				matDst.at<uchar>(y, x) = (int)base;
	// 			}
	// 			else if (blend == 255)
	// 			{
	// 				matDst.at<uchar>(y, x) = 0;
	// 			}
	// 			else {
	// 				val = int(r);
	// 				matDst.at<uchar>(y, x) = val;
	// 			}
	// 		}
	// 	}

	return TRUE;
}


BOOL CDlgFunOperation::AdbMultiply(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst)
{
	double a, b, r;
	double base, blend;
	int val;
	for (int y = 0; y < matSrc1.rows; y++) {
		for (int x = 0; x < matSrc1.cols; x++) {
			blend = matSrc1.at<uchar>(y, x);
			base = matSrc2.at<uchar>(y, x);
			b = blend / 255;
			a = base / 255;
			r = a * b;
			if (blend == 0 || base == 0) {
				matDst.at<uchar>(y, x) = 0;
			}
			else {
				val = int(r * 255);
				matDst.at<uchar>(y, x) = val;
			}
		}
	}

	return TRUE;
}


BOOL CDlgFunOperation::AdbDifference(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst)
{
	double a, b, r;
	double base, blend;
	int val;
	for (int y = 0; y < matSrc1.rows; y++) {
		for (int x = 0; x < matSrc1.cols; x++) {
			blend = matSrc1.at<uchar>(y, x);
			base = matSrc2.at<uchar>(y, x);
			b = blend / 255;
			a = base / 255;
			r = fabs(a - b);

			val = int(r * 255);
			matDst.at<uchar>(y, x) = val;
		}
	}

	return TRUE;
}


BOOL CDlgFunOperation::AdbDivide(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst)
{
	double base, blend;
	for (int y = 0; y < matSrc1.rows; y++) {
		for (int x = 0; x < matSrc1.cols; x++) {
			blend = matSrc1.at<uchar>(y, x);
			base = matSrc2.at<uchar>(y, x);
			if (blend == 0 && base == 0) {
				matDst.at<uchar>(y, x) = 0;
			}
			else if (blend == 0) {
				matDst.at<uchar>(y, x) = 255;
			}
			else if (base >= blend) {
				matDst.at<uchar>(y, x) = 255;
			}
			else {
				double a, b, r;
				a = base / 255;
				b = blend / 255;
				r = a / b;
				int val = int(r * 255);
				matDst.at<uchar>(y, x) = val;
			}
		}
	}

	// 	for (int y = 0; y < matSrc1.rows; y++) {
	// 		for (int x = 0; x < matSrc1.cols; x++) {
	// 			blend = matSrc1.at<uchar>(y, x);
	// 			base = matSrc2.at<uchar>(y, x);
	// 			b = blend / 255;
	// 			a = base / 255;
	// 			r = a / b;
	// 			//if (r > 1) {
	// 			//	matDst.at<uchar>(y, x) = 255;	n[0]++;
	// 			//}
	// 			if (b == 1) {
	// 				matDst.at<uchar>(y, x) = base;
	// 			}
	// 			else if (a >= b) {
	// 				matDst.at<uchar>(y, x) = 255;
	// 			}
	// 			//else if (b == 0) {
	// 			else if (blend == 0) {
	// 				matDst.at<uchar>(y, x) = 255;
	// 			}
	// 			else if (blend == 255) {
	// 				matDst.at<uchar>(y, x) = 255;
	// 			}
	// 			//else if (a == 0 && b == 0) {
	// 			else if (blend == 0 && base == 0) {
	// 				matDst.at<uchar>(y, x) = 0;
	// 			}
	// 			else {
	// 				int val = int(r * 255);
	// 				matDst.at<uchar>(y, x) = val;
	// 			}
	// 		}
	// 	}
	//for (int y = 0; y < m_matSrc1.rows; y++) {
	//	for (int x = 0; x < m_matSrc1.cols; x++) {
	//		nBase = m_matSrc1.at<uchar>(y, x);
	//		nBlend = m_matSrc2.at<uchar>(y, x);
	//		if (nBase == 0 && nBlend == 0) {
	//			m_matDst.at<uchar>(y, x) = 0;
	//		}
	//		else if(nBlend == 0) {
	//			m_matDst.at<uchar>(y, x) = 255;
	//		}
	//		else if (nBase >= nBlend) {
	//			m_matDst.at<uchar>(y, x) = 255;
	//		}
	//		else {
	//			dbBase = nBase / 255;
	//			dbBlend = nBlend / 255;
	//			m_matDst.at<uchar>(y, x) =  (dbBase / dbBlend) * 255;
	//		}
	//	}
	//}
	return TRUE;
}


BOOL CDlgFunOperation::Modulo(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst)
{
	double base, blend;
	int val;
	for (int y = 0; y < matSrc1.rows; y++) {
		for (int x = 0; x < matSrc1.cols; x++) {
			blend = matSrc1.at<uchar>(y, x);
			base = matSrc2.at<uchar>(y, x);
			val = int(blend + base) / 256;
			//b = blend / 255;
			//a = base / 255;
			//r = fabs(a - b);
			//val = int(r * 255);
			matDst.at<uchar>(y, x) = val;
		}
	}

	return TRUE;
}


void CDlgFunOperation::OnBnClickedMfcbuttonApply()
{
	//Input
	cv::Mat matSrc1 = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC1))->GetCurSel()].GetImage();
	cv::Mat matSrc2 = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC2))->GetCurSel()].GetImage();
	if (matSrc1.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}

	int sel = ((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->GetCurSel();
	cv::Mat matDst;

	try 
	{
		_debugLog(LOG_MAIN, _T("operation begin"));
		switch ((eOperatorMethode)sel)
		{
		case eOperatorMethode::Invert:
		{
			matDst = ~matSrc1;
			break;
		}
		case eOperatorMethode::Add:
		{
			Add(matSrc1, matSrc2, matDst);
			break;
		}
		case eOperatorMethode::Subtract:
		{
			Subtract(matSrc1, matSrc2, matDst);
			break;
		}
		case eOperatorMethode::Multiply:
		{
			Multiply(matSrc1, matSrc2, matDst);
			break;
		}
		case eOperatorMethode::Divide:
		{
			Divide(matSrc1, matSrc2, matDst);
			break;
		}
		case eOperatorMethode::Compare:
		{
			int nMethode = ((CComboBox*)GetDlgItem(IDC_COMBO_METHOD2))->GetCurSel();
			Compare(matSrc1, matSrc2, matDst, nMethode);
			break;
		}
		case eOperatorMethode::AddWeighted:
		{
			AddWeighted(matSrc1, matSrc2, matDst);
			break;
		}
		case  eOperatorMethode::AdobeAddition:
		{
			if (matSrc1.channels() != 1)
				cv::cvtColor(matSrc1, matSrc1, CV_BGR2GRAY);
			if (matSrc2.channels() != 1)
				cv::cvtColor(matSrc2, matSrc2, CV_BGR2GRAY);
			matDst = cv::Mat(size(matSrc1), CV_8UC1);
			AdbAddition(matSrc1, matSrc2, matDst);
			break;
		}
		case  eOperatorMethode::AdobeSubtract:
		{
			if (matSrc1.channels() != 1)
				cv::cvtColor(matSrc1, matSrc1, CV_BGR2GRAY);
			if (matSrc2.channels() != 1)
				cv::cvtColor(matSrc2, matSrc2, CV_BGR2GRAY);
			matDst = cv::Mat(size(matSrc1), CV_8UC1);
			AdbSubtract(matSrc1, matSrc2, matDst);
			break;
		}
		case  eOperatorMethode::AdobeMultiply:
		{
			if (matSrc1.channels() != 1)
				cv::cvtColor(matSrc1, matSrc1, CV_BGR2GRAY);
			if (matSrc2.channels() != 1)
				cv::cvtColor(matSrc2, matSrc2, CV_BGR2GRAY);
			matDst = cv::Mat(size(matSrc1), CV_8UC1);
			AdbMultiply(matSrc1, matSrc2, matDst);
			break;
		}
		case  eOperatorMethode::AdobeDifference:
		{
			if (matSrc1.channels() != 1)
				cv::cvtColor(matSrc1, matSrc1, CV_BGR2GRAY);
			if (matSrc2.channels() != 1)
				cv::cvtColor(matSrc2, matSrc2, CV_BGR2GRAY);
			matDst = cv::Mat(size(matSrc1), CV_8UC1);
			AdbDifference(matSrc1, matSrc2, matDst);
			break;
		}
		case  eOperatorMethode::AdobeDivide:
		{
			if (matSrc1.channels() != 1)
				cv::cvtColor(matSrc1, matSrc1, CV_BGR2GRAY);
			if (matSrc2.channels() != 1)
				cv::cvtColor(matSrc2, matSrc2, CV_BGR2GRAY);
			matDst = cv::Mat(size(matSrc1), CV_8UC1);
			AdbDivide(matSrc1, matSrc2, matDst);
			break;
		}
		case eOperatorMethode::Modulo:
		{
			if (matSrc1.channels() != 1)
				cv::cvtColor(matSrc1, matSrc1, CV_BGR2GRAY);
			if (matSrc2.channels() != 1)
				cv::cvtColor(matSrc2, matSrc2, CV_BGR2GRAY);
			matDst = cv::Mat(size(matSrc1), CV_8UC1);
			Modulo(matSrc1, matSrc2, matDst);
			break;
		}
		case eOperatorMethode::MeanStdDev:
		{
			cv::Scalar mean, stddev;
			cv::meanStdDev(matSrc1, mean, stddev);
			_debugLog(LOG_MAIN, _T("operation end"));
			CString str;
			str.Format(_T("mean:%f, stddev:%f"), mean.val[0], stddev.val[0]);
			AfxMessageBox(str);
			return;
		}
		case eOperatorMethode::CountNonZero:
		{
			if (matSrc1.channels() != 1)
				cv::cvtColor(matSrc1, matSrc1, CV_BGR2GRAY);
			int count = cv::countNonZero(matSrc1);
			CString str;
			str.Format(_T("countNonZero: %d"), count);
			AfxMessageBox(str);
			return;
		}
		case eOperatorMethode::Integral:
		{
			integral(matSrc1, matDst, CV_32S);
			_debugLog(LOG_MAIN, _T("operation end"));
			cv::imshow("integral", matDst);
			return;
		}
		default:
			break;
		}
		_debugLog(LOG_MAIN, _T("operation end"));
	}
	catch (const std::exception&) {
		AfxMessageBox(_T("Thrown an exception"), MB_ICONSTOP);
		return;
	}

	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matDst);
}


void CDlgFunOperation::OnCbnSelchangeComboMethod()
{
	int sel = ((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->GetCurSel();

	switch ((CDlgFunOperation::eOperatorMethode)sel)
	{
	case CDlgFunOperation::eOperatorMethode::Invert:
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_DST))->ShowWindow(SW_SHOW);
		((CComboBox*)GetDlgItem(IDC_COMBO_METHOD2))->ShowWindow(SW_HIDE);
		break;
	}
	case CDlgFunOperation::eOperatorMethode::Add:
	case CDlgFunOperation::eOperatorMethode::Subtract:
	case CDlgFunOperation::eOperatorMethode::Multiply:
	case CDlgFunOperation::eOperatorMethode::Divide:
	case CDlgFunOperation::eOperatorMethode::AdobeAddition:
	case CDlgFunOperation::eOperatorMethode::AdobeSubtract:
	case CDlgFunOperation::eOperatorMethode::AdobeMultiply:
	case CDlgFunOperation::eOperatorMethode::AdobeDifference:
	case CDlgFunOperation::eOperatorMethode::AdobeDivide:
	case CDlgFunOperation::eOperatorMethode::AddWeighted:
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_DST))->ShowWindow(SW_SHOW);
		((CComboBox*)GetDlgItem(IDC_COMBO_METHOD2))->ResetContent();
		((CComboBox*)GetDlgItem(IDC_COMBO_METHOD2))->ShowWindow(SW_HIDE);
		break;
	}
	case CDlgFunOperation::eOperatorMethode::Compare:
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_DST))->ShowWindow(SW_SHOW);
		((CComboBox*)GetDlgItem(IDC_COMBO_METHOD2))->ShowWindow(SW_SHOW);
		((CComboBox*)GetDlgItem(IDC_COMBO_METHOD2))->ResetContent();
		((CComboBox*)GetDlgItem(IDC_COMBO_METHOD2))->AddString(_T("CMP_EQ"));
		((CComboBox*)GetDlgItem(IDC_COMBO_METHOD2))->AddString(_T("CMP_GT"));
		((CComboBox*)GetDlgItem(IDC_COMBO_METHOD2))->AddString(_T("CMP_GE"));
		((CComboBox*)GetDlgItem(IDC_COMBO_METHOD2))->AddString(_T("CMP_LT"));
		((CComboBox*)GetDlgItem(IDC_COMBO_METHOD2))->AddString(_T("CMP_LE"));
		((CComboBox*)GetDlgItem(IDC_COMBO_METHOD2))->AddString(_T("CMP_NE"));
		((CComboBox*)GetDlgItem(IDC_COMBO_METHOD2))->SetCurSel(0);
		break;
	}
	case eOperatorMethode::MeanStdDev:
	case eOperatorMethode::CountNonZero:
	case eOperatorMethode::Integral:
	{
		((CComboBox*)GetDlgItem(IDC_COMBO_SRC2))->ShowWindow(SW_HIDE);
		((CComboBox*)GetDlgItem(IDC_COMBO_DST))->ShowWindow(SW_HIDE);
		((CComboBox*)GetDlgItem(IDC_COMBO_METHOD2))->ShowWindow(SW_HIDE);
		break;
	}
	default:
		break;
	}
}


void CDlgFunOperation::OnCbnSelchangeComboMethod2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
