#pragma once

class AFX_EXT_CLASS hhLibINIDataStr
{
public:
	hhLibINIDataStr();

private:
	BOOL m_isFile;
	CString m_iniPath;
	CString m_section;
	CString m_key;
	BOOL m_reset;

private:
	CString m_val;

public:
	void Load(CString section, CString key, CString fullPath);
	CString Get();
	BOOL Set(CString val);
};

