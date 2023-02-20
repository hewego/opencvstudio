
#include "pch.h"
#include "opencvstudio.h"
#include "OpencvstudioDlg.h"
#include "afxdialogex.h"
#include "DlgFunLabel.h"


IMPLEMENT_DYNAMIC(CDlgFunLabel, CDialogEx)

CDlgFunLabel::CDlgFunLabel(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DLG_FUN_LABEL, pParent)
{

}

CDlgFunLabel::~CDlgFunLabel()
{
}

void CDlgFunLabel::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRID_RESULT, m_GridLabels);
}


BEGIN_MESSAGE_MAP(CDlgFunLabel, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LABEL_RESET, &CDlgFunLabel::OnBnClickedButtonLabelReset)
	ON_BN_CLICKED(IDC_MFCBUTTON_APPLY, &CDlgFunLabel::OnBnClickedMfcbuttonApply)
	ON_NOTIFY(NM_CLICK, IDC_GRID_RESULT, &CDlgFunLabel::OnBnClickedBlobInfo)
END_MESSAGE_MAP()


BOOL CDlgFunLabel::OnInitDialog()
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

	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgFunLabel::InitGrid(int nRowCount)
{
	/*Grid*/
	CGridCtrl* grid = &m_GridLabels;
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
	grid->SetRowCount(nRowCount);
	grid->SetColumnCount(6);
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
	grid->SetItemText(0, 1, _T("area"));
	grid->SetItemText(0, 2, _T("left"));
	grid->SetItemText(0, 3, _T("top"));
	grid->SetItemText(0, 4, _T("width"));
	grid->SetItemText(0, 5, _T("height"));

	grid->SetColumnWidth(0, 50);
	grid->SetColumnWidth(1, 80);
	grid->SetColumnWidth(2, 80);
	grid->SetColumnWidth(3, 80);
	grid->SetColumnWidth(4, 80);
	grid->SetColumnWidth(5, 80);

	grid->ExpandColumnsToFit();
}


void CDlgFunLabel::OnBnClickedBlobInfo(NMHDR* pNotifyStruct, LRESULT* pResult)
{
	NM_GRIDVIEW* pItem = (NM_GRIDVIEW*)pNotifyStruct;
	CGridCtrl* grid = &m_GridLabels;

	int nSleection = pItem->iRow;
	m_matColor = Mat::zeros(m_matGray.size(), CV_8UC3);
	for (int y = 0; y < m_matColor.rows; y++) {
		for (int x = 0; x < m_matColor.cols; x++) {
			int label = m_MatLabel.at<int>(y, x);
			CV_Assert(0 <= label && label <= m_numOfLables);

			if (pItem->iRow - 1 == label)
				m_matColor.at<cv::Vec3b>(y, x) = m_colors[label];
		}
	}

	//Output
	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(m_matColor);
}


void CDlgFunLabel::OnBnClickedButtonLabelReset()
{

}


void CDlgFunLabel::OnBnClickedMfcbuttonApply()
{
	cv::Mat matSrc = theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_SRC))->GetCurSel()].GetImage();
	if (matSrc.rows <= 0) {
		AfxMessageBox(_T("No image selected"));
		return;
	}
	if (matSrc.type() != CV_8UC1) {
		cv::cvtColor(matSrc, matSrc, CV_BGR2GRAY);
	}

	m_matGray = matSrc.clone();

	//cv::threshold(matGray, matGray, 128, 255, cv::THRESH_BINARY);
	//bitwise_not(matGray, matGray);

	_debugLog(LOG_MAIN, _T("start"));
	cv::Mat matStats, matCentroids;
	m_numOfLables = cv::connectedComponentsWithStats(matSrc, m_MatLabel, matStats, matCentroids, 8, CV_32S);
	_debugLog(LOG_MAIN, _T("end Labels=%d"), m_numOfLables);

	if (m_numOfLables != 0) {
		InitGrid(m_numOfLables + 1);
	}


	m_colors.assign(m_numOfLables + 1, 0);
	m_colors[0] = Vec3b(0, 0, 0); // background pixels remain black.
	for (int i = 1; i < m_numOfLables; i++) {
		m_colors[i] = Vec3b(rand() % 256, rand() % 256, rand() % 256);
		//if (matStats.at<int>(i, cv::CC_STAT_AREA) < 200)
		//colors[i] = Vec3b(0, 0, 0); // 작은건 검정색으로 칠하겠음
	}

	m_matColor = Mat::zeros(matSrc.size(), CV_8UC3);
	for (int y = 0; y < m_matColor.rows; y++) {
		for (int x = 0; x < m_matColor.cols; x++) {
			int label = m_MatLabel.at<int>(y, x);
			CV_Assert(0 <= label && label <= m_numOfLables);

			m_matColor.at<cv::Vec3b>(y, x) = m_colors[label];
		}
	}


	//for (int y = 0; y < mLabel.rows; ++y) {
	//	int *label = mLabel.ptr<int>(y);
	//	Vec3b* pixel = matSrc.ptr<Vec3b>(y);
	//	for (int x = 0; x < mLabel.cols; ++x) {
	//		if (label[x] == 3) {
	//			pixel[x][2] = 0;
	//			pixel[x][1] = 255;
	//			pixel[x][0] = 0;
	//		}
	//	}
	//}


	int nLineIdx = 0;
	cv::Rect rt;
	for (int j = 0; j < m_numOfLables; j++)
	{
		//int left = matStats.at<int>(j, CC_STAT_LEFT);
		//int top = matStats.at<int>(j, CC_STAT_TOP);
		//int width = matStats.at<int>(j, CC_STAT_WIDTH);
		//int height = matStats.at<int>(j, CC_STAT_HEIGHT);
		int area = matStats.at<int>(j, CC_STAT_AREA);
		rt.x = matStats.at<int>(j, CC_STAT_LEFT);
		rt.y = matStats.at<int>(j, CC_STAT_TOP);
		rt.width = matStats.at<int>(j, CC_STAT_WIDTH);
		rt.height = matStats.at<int>(j, CC_STAT_HEIGHT);

		//cv::rectangle(matSrc, rt, Scalar(0, 0, 255), 1);
		//cv::rectangle(matSrc, cv::Point(left, top), cv::Point(left + width, top + height), Scalar(0, 0, 255), 1);
		//cv::putText(matSrc, to_string(j), cv::Point(left + 20, top + 20), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);

		m_GridLabels.SetItemText(nLineIdx + 1, 0, _int2str(nLineIdx));
		m_GridLabels.SetItemText(nLineIdx + 1, 1, _int2str(area));
		m_GridLabels.SetItemText(nLineIdx + 1, 2, _int2str(rt.x));
		m_GridLabels.SetItemText(nLineIdx + 1, 3, _int2str(rt.y));
		m_GridLabels.SetItemText(nLineIdx + 1, 4, _int2str(rt.width));
		m_GridLabels.SetItemText(nLineIdx + 1, 5, _int2str(rt.height));

		nLineIdx++;
	}
	m_GridLabels.Refresh();
	m_GridLabels.RedrawWindow();

	theDlg->m_DlgImg[((CComboBox*)GetDlgItem(IDC_COMBO_DST))->GetCurSel()].SetImage(m_matColor);
}