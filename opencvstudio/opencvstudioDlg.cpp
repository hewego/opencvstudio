
#include "pch.h"
#include "framework.h"
#include "opencvstudio.h"
#include "opencvstudioDlg.h"
#include "afxdialogex.h"
#include "DlgFunThreshold.h"
#include "DlgFunThresholdA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


COpencvstudioDlg::COpencvstudioDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPENCVSTUDIO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	theDlg = this;
}
void COpencvstudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LOG, m_ListboxLog);
}

BEGIN_MESSAGE_MAP(COpencvstudioDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_VIEW_IMAGE1, &COpencvstudioDlg::OnViewImage1)
	ON_COMMAND(ID_VIEW_IMAGE2, &COpencvstudioDlg::OnViewImage2)
	ON_COMMAND(ID_VIEW_IMAGE3, &COpencvstudioDlg::OnViewImage3)
	ON_COMMAND(ID_VIEW_IMAGE4, &COpencvstudioDlg::OnViewImage4)
	ON_COMMAND(ID_VIEW_IMAGE5, &COpencvstudioDlg::OnViewImage5)
	ON_COMMAND(ID_VIEW_IMAGE5, &COpencvstudioDlg::OnViewImage6)
	ON_BN_CLICKED(IDC_MFCBUTTON_FUN_TH, &COpencvstudioDlg::OnBnClickedMfcbuttonFunTh)
	ON_BN_CLICKED(IDC_MFCBUTTON_FUN_ATH, &COpencvstudioDlg::OnBnClickedMfcbuttonFunAth)
END_MESSAGE_MAP()


BOOL COpencvstudioDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	for (int i = 0; i < 6; i++)
	{
		//m_DlgImg[i].m_nNo = i;
		m_DlgImg[i].Create(IDD_DLG_IMAGE);
		m_DlgImg[i].ShowWindow(SW_HIDE);
	}

	return TRUE;
}

void COpencvstudioDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


void COpencvstudioDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}


HCURSOR COpencvstudioDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void COpencvstudioDlg::OnViewImage1()
{
	m_DlgImg[0].ShowWindow(SW_SHOW);
}


void COpencvstudioDlg::OnViewImage2()
{
	m_DlgImg[1].ShowWindow(SW_SHOW);
}


void COpencvstudioDlg::OnViewImage3()
{
	m_DlgImg[2].ShowWindow(SW_SHOW);
}


void COpencvstudioDlg::OnViewImage4()
{
	m_DlgImg[3].ShowWindow(SW_SHOW);
}


void COpencvstudioDlg::OnViewImage5()
{
	m_DlgImg[4].ShowWindow(SW_SHOW);
}


void COpencvstudioDlg::OnViewImage6()
{
	m_DlgImg[5].ShowWindow(SW_SHOW);
}


void COpencvstudioDlg::OnCancel()
{
	ResetDlg();
	CDialogEx::OnCancel();
}


void COpencvstudioDlg::SetLog(CString sLog)
{
	m_ListboxLog.InsertString(0, sLog);
}


void COpencvstudioDlg::ResetDlg()
{
	if (m_oblist_dlgTh.GetSize() != 0) {
		POSITION pos;
		CDlgFunThreshold* pDlg;
		for (pos = m_oblist_dlgTh.GetHeadPosition(); pos != NULL; ) {
			pDlg = (CDlgFunThreshold*)m_oblist_dlgTh.GetNext(pos);
			delete pDlg;
			pDlg = NULL;
		}
		m_oblist_dlgTh.RemoveAll();
	}


	if (m_oblist_dlgATh.GetSize() != 0) {
		POSITION pos;
		CDlgFunThresholdA* pDlg;
		for (pos = m_oblist_dlgTh.GetHeadPosition(); pos != NULL; ) {
			pDlg = (CDlgFunThresholdA*)m_oblist_dlgATh.GetNext(pos);
			delete pDlg;
			pDlg = NULL;
		}
		m_oblist_dlgATh.RemoveAll();
	}
}


void COpencvstudioDlg::OnBnClickedMfcbuttonFunTh()
{
	static int count = 0;
	CDlgFunThreshold* pDlg = NULL;
	pDlg = new CDlgFunThreshold;
	if (pDlg != NULL) {
		//pDlg->m_nNo = count++;
		pDlg->Create(IDD_DLG_FUN_THRESHOLD);
		pDlg->ShowWindow(SW_SHOW);
		m_oblist_dlgTh.AddTail(pDlg);
	}
}


void COpencvstudioDlg::OnBnClickedMfcbuttonFunAth()
{
	static int count = 0;
	CDlgFunThresholdA* pDlg = NULL;
	pDlg = new CDlgFunThresholdA;
	if (pDlg != NULL) {
		pDlg->Create(IDD_DLG_FUN_THRESHOLDA);
		pDlg->ShowWindow(SW_SHOW);
		m_oblist_dlgATh.AddTail(pDlg);
	}
}
