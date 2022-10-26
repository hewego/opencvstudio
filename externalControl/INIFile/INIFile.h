
#if !defined(AFX_INIFILE_H__241BF23C_B7BB_4711_BCB5_229A32245A95__INCLUDED_)
#define AFX_INIFILE_H__241BF23C_B7BB_4711_BCB5_229A32245A95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CINIFile  
{
public:
	CINIFile();
	CINIFile(CString sFileName);
	virtual ~CINIFile();

private:
	CString m_sFileName;

public:
	BOOL WriteInt(CString strSection, CString strKey, int nValue);
	UINT ReadInt(CString strSection, CString strKey, int nValue);
	BOOL WriteStr(CString strSection, CString strKey, CString strValue);
	CString	ReadStr(CString strSection, CString strKey, CString strValue);
	CString	ReadSection(CString strSection);
	BOOL WriteSection(CString strSection, CString strValue);
	BOOL DeleteSection(CString strSection);
	BOOL DeleteKey(CString strSection, CString strKey);
	CString ReadAllSection(int nMaxSize=4096);
	BOOL ReaAllKey(CString strSection, CStringArray& strAry, int nMaxSize=1024);
	int FindStringCnt(CString buf, CString string);

public:
	inline void SetFileName(CString strFileName){ m_sFileName = strFileName; }
	inline CString GetFileName(){ return m_sFileName; }

public:
	static CString ini_GetString(CString strPath, CString strSection, CString strKey);
	static int ini_GetInt(CString strPath, CString strSection, CString strKey);
};
#endif // !defined(AFX_INIFILE_H__241BF23C_B7BB_4711_BCB5_229A32245A95__INCLUDED_)
