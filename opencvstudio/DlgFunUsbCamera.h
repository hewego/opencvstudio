#pragma once
#include "afxdialogex.h"

class CDlgFunUsbCamera : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFunUsbCamera)

public:
	CDlgFunUsbCamera(CWnd* pParent = nullptr);
	virtual ~CDlgFunUsbCamera();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FUN_USBCAMERA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedMfcbuttonGrab();
	afx_msg void OnBnClickedMfcbuttonOpen();
	afx_msg void OnBnClickedMfcbuttonShot();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedMfcbuttonToImage();
	afx_msg void OnCbnSelchangeComboExposure();

private:
	BOOL SetExpousertime(int no);
	BOOL ScanCard();

private:
	cv::VideoCapture m_cam;
	hhLibImageControlUI m_hhImage;
	cv::Mat m_matImg;
	BOOL m_bShot;
};
