﻿
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'pch.h'를 포함합니다."
#endif

#include "resource.h"		// 주 기호입니다.

class COpencvstudioDlg;
class COpencvstudioApp : public CWinApp
{
public:
	COpencvstudioApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern COpencvstudioApp theApp;
extern COpencvstudioDlg* theDlg;
extern void _debugLog(CString sType, TCHAR* lpszFormat, ...);