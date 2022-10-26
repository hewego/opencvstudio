
#include "pch.h"
#include "framework.h"
#include "opencvstudio.h"
#include "opencvstudioDlg.h"
#include "afxdialogex.h"
#include "DlgFunThreshold.h"

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


// CopencvstudioDlg 대화 상자



CopencvstudioDlg::CopencvstudioDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPENCVSTUDIO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CopencvstudioDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CopencvstudioDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_VIEW_IMAGE1, &CopencvstudioDlg::OnViewImage1)
	ON_COMMAND(ID_VIEW_IMAGE2, &CopencvstudioDlg::OnViewImage2)
	ON_COMMAND(ID_VIEW_IMAGE3, &CopencvstudioDlg::OnViewImage3)
	ON_COMMAND(ID_VIEW_IMAGE4, &CopencvstudioDlg::OnViewImage4)
	ON_COMMAND(ID_VIEW_IMAGE5, &CopencvstudioDlg::OnViewImage5)
	ON_COMMAND(ID_VIEW_IMAGE5, &CopencvstudioDlg::OnViewImage6)
	ON_BN_CLICKED(IDC_MFCBUTTON_FUN_TH, &CopencvstudioDlg::OnBnClickedMfcbuttonFunTh)
END_MESSAGE_MAP()


BOOL CopencvstudioDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

void CopencvstudioDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CopencvstudioDlg::OnPaint()
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


HCURSOR CopencvstudioDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CopencvstudioDlg::OnViewImage1()
{
	m_DlgImg[0].ShowWindow(SW_SHOW);
}


void CopencvstudioDlg::OnViewImage2()
{
	m_DlgImg[1].ShowWindow(SW_SHOW);
}


void CopencvstudioDlg::OnViewImage3()
{
	m_DlgImg[2].ShowWindow(SW_SHOW);
}


void CopencvstudioDlg::OnViewImage4()
{
	m_DlgImg[3].ShowWindow(SW_SHOW);
}


void CopencvstudioDlg::OnViewImage5()
{
	m_DlgImg[4].ShowWindow(SW_SHOW);
}


void CopencvstudioDlg::OnViewImage6()
{
	m_DlgImg[5].ShowWindow(SW_SHOW);
}


void CopencvstudioDlg::OnBnClickedMfcbuttonFunTh()
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


void CopencvstudioDlg::OnCancel()
{
	ResetDlg();
	CDialogEx::OnCancel();
}


void CopencvstudioDlg::ResetDlg()
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
}