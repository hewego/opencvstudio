#include "stdafx.h"
#include "INIData.h"

CINIData::CINIData()
{
}

CINIData::~CINIData()
{
}

VOID CINIData::Init(CString sFileName, CString sSection, CString sKey)
{
	m_sFileName = sFileName;
	m_sSection = sSection;
	m_sKey = sKey;
	m_bReset = TRUE;
}

BOOL CINIData::GetVal(CString& sOutVal)
{
	if (!m_bReset) {
		sOutVal = m_sData;
		return TRUE;
	}

	BOOL bResult = FALSE;
	TCHAR szResult[MAX_PATH + 1] = { NULL, };
	GetPrivateProfileString(m_sSection, m_sKey, _T(""), szResult, (MAX_PATH + 1), m_sFileName);
	m_sData.Format(_T("%s"), szResult);
	
	sOutVal = m_sData;
	m_bReset = FALSE;
	return bResult;
}

BOOL CINIData::SetVal(CString sInVal)
{
	m_bReset = TRUE;
	return WritePrivateProfileString(m_sSection, m_sKey, sInVal, m_sFileName);
}