#pragma once

class AFX_EXT_CLASS hhLibINIDataInt
{
public:
	hhLibINIDataInt();

private:
	BOOL m_isFile;
	CString m_iniPath;
	CString m_section;
	CString m_key;
	BOOL m_reset;

private:
	int m_val;

public:
	void Load(CString section, CString key, CString fullPath);
	int Get();
	BOOL Set(int val);
};

