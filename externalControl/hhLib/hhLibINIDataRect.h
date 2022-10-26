#pragma once

class AFX_EXT_CLASS hhLibINIDataRect
{
public:
	hhLibINIDataRect();

public:
	struct stRect_t {
		int x;
		int y;
		int width;
		int height;
	};

private:
	BOOL m_isFile;
	CString m_iniPath;
	CString m_section;
	CString m_key;
	BOOL m_reset;

private:
	stRect_t m_val;

public:
	void Load(CString section, CString key, CString fullPath);
	stRect_t Get();
	BOOL Set(stRect_t val);
};

