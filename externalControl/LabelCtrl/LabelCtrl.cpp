#include "pch.h"
#include "LabelCtrl.h"
#include <tchar.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CLabelCtrl::CLabelCtrl()
{
	m_crText = GetSysColor(COLOR_WINDOWTEXT);
	m_hBrush = ::CreateSolidBrush(GetSysColor(COLOR_3DFACE));

	::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT), sizeof(m_lf), &m_lf);

	m_lf.lfCharSet			= DEFAULT_CHARSET;
	m_lf.lfOutPrecision		= OUT_DEFAULT_PRECIS;
	m_lf.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	m_lf.lfQuality			= CLEARTYPE_NATURAL_QUALITY;
	//_stprintf(m_lf.lfFaceName, _T("%s"), _T("Arial"));
	_stprintf(m_lf.lfFaceName, _T("%s"), _T("Arial"));

	m_font.CreateFontIndirect(&m_lf);

	m_bTimer	= FALSE;
	m_bState	= FALSE;
	m_bLink		= TRUE;
	m_hCursor	= NULL;
	m_strText = _T("");

	m_hwndBrush = ::CreateSolidBrush(GetSysColor(COLOR_3DFACE));
}

CLabelCtrl::~CLabelCtrl()
{
}

BEGIN_MESSAGE_MAP(CLabelCtrl, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

CLabelCtrl& CLabelCtrl::SetText(const CString& strText)
{
	if (m_strText == strText){
		return *this;
	}

	m_strText = strText;

	SetWindowText(m_strText);
	return *this;
}

void CLabelCtrl::SetTitleChange(COLORREF clrBKTilte, LPCTSTR lpszText)
{
	if (m_strText != lpszText)
	{
		m_strText = lpszText;
		SetWindowText(m_strText);
	}

	if (m_crBKColor != clrBKTilte)
	{
		m_crBKColor = clrBKTilte;

		if (m_hBrush)
			::DeleteObject(m_hBrush);

		m_hBrush = ::CreateSolidBrush(m_crBKColor);

		Invalidate(FALSE);
	}
}

CLabelCtrl& CLabelCtrl::SetTextColor(COLORREF crText)
{
	m_crText = crText;
	RedrawWindow();
	return *this;
}

CLabelCtrl& CLabelCtrl::SetFontBold(BOOL bBold)
{	
	m_lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	ReconstructFont();
	RedrawWindow();
	return *this;
}

CLabelCtrl& CLabelCtrl::SetFontUnderline(BOOL bSet)
{	
	m_lf.lfUnderline = bSet;
	ReconstructFont();
	RedrawWindow();
	return *this;
}

CLabelCtrl& CLabelCtrl::SetFontItalic(BOOL bSet)
{
	m_lf.lfItalic = bSet;
	ReconstructFont();
	RedrawWindow();
	return *this;	
}

CLabelCtrl& CLabelCtrl::SetSunken(BOOL bSet)
{
	if (!bSet)
		ModifyStyleEx(WS_EX_STATICEDGE,0,SWP_DRAWFRAME);
	else
		ModifyStyleEx(0,WS_EX_STATICEDGE,SWP_DRAWFRAME);
		
	return *this;	
}

CLabelCtrl& CLabelCtrl::SetBorder(BOOL bSet)
{
	if (!bSet)
		ModifyStyle(WS_BORDER,0,SWP_DRAWFRAME);
	else
		ModifyStyle(0,WS_BORDER,SWP_DRAWFRAME);
		
	return *this;	
}

CLabelCtrl& CLabelCtrl::SetFontSize(int nSize)
{
	nSize*=-1;
	m_lf.lfHeight = nSize;
	ReconstructFont();
	RedrawWindow();
	return *this;
}

CLabelCtrl& CLabelCtrl::SetBkColor(COLORREF crBkgnd)
{
// 	if (m_crBKColor == crBkgnd){
// 		return *this; 
// 	}

	m_crBKColor = crBkgnd;

	if (m_hBrush)
		::DeleteObject(m_hBrush);
	
	m_hBrush = ::CreateSolidBrush(m_crBKColor);

	Invalidate(FALSE);

	return *this;
}

CLabelCtrl& CLabelCtrl::SetFontName(const CString& strFont)
{	
	_tcscpy(m_lf.lfFaceName, strFont);
	ReconstructFont();
	RedrawWindow();
	return *this;
}

// CLabelCtrl& CLabelCtrl::FlashText(BOOL bActivate)
// {
// 	if (m_bTimer)
// 	{
// 		SetWindowText(m_strText);
// 		KillTimer(1);
// 	}
// 
// 	if (bActivate)
// 	{
// 		GetWindowText(m_strText);
// 		m_bState = FALSE;
// 		
// 		m_bTimer = TRUE;
// 		SetTimer(1,300,NULL);
// 		m_Type = Text;
// 	}
// 
// 	return *this;
// }

// CLabelCtrl& CLabelCtrl::FlashBackground(BOOL bActivate)
// {
// 	if (m_bTimer)
// 		KillTimer(1);
// 
// 	if (bActivate)
// 	{
// 		m_bState = FALSE;
// 
// 		m_bTimer = TRUE;
// 		SetTimer(1, 300, NULL);
// 
// 		m_Type = Background;
// 	}
// 
// 	return *this;
// }

CLabelCtrl& CLabelCtrl::SetLink(BOOL bLink)
{
	m_bLink = bLink;

	if (bLink)
		ModifyStyle(0, SS_NOTIFY);
	else
		ModifyStyle(SS_NOTIFY, 0);

	return *this;
}

CLabelCtrl& CLabelCtrl::SetLinkCursor(HCURSOR hCursor)
{
	m_hCursor = hCursor;
	return *this;
}

void CLabelCtrl::ReconstructFont()
{
	m_font.DeleteObject();
	BOOL bCreated = m_font.CreateFontIndirect(&m_lf);

	ASSERT(bCreated);
}

HBRUSH CLabelCtrl::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	if (CTLCOLOR_STATIC == nCtlColor)
	{
		pDC->SelectObject(&m_font);
		pDC->SetTextColor(m_crText);
		pDC->SetBkMode(TRANSPARENT);
	}

// 	if (m_Type == Background)
// 	{
// 		if (!m_bState)
// 			return m_hwndBrush;
// 	}

	return m_hBrush;
}

BOOL CLabelCtrl::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (m_hCursor)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}

	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

void CLabelCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CString strLink;

//	GetWindowText(strLink);
//	ShellExecute(NULL,"open",strLink,NULL,NULL,SW_SHOWNORMAL);
		
	CStatic::OnLButtonDown(nFlags, point);
}

void CLabelCtrl::PreSubclassWindow()
{
	GetWindowText(m_strText);
}

void CLabelCtrl::Init(int nSize, BOOL bBold, CString strFontName, COLORREF crBK, COLORREF crText)
{
	SetBkColor(crBK);
	SetFontName(strFontName);
	SetTextColor(crText);
	SetFontBold(bBold);
	SetFontSize(nSize);
	SetBorder(FALSE);
}
