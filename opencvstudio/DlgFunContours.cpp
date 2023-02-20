
#include "pch.h"
#include "opencvstudio.h"
#include "OpencvstudioDlg.h"
#include "afxdialogex.h"
#include "DlgFunContours.h"

IMPLEMENT_DYNAMIC(CDlgFunContours, CDialogEx)

CDlgFunContours::CDlgFunContours(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FUN_CONTOURS, pParent)
{

}

CDlgFunContours::~CDlgFunContours()
{
}

void CDlgFunContours::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID_RESULT, m_GridContour);
}


BEGIN_MESSAGE_MAP(CDlgFunContours, CDialogEx)
	ON_BN_CLICKED(IDC_MFCBUTTON_APPLY, &CDlgFunContours::OnBnClickedMfcbuttonApply)
	ON_NOTIFY(NM_CLICK, IDC_GRID_RESULT, OnGridClickContour)
END_MESSAGE_MAP()


BOOL CDlgFunContours::OnInitDialog()
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

	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->InsertString(0, _T("CV_RETR_EXTERNAL"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->InsertString(1, _T("CV_RETR_LIST"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->InsertString(2, _T("CV_RETR_CCOMP"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->InsertString(3, _T("CV_RETR_TREE"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->InsertString(4, _T("CV_RETR_FLOODFILL"));
	((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->SetCurSel(2);

	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(0, _T("CV_CHAIN_CODE"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(1, _T("CV_CHAIN_APPROX_NONE"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(2, _T("CV_CHAIN_APPROX_SIMPLE"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(3, _T("CV_CHAIN_APPROX_TC89_L1"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(4, _T("CV_CHAIN_APPROX_TC89_KCOS"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->InsertString(5, _T("CV_LINK_RUNS"));
	((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->SetCurSel(2);

	((CComboBox*)GetDlgItem(IDC_COMBO_DRAWLINE_THICKNESS))->SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgFunContours::InitGridContours(int nRowCount)
{
	/*Grid*/
	CGridCtrl* grid = &m_GridContour;
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
	grid->SetRowCount(nRowCount + 1/*Header*/);
	grid->SetColumnCount(10);
	grid->SetFixedRowCount(1);
	grid->SetFixedColumnCount(0);
	grid->SetSingleColSelection(TRUE);
	grid->SetFixedColumnSelection(TRUE);
	grid->SetFixedRowSelection(TRUE);
	//grid->SetFrameFocusCell(FALSE);
	//grid->SetTrackFocusCell(FALSE);
	grid->SetGridLines(GVL_BOTH);
	grid->SetGridLineColor(RGB(200, 200, 200));
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
	grid->SetItemText(0, 1, _T("X"));
	grid->SetItemText(0, 2, _T("Y"));
	grid->SetItemText(0, 3, _T("W"));
	grid->SetItemText(0, 4, _T("H"));
	grid->SetItemText(0, 5, _T("Area"));
	grid->SetItemText(0, 6, _T("Point"));

	grid->SetColumnWidth(0, 50);
	grid->SetColumnWidth(1, 80);
	grid->SetColumnWidth(2, 80);
	grid->SetColumnWidth(3, 80);
	grid->SetColumnWidth(4, 80);
	grid->SetColumnWidth(5, 80);
	grid->SetColumnWidth(6, 80);
	//grid->ExpandColumnsToFit();
}


void CDlgFunContours::OnBnClickedMfcbuttonApply()
{
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}

	if (matSrc.type() != CV_8UC1) {
		cv::cvtColor(matSrc, matSrc, CV_BGR2GRAY);
	}

	cv::Mat matDst = cv::Mat(size(matSrc), CV_8U);
	cv::cvtColor(matDst, matDst, CV_GRAY2BGR);

	//contour retrieval modes
	int nMode;
	switch (((CComboBox*)GetDlgItem(IDC_COMBO_TYPE))->GetCurSel())
	{
	case 0: nMode = CV_RETR_EXTERNAL; break;
	case 1: nMode = CV_RETR_LIST; break;
	case 2: nMode = CV_RETR_CCOMP; break;
	case 3: nMode = CV_RETR_TREE; break;
	case 4: nMode = CV_RETR_FLOODFILL; break;
	default: break;
	}

	//contour approximation methods
	int nMethod;
	switch (((CComboBox*)GetDlgItem(IDC_COMBO_METHOD))->GetCurSel())
	{
	case 0: nMethod = CV_CHAIN_CODE; break;
	case 1: nMethod = CV_CHAIN_APPROX_NONE; break;
	case 2: nMethod = CV_CHAIN_APPROX_SIMPLE; break;
	case 3: nMethod = CV_CHAIN_APPROX_TC89_L1; break;
	case 4: nMethod = CV_CHAIN_APPROX_TC89_KCOS; break;
	case 5: nMethod = CV_LINK_RUNS; break;
	default: break;
	}



	try 
	{
		//find Contours
		CString sTxt;
		vector<vector<cv::Point>> vContours;
		vector<Vec4i> vHierarchy;
		_debugLog(LOG_MAIN, _T("findContours begin"));
		cv::findContours(matSrc, vContours, vHierarchy, nMode, nMethod);
		_debugLog(LOG_MAIN, _T("findContours end"));

		int nFineCnt = vContours.size();
		if (nFineCnt != 0) {
			InitGridContours(nFineCnt);
		}
		_debugLog(LOG_MAIN, _T("findContours Cnt : %d"), nFineCnt);

		//bounding rect
		GV_ITEM Item;
		cv::Rect rect;
		DOUBLE dbArea;
		for (int nContourIdx = 0; nContourIdx < vContours.size(); nContourIdx++) {
			rect = cv::boundingRect(vContours[nContourIdx]);
			Item.mask = GVIF_TEXT;
			Item.row = nContourIdx + 1;
			Item.col = 0;	Item.strText.Format(_T("%d"), nContourIdx + 1);		m_GridContour.SetItem(&Item);
			Item.col = 1;	Item.strText.Format(_T("%d"), rect.x);				m_GridContour.SetItem(&Item);
			Item.col = 2;	Item.strText.Format(_T("%d"), rect.y);				m_GridContour.SetItem(&Item);
			Item.col = 3;	Item.strText.Format(_T("%d"), rect.width);			m_GridContour.SetItem(&Item);
			Item.col = 4;	Item.strText.Format(_T("%d"), rect.height);			m_GridContour.SetItem(&Item);
			Item.col = 5;
			//dbArea = contourArea(Mat(vContours[nContourIdx]));
			dbArea = rect.width * rect.height;
			Item.strText.Format(_T("%f"), dbArea);
			m_GridContour.SetItem(&Item);

			Item.col = 6;
			Item.strText.Format(_T("%d"), vContours[nContourIdx].size());
			m_GridContour.SetItem(&Item);
		}
		m_vContours = vContours;

		m_GridContour.Refresh();

		//drawContours
		_debugLog(LOG_MAIN, _T("drawContours S"));
		for (int nContourIdx = 0; nContourIdx < vContours.size(); nContourIdx++) {
			Scalar color(255, 255, 0);
			cv::drawContours(matDst, vContours, nContourIdx, color, 1, 8);
		}
		_debugLog(LOG_MAIN, _T("drawContours E"));
	}
	catch (const std::exception&)
	{
		AfxMessageBox(_T("Thrown an exception"), MB_ICONSTOP);
		return;
	}

	//Output
	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matDst);
	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].ShowWindow(SW_SHOW);
}


void CDlgFunContours::OnGridClickContour(NMHDR* pNotifyStruct, LRESULT* /*pResult*/)
{
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}
	if (matSrc.type() != CV_8UC1) {
		cv::cvtColor(matSrc, matSrc, CV_BGR2GRAY);
	}

	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNotifyStruct;
	if (pItem->iRow <= 0) {
		return;
	}

	int nX, nY, nWidth, nHeight;
	CString str;
	CGridCtrl* pGrid = &m_GridContour;
	str = pGrid->GetItemText(pItem->iRow, 1);		nX = _ttoi(str);
	str = pGrid->GetItemText(pItem->iRow, 2);		nY = _ttoi(str);
	str = pGrid->GetItemText(pItem->iRow, 3);		nWidth = _ttoi(str);
	str = pGrid->GetItemText(pItem->iRow, 4);		nHeight = _ttoi(str);

	_debugLog(LOG_MAIN, _T("Contour Pos X:%d Y:%d W:%d H:%d"), nX, nY, nWidth, nHeight);

	int nMargin = 0;
	cv::Rect rtROI;
	rtROI.x = nX;
	rtROI.y = nY;
	rtROI.width = nWidth;
	rtROI.height = nHeight;

	rtROI.x -= nMargin;
	rtROI.y -= nMargin;
	rtROI.width = rtROI.width + (nMargin * 2);
	rtROI.height = rtROI.height + (nMargin * 2);

	//cv::Mat matColor;
	//if (m_matLoad.channels() != 3) {
	//	cvtColor(m_matLoad, matColor, CV_GRAY2BGR);
	//}
	//else {
	//	matColor = m_matLoad.clone();
	//}

	Scalar color(0, 255, 0);
	int nThickness = ((CComboBox*)GetDlgItem(IDC_COMBO_DRAWLINE_THICKNESS))->GetCurSel();

	cv::Mat matDst = matSrc.clone();
	cv::cvtColor(matDst, matDst, CV_GRAY2BGR);
	rectangle(matDst, rtROI, color, nThickness + 1);

	//Scalar colorLine(64, 64, 64);
	//cv::line(matDisplay, cv::Point(0, nY), cv::Point(matDisplay.cols, nY), colorLine, 1);
	//cv::line(matDisplay, cv::Point(nX, 0), cv::Point(nX, matDisplay.rows), colorLine, 1);

	/*Align*/
	//int nIdx;
	//str = pGrid->GetItemText(pItem->iRow, 0);
	//nIdx = _ttoi(str);
	//nIdx = nIdx - 1;

	//int nPointSize = m_vContours[nIdx].size();
	//for (int i = 0; i < nPointSize; i++)
	//{
	//	m_vContours[nIdx][i].x;
	//	cv::circle(matColor, m_vContours[nIdx][i], 22, color, 5);
	//}

	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(matDst);
	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].ShowWindow(SW_SHOW);
}
