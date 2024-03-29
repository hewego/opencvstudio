﻿
#include "pch.h"
#include "framework.h"
#include "opencvstudio.h"
#include "opencvstudioDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(COpencvstudioApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


COpencvstudioApp::COpencvstudioApp()
{
}


COpencvstudioApp theApp;
COpencvstudioDlg* theDlg;


BOOL COpencvstudioApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);

	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	AfxEnableControlContainer();


	CShellManager *pShellManager = new CShellManager;

	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
	
	SetRegistryKey(_T("로컬 애플리케이션 마법사에서 생성된 애플리케이션"));

	COpencvstudioDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 여기에 [확인]을 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 여기에 [취소]를 클릭하여 대화 상자가 없어질 때 처리할
		//  코드를 배치합니다.
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "경고: 대화 상자를 만들지 못했으므로 애플리케이션이 예기치 않게 종료됩니다.\n");
		TRACE(traceAppMsg, 0, "경고: 대화 상자에서 MFC 컨트롤을 사용하는 경우 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS를 수행할 수 없습니다.\n");
	}

	// 위에서 만든 셸 관리자를 삭제합니다.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 대화 상자가 닫혔으므로 응용 프로그램의 메시지 펌프를 시작하지 않고 응용 프로그램을 끝낼 수 있도록 FALSE를
	// 반환합니다.
	return FALSE;
}


void _debugLog(CString sType, TCHAR* lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);

	int nBuf;
	TCHAR szBuffer[1024];
	memset(szBuffer, NULL, sizeof(TCHAR) * 1024);
	nBuf = _vsntprintf(szBuffer, _countof(szBuffer), lpszFormat, args);

	CString str;
	if (sType == LOG_MAIN) {
		static CQueryPerformanceTime pTime;
		str.Format(_T("[%05d] %s"), pTime.End(), szBuffer);
		theDlg->SetLog(str);
	}
}


CString _curDir()
{
	CString str;
	TCHAR szCurDir[MAX_PATH];
	memset(szCurDir, 0, sizeof(szCurDir));
	GetCurrentDirectory(MAX_PATH, szCurDir);
	str.Format(_T("%s"), szCurDir);
	return str;
}


int _getDlgItemInt(CWnd* pWnd, int nID)
{
	return pWnd->GetDlgItemInt(nID);
}


DOUBLE _getDlgItemDb(CWnd* pWnd, int nID)
{
	CString str;
	pWnd->GetDlgItemText(nID, str);
	return _ttof(str);
}


CString _getDlgItemStr(CWnd* pWnd, int nID)
{
	CString str;
	pWnd->GetDlgItemText(nID, str);
	return str;
}

int _makeOdd(int nVal)
{
	if ((nVal % 2) == 0) {
		return  nVal + 1;
	}

	return nVal;
}

int _str2int(CString str, CString strCut)
{
	str.Replace(_T(" "), _T(""));
	str.Replace(strCut, _T(""));
	return _ttoi(str);
}

CString _int2str(int nValue)
{
	CString str;
	str.Format(_T("%d"), nValue);
	return str;
}

double _str2db(CString sVal)
{
	return _ttof(sVal);
}

CString _db2str(DOUBLE dbVal)
{
	CString str;
	str.Format(_T("%.2f"), dbVal);
	return str;
}