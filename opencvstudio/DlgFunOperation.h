#pragma once
#include "afxdialogex.h"


class CDlgFunOperation : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFunOperation)

public:
	CDlgFunOperation(CWnd* pParent = nullptr);
	virtual ~CDlgFunOperation();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_FUN_OPERATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	DECLARE_MESSAGE_MAP()
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedMfcbuttonApply();
	afx_msg void OnCbnSelchangeComboMethod();
	afx_msg void OnCbnSelchangeComboMethod2();

private:
	enum class eOperatorMethode {
		Invert,
		Add,
		Subtract,
		Multiply,
		Divide,
		Compare,
		AddWeighted,
		AdobeAddition,
		AdobeSubtract,
		AdobeMultiply,
		AdobeDifference,
		AdobeDivide,
		Modulo,
		MeanStdDev,			//평균 및 표준편찻
		CountNonZero,		//행렬 src에서 0이 아닌 요소의 개수를 반환
		Integral,
		Max,
	};

private:
	CString ToString(eOperatorMethode val);

private:
	BOOL Add(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst);
	BOOL Subtract(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst);
	BOOL Multiply(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst);
	BOOL Divide(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst);
	BOOL Compare(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst, int nMethode);
	BOOL AddWeighted(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst);
	BOOL AdbAddition(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst);
	BOOL AdbSubtract(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst);
	BOOL AdbMultiply(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst);
	BOOL AdbDifference(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst);
	BOOL AdbDivide(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst);
	BOOL Modulo(cv::Mat& matSrc1, cv::Mat& matSrc2, cv::Mat& matDst);
};
