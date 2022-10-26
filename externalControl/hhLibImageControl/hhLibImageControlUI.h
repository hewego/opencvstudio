#pragma once
#include "afxdialogex.h"
#include "resource.h"

class CImageControl;
class AFX_EXT_CLASS hhLibImageControlUI : public CDialogEx
{
	DECLARE_DYNAMIC(hhLibImageControlUI)

public:
	hhLibImageControlUI(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~hhLibImageControlUI();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLL_DLG_IMAGE_CONTROL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnMenu();
	afx_msg void OnBnClickedBtnFit();
	afx_msg void OnBnClickedBtnZOut();
	afx_msg void OnBnClickedBtnZIn();
	afx_msg void OnMenuLoad();
	afx_msg void OnMenuSave();
	afx_msg void OnMenuMeasure();
	afx_msg void OnMenuRoiShow();
	afx_msg void OnMenuRoiExport();
	afx_msg void OnMenuImageInfo();

private:
	void UpdateRatio();
	double CheckRatio(double dbl, bool bZoom = true);

private:
	CImageControl* m_pImageControl;
	bool m_bUseRoi;
	DOUBLE m_dbPixelRes; //um단위

private:
	bool m_bThemeBlack;
	CMenu m_Menu;
	COLORREF m_bkcolor;
	CBrush m_combo_brush;

public:
	void Init(CWnd* pParentWnd, bool toolBox, bool bThemeBlack);
	void SetPixelRes(DOUBLE res);
	void SetImage(cv::Mat img);
	cv::Mat GetImage();
	cv::Rect GetRoi();
	void SetRoi(BOOL bShow, cv::Rect rt = cv::Rect(0,0,0,0));
	afx_msg void OnImagerotateFlipvertical();
};
