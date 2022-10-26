#include <wtypes.h>
#include <afxwin.h>
#if !defined(AFX_LABELCTRL_H__317D9557_202C_4D21_BD9D_C277762CF9E0__INCLUDED_)
#define AFX_LABELCTRL_H__317D9557_202C_4D21_BD9D_C277762CF9E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////
// ±âº»»ý¼ºÄÚµå
//////////////////////////////////////////////////////////////////////////
/*
	m_StaticMsg.SetBkColor(RGB(0,0,0));
	m_StaticMsg.SetFontName("¸¼Àº °íµñ");
	m_StaticMsg.SetTextColor(RGB(255,255,255));
	m_StaticMsg.SetFontBold(TRUE);
	m_StaticMsg.SetFontSize(20);
	m_StaticMsg.SetBorder(FALSE);


	BaseUICtrl::CLabelCtrl* pLabel;
	pLabel = &m_StaticCurMaskSizeA;
	pLabel->SetBkColor(RGB(0,0,0));
	pLabel->SetFontName("¸¼Àº °íµñ");
	pLabel->SetTextColor(RGB(255,255,255));
	pLabel->SetFontBold(TRUE);
	pLabel->SetFontSize(20);
	pLabel->SetBorder(FALSE);

*/

//enum FlashType {None, Text, Background };

class CLabelCtrl : public CStatic
{
public:
	CLabelCtrl();
	virtual ~CLabelCtrl();

private:
	COLORREF	m_crText;		// Text Color
	COLORREF	m_crBKColor;
	HCURSOR		m_hCursor;		// Cursor Handle
	HBRUSH		m_hBrush;		// Brush Handle
	HBRUSH		m_hwndBrush;	// Window Brush Handel
	LOGFONT		m_lf;			// Font
	CFont		m_font;			// Font
	CString		m_strText;		// Text Value
	BOOL		m_bState;		// State Flag
	BOOL		m_bTimer;		// Timer Flag
	BOOL		m_bLink;		// Link Flag
//	FlashType	m_Type;			// Flash Type

protected:
	void ReconstructFont();

protected:
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void PreSubclassWindow();
	DECLARE_MESSAGE_MAP()

public:
	CLabelCtrl&	SetBkColor(COLORREF crBkgnd);
	CLabelCtrl&	SetTextColor(COLORREF crText);
	CLabelCtrl&	SetText(const CString& strText);
	CLabelCtrl&	SetFontBold(BOOL bBold);
	CLabelCtrl&	SetFontName(const CString& strFont);
	CLabelCtrl&	SetFontUnderline(BOOL bSet);
	CLabelCtrl&	SetFontItalic(BOOL bSet);
	CLabelCtrl&	SetFontSize(int nSize);
	CLabelCtrl&	SetSunken(BOOL bSet);
	CLabelCtrl&	SetBorder(BOOL bSet);
	//CLabelCtrl&	FlashText(BOOL bActivate);
	//CLabelCtrl&	FlashBackground(BOOL bActivate);
	CLabelCtrl&	SetLink(BOOL bLink);
	CLabelCtrl&	SetLinkCursor(HCURSOR hCursor);
	void SetTitleChange(COLORREF clrBKTilte, LPCTSTR lpszText);
	void Init(int nSize=17, BOOL bBold=TRUE, CString sFontName=_T("Calibri"), COLORREF crBK=RGB(0,0,0), COLORREF crText=RGB(255,255,255));
};

#endif

