#pragma once

class CINIData
{
public:
	CINIData();
	~CINIData();

private:
	CString m_sFileName;
	CString m_sSection;
	CString m_sKey;

private:
	BOOL m_bReset;
	CString m_sData;

public:
	VOID Init(CString sFileName, CString sSection, CString sKey);
	BOOL GetVal(CString& sOutVal);
	BOOL SetVal(CString sInVal);
};