
#include "pch.h"
#include "opencvstudio.h"
#include "OpencvstudioDlg.h"
#include "afxdialogex.h"
#include "DlgFunMatch.h"


IMPLEMENT_DYNAMIC(CDlgFunMatch, CDialogEx)

CDlgFunMatch::CDlgFunMatch(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FUN_MATCH, pParent)
{
	m_nTestType = 5;
}

CDlgFunMatch::~CDlgFunMatch()
{
}

void CDlgFunMatch::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID_RESULT, m_GridResult);
}


BEGIN_MESSAGE_MAP(CDlgFunMatch, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_LOAD, &CDlgFunMatch::OnBnClickedMfcbuttonLoad)
	ON_BN_CLICKED(IDC_MFCBUTTON_APPLY, &CDlgFunMatch::OnBnClickedMfcbuttonApply)
END_MESSAGE_MAP()


BOOL CDlgFunMatch::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitGrid(1);
	m_hhImage.Init(GetDlgItem(IDC_STATIC_LAYOUT_IMG), 1, 0);

	CString str;
	for (int i = 0; i < DEF_MAX_VIEW; i++) {
		str.Format(_T("%02d"), i);
		((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->AddString(str);
		((CComboBox*)GetDlgItem(IDC_COMBO_DST))->AddString(str);
	}
	((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->SetCurSel(0);
	((CComboBox*)GetDlgItem(IDC_COMBO_DST))->SetCurSel(1);

	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(0, _T("TM_SQDIFF"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(1, _T("TM_SQDIFF_NORMED"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(2, _T("TM_CCORR"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(3, _T("TM_CCORR_NORMED"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(4, _T("TM_CCOEFF"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(5, _T("TM_CCOEFF_NORMED"));

	return TRUE;
}

void CDlgFunMatch::InitGrid(int nRowCount)
{
	CGridCtrl* grid = &m_GridResult;
	grid->GetDefaultCell(FALSE, FALSE)->SetBackClr(RGB(0xFF, 0xFF, 0xE0));
	grid->SetAutoSizeStyle();
	grid->SetHeaderSort(TRUE);			//혜더컬럼정렬
	grid->SetTextBkColor(RGB(255,255,255));
	grid->SetVirtualMode(FALSE);
	grid->SetEditable(TRUE);			//컬럼수정 가능/불가능
	grid->EnableDragAndDrop(FALSE);		//마우스끌기
	grid->SetRowResize(FALSE);			//세로컬럼사이즈저절
	grid->EnableSelection(TRUE);		//라인별선택
	grid->SetColumnResize(FALSE);		//가로컬럼사이즈조절
	grid->SetListMode(TRUE);			//라인별선택
	grid->SetSingleRowSelection(FALSE);	//한개라인씩 선택
	grid->SetRowCount(nRowCount + 1);
	grid->SetColumnCount(7);
	grid->SetFixedRowCount(1);
	grid->SetFixedColumnCount(0);
	grid->SetSingleColSelection(TRUE);
	grid->SetFixedColumnSelection(TRUE);
	grid->SetFixedRowSelection(TRUE);
	//grid->SetFrameFocusCell(FALSE);
	//grid->SetTrackFocusCell(FALSE);
	grid->SetGridLines(GVL_BOTH);
	grid->SetGridLineColor(RGB(200,200,200));
	grid->SetCompareFunction(CGridCtrl::pfnCellNumericCompare);

	for (int row = 0; row < grid->GetRowCount(); row++) {
		for (int col = 0; col < grid->GetColumnCount(); col++) {
			if (row == 0) {
				//grid->SetItemFormat(row, col, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				grid->SetItemState(row, col, grid->GetItemState(row, col) | GVIS_READONLY);
				//grid->SetItemBkColour(row, col, RGB_BLACK);
				//grid->SetItemFgColour(row, col, RGB_WHITE);
				//grid->SetItemFont(row, col, &m_lfFontM);
				//grid->SetRowHeight(row, 25);
			}
			else {
				grid->SetItemState(row, col, grid->GetItemState(row, col) | GVIS_READONLY);
				//grid->SetItemBkColour(row, col, RGB_WHITE);
				//grid->SetItemFont(row, col, &m_lfFontM);
			}
		}
	}

	grid->SetItemText(0, 0, _T("No"));
	grid->SetItemText(0, 1, _T("minV"));
	grid->SetItemText(0, 2, _T("maxV"));
	grid->SetItemText(0, 3, _T("minLocX"));
	grid->SetItemText(0, 4, _T("minLocY"));
	grid->SetItemText(0, 5, _T("maxLocX"));
	grid->SetItemText(0, 6, _T("maxLocY"));

	grid->SetColumnWidth(1, 100);
	grid->SetColumnWidth(2, 100);
	grid->SetColumnWidth(3, 100);
	grid->SetColumnWidth(4, 100);
	grid->SetColumnWidth(5, 100);
	grid->SetColumnWidth(6, 100);

	grid->ExpandColumnsToFit();
}


void CDlgFunMatch::OnBnClickedMfcbuttonLoad()
{
	DWORD dwFlag = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_ALLOWMULTISELECT; // 속성
	CString sFilter;
	CString sPath;
	sFilter.Format(_T("%s%s|"), _T("BMP"), _T("bmp"));
	CFileDialog dlg(TRUE, NULL, NULL, dwFlag, sFilter, this);
	if (dlg.DoModal() == IDOK) {
		for (POSITION pos = dlg.GetStartPosition(); pos != NULL;) {
			sPath = dlg.GetNextPathName(pos);
		}
	}
	else {
		return;
	}

	//m_matLoad = imread((cv::String)(CStringA)m_sReloadPath, CV_LOAD_IMAGE_GRAYSCALE);
	m_matMark = imread((cv::String)(CStringA)sPath);

	cv::Mat matGray;
	int nChannel = m_matMark.channels();
	if (nChannel != 1) {
		cv::cvtColor(m_matMark, matGray, CV_BGR2GRAY);
	}

	m_hhImage.SetImage(m_matMark);
}


void CDlgFunMatch::OnBnClickedMfcbuttonApply()
{
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}
	if (m_matMark.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}


	//matSrc = matSrc + Scalar(50, 50, 50);
	//cv::Mat matNoise(matSrc.size(), CV_32SC3);
	//cv::randn(matNoise, 0, 10);
	//cv::add(matSrc, matNoise, matSrc, cv::Mat(), CV_8UC3);

	CQueryPerformanceTime ptime;
	ptime.Start();
	_debugLog(LOG_MAIN, _T("Match Start"));

	cv::Mat result;
	DOUBLE minVal, maxVal;
	cv::Point minLoc, maxLoc, matchLoc;
	//int match_method = TM_CCOEFF_NORMED;
	int match_method = ((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->GetCurSel();

	switch (m_nTestType)
	{
	case 0: //Resize
	{
		cv::Mat matScaleTemp;
		cv::Mat matScaleSrc;
		DOUBLE dbScale = 0.25;
		cv::resize(matSrc, matScaleSrc, cv::Size(), dbScale, dbScale, cv::INTER_LINEAR);
		cv::resize(m_matMark, matScaleTemp, cv::Size(), dbScale, dbScale, cv::INTER_LINEAR);

		//Mat img_display;
		//matSrc.copyTo(img_display);
		//int result_cols = matSrc.cols - m_matTemplate.cols + 1;
		//int result_rows = matSrc.rows - m_matTemplate.rows + 1;
		//result.create(result_rows, result_cols, CV_32FC1);
		matchTemplate(matScaleSrc, matScaleTemp, result, match_method);
		//cv::normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat()); //0,1로 정규화
		cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

		_debugLog(LOG_MAIN, _T("Match End Resize (%d msec)"), ptime.End());

		if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED) {
			matchLoc = minLoc;
		}
		else {
			matchLoc = maxLoc;
		}
		rectangle(matScaleSrc, matchLoc,
			cv::Point(matchLoc.x + matScaleTemp.cols, matchLoc.y + matScaleTemp.rows),
			cv::Scalar(255, 255, 0), 1, 8, 0);

		//Output
		//theView->m_DlgMatView[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetMat(matScaleSrc);
		theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matScaleSrc);

		InitGrid(1);
		m_GridResult.SetItemText(1, 0, _T("0"));
		m_GridResult.SetItemText(1, 1, _db2str(minVal));	//검출된위치의 최소지점
		m_GridResult.SetItemText(1, 2, _db2str(maxVal));	//검출된위치의 최대 지점
		m_GridResult.SetItemText(1, 3, _db2str(minLoc.x));	//검출된위치의 최소포인터
		m_GridResult.SetItemText(1, 4, _db2str(minLoc.y));
		m_GridResult.SetItemText(1, 5, _db2str(maxLoc.x));	//검출된위치의 최대포인터
		m_GridResult.SetItemText(1, 6, _db2str(maxLoc.y));
		m_GridResult.Refresh();

		break;
	}
	case 1: //Rotate
	{
		cv::Mat matMatchSrc;
		DOUBLE dbSelMaxVal = -100;
		DOUBLE dbSelAngle;

		for (DOUBLE a = -3; a <= 3; a = a + 0.1)
		{
			cv::Mat matR = cv::getRotationMatrix2D(cv::Point2f(matSrc.cols / 2, matSrc.rows / 2), a, 1);
			cv::warpAffine(matSrc, matMatchSrc, matR, matSrc.size(), CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS);
			cv::matchTemplate(matMatchSrc, m_matMark, result, match_method);
			cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());
			if (dbSelMaxVal < maxVal) {
				dbSelMaxVal = maxVal;
				dbSelAngle = a;
			}
			_debugLog(LOG_MAIN, _T("Angle=%f, MaxVal=%f"), a, maxVal);
		}

		_debugLog(LOG_MAIN, _T("Match End Score=%f, Angle=%f"), dbSelMaxVal, dbSelAngle);

		if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED) {
			matchLoc = minLoc;
		}
		else {
			matchLoc = maxLoc;
		}

		rectangle(matSrc, matchLoc,
			cv::Point(matchLoc.x + m_matMark.cols, matchLoc.y + m_matMark.rows),
			cv::Scalar(255, 255, 0), 1, 8, 0);
		
		//Output
		//theView->m_DlgMatView[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetMat(matSrc);
		theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matSrc);

		InitGrid(1);
		m_GridResult.SetItemText(1, 0, _T("0"));
		m_GridResult.SetItemText(1, 1, _db2str(minVal));	//검출된위치의 최소지점
		m_GridResult.SetItemText(1, 2, _db2str(maxVal));	//검출된위치의 최대 지점
		m_GridResult.SetItemText(1, 3, _db2str(minLoc.x));	//검출된위치의 최소포인터
		m_GridResult.SetItemText(1, 4, _db2str(minLoc.y));
		m_GridResult.SetItemText(1, 5, _db2str(maxLoc.x));	//검출된위치의 최대포인터
		m_GridResult.SetItemText(1, 6, _db2str(maxLoc.y));
		m_GridResult.Refresh();

		break;
	}
	case 3: //Resize + Rotate
	{
		break;
	}
	case 4:
	{
		//cv::Mat matScaleTemp;
		//cv::Mat matScaleSrc;
		//DOUBLE dbScale = 0.25;
		//cv::resize(m_matSrc, matScaleSrc, cv::Size(), dbScale, dbScale, cv::INTER_LINEAR);
		//cv::resize(m_matMark, matScaleTemp, cv::Size(), dbScale, dbScale, cv::INTER_LINEAR);
		matchTemplate(matSrc, m_matMark, result, match_method);
		_debugLog(LOG_MAIN, _T("Match End (%d msec)"), ptime.End());

		vFind.clear();
		stFind_t find;
		float th = 0.80f;

		for (int y = 0; y < result.rows; y++) {
			for (int x = 0; x < result.cols; x++) {
				if (result.at<float>(y, x) > th) {
					find.pt = cv::Point(x, y);
					find.socore = result.at<float>(y, x);
					vFind.push_back(find);
					_debugLog(LOG_MAIN, _T("Score=%f x=%d y=%d"), result.at<float>(y, x), x, y);
				}
			}
		}

		InitGrid(vFind.size());

		int nLineIdx = 0;
		for (auto it = vFind.begin(); it != vFind.end(); ++it) {
			//rectangle(m_matSrc, *it, cv::Point(it->pt.x + m_matMark.cols, it->pt.y + m_matMark.rows), cv::Scalar(255, 255, 0), 1, 8, 0);
			m_GridResult.SetItemText(nLineIdx + 1, 0, _int2str(nLineIdx));
			m_GridResult.SetItemText(nLineIdx + 1, 1, _int2str(it->pt.x));
			m_GridResult.SetItemText(nLineIdx + 1, 2, _int2str(it->pt.y));
			m_GridResult.SetItemText(nLineIdx + 1, 3, _db2str(it->socore));
			nLineIdx++;
		}

		break;
	}
	case 5:
	{
		if (matSrc.empty()) {
			AfxMessageBox(_T("Error"));
		}

		/*
		0: TM_SQDIFF
		1: TM_SQDIFF NORMED
		2: TM CCORR
		3: TM CCORR NORMED (일반적으로 가장 많이 사용됨)
		4: TM COEFF
		5: TM COEFF NORMED";
		*/

		/*
		속도향상을 위한 팁
			1. resize
			2. gray image가 3~6배 속도가 빠름
		*/

		matchTemplate(matSrc, m_matMark, result, match_method);
		cv::normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat()); //0,1로 정규화
		cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());

		if (match_method == TM_SQDIFF || match_method == TM_SQDIFF_NORMED) {
			matchLoc = minLoc;
		}
		else {
			matchLoc = maxLoc;
		}


		cv::Mat matDisplay = m_matSrc.clone();
		rectangle(matDisplay,
			matchLoc,
			cv::Point(matchLoc.x + m_matMark.cols, matchLoc.y + m_matMark.rows),
			cv::Scalar(0, 0, 255), 3, 8, 0);

		cv::cvtColor(result, result, COLOR_GRAY2BGR);
		cv::circle(result, matchLoc, 3, Scalar(0, 0, 255), 1);
		cv::imshow("result", result);

		//Output
		//theView->m_DlgMatView[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetMat(matDisplay);
		theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matSrc);

		break;
	}
	default:
		break;
	}

	
}
