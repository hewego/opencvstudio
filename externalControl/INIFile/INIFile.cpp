
#include "pch.h"
#include "INIFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CINIFile::CINIFile()
{
}

CINIFile::CINIFile(CString sFileName)
{
	m_sFileName = sFileName;
}

CINIFile::~CINIFile()
{
}

UINT CINIFile::ReadInt(CString strSection, CString strKey, int nValue)
{
	return GetPrivateProfileInt(strSection, strKey, nValue, m_sFileName);
}

BOOL CINIFile::WriteInt(CString strSection, CString strKey, int nValue)
{
	TCHAR szValue[16] = {'\n', };
	//_stprintf(szValue, _T("%i"), nValue);
	_stprintf(szValue, _T("%i"), nValue);

	return WritePrivateProfileString(strSection, strKey, szValue, m_sFileName);
}

CString CINIFile::ReadStr(CString strSection, CString strKey, CString strValue)
{
	TCHAR szResult[MAX_PATH + 1] = {NULL, };
	int  nIndex = 0;
	CString strData = _T("");
	CString strTemd = _T("");

	GetPrivateProfileString(strSection, strKey, strValue, szResult, (MAX_PATH + 1), m_sFileName);

	strData.Format(_T("%s"), szResult);
	nIndex = strData.Find(_T("//"), 0);
	if (!(nIndex == -1))
	{
		strTemd = strData.Left(nIndex-1);
		strTemd.TrimLeft();
		strTemd.TrimRight();
		strTemd.Replace(_T(" "), _T(""));
		strTemd.Replace(_T("\r\n"), _T(""));
	}
	else
	{
		return strData;
	}

	return strTemd;
}

BOOL CINIFile::WriteStr(CString strSection, CString strKey, CString strValue)
{
	return WritePrivateProfileString(strSection, strKey, strValue, m_sFileName);
}

BOOL CINIFile::DeleteSection(CString strSection)
{
	return WritePrivateProfileSection(strSection, NULL, m_sFileName);
}

BOOL CINIFile::DeleteKey(CString strSection, CString strKey)
{
	return WritePrivateProfileString(strSection, strKey, NULL, m_sFileName);
}

CString CINIFile::ReadSection(CString strSection)
{
	TCHAR szResult[MAX_PATH + 1] = {NULL, };
	GetPrivateProfileSection(strSection, szResult, (MAX_PATH + 1), m_sFileName);
	return szResult;
}

BOOL CINIFile::WriteSection(CString strSection, CString strValue)
{
	return WritePrivateProfileSection(strSection, strValue, m_sFileName);
}

CString CINIFile::ReadAllSection(int nMaxSize)
{
//#ifdef UNICODE
//	CString strString;
//	return strString;
//
//	TCHAR* pBuff = new TCHAR[nMaxSize];
//	memset(pBuff, NULL, sizeof(TCHAR)*nMaxSize);
//	DWORD n = ::GetPrivateProfileSectionNames(pBuff, nMaxSize, m_strFileName);
//
//#else
	CString str;
	CString strString;
	TCHAR* pBuff;
	pBuff = new TCHAR[nMaxSize];
	memset(pBuff, NULL, sizeof(TCHAR)*nMaxSize);
	TCHAR sect[512] = { 0x00, };

	DWORD n = ::GetPrivateProfileSectionNames(pBuff, nMaxSize, m_sFileName);

	int pos=0;
	BOOL bMakedSect=FALSE; // 하나의 섹션을 구성완료하면 TRUE하여 pos를 0으로 초기화
	for(int i=0; i<n; i++, pos++){
		if(pBuff[i] != '\0'){
			if(bMakedSect){ 
				pos = 0;
			}

			memcpy(sect+pos, pBuff+i, 1);
			bMakedSect = FALSE;
			continue;
		}
		else{
			//sect[i] = '\0';
			str.Format(_T("%s"), sect);
			strString+=str;
			strString+=",";
			memset(sect, 0x00, sizeof(sect));
			bMakedSect = TRUE;
		}
	}
	delete[] pBuff;
	return strString;
//#endif
}

BOOL CINIFile::ReaAllKey(CString strSection, CStringArray& strAry, int nMaxSize)
{
	//CString strPath;
	//strPath = _T("D:\\Dev\\CimSvr1\\CimSvr\\Bin\\data\\Temp.ini");
	
	//char* pBuff;
	//pBuff = new char[nMaxSize];
	//memset(pBuff, NULL, sizeof(char)*nMaxSize);
	//char sect[512] = {0x00,};

	TCHAR* pBuff;
	pBuff = new TCHAR[nMaxSize];
	memset(pBuff, NULL, sizeof(char)*nMaxSize);
	char sect[512] = {0x00,};

	DWORD n = GetPrivateProfileSection(strSection, pBuff, nMaxSize, m_sFileName);

	CString str;
	int pos=0;
	BOOL bMakedSect=FALSE; // 하나의 섹션을 구성완료하면 TRUE하여 pos를 0으로 초기화
	for(int i=0; i<n; i++, pos++){
		if(pBuff[i] != '\0'){
			if(bMakedSect){ 
				pos = 0;
			}

			memcpy(sect+pos, pBuff+i, 1);
			bMakedSect = FALSE;
			continue;
		}
		else{
			//sect[i] = '\0';
			str.Format(_T("%s"), sect);
			memset(sect, 0x00, sizeof(sect));
			strAry.Add(str);
			bMakedSect = TRUE;
		}
	}

	delete[] pBuff;
	return TRUE;
}

int CINIFile::FindStringCnt(CString buf, CString string)
{
	int nCnt = 0;
	int	nCntBuf = 0;
	int nfind = 0;

	while (nCntBuf >= 0)
	{
		nCntBuf = buf.Find(string, nfind);
		nfind = nCntBuf+1;
		nCnt++;
	}

	return nCnt-1;
}

CString CINIFile::ini_GetString(CString strPath, CString strSection, CString strKey)
{
	TCHAR szResult[MAX_PATH + 1] = {NULL, };
	int  nIndex = 0;
	CString strData;
	CString strTemd;
	CString strValue;

	GetPrivateProfileString(strSection, strKey, strValue, szResult, (MAX_PATH + 1), strPath);

	strData.Format(_T("%s"), szResult);
	nIndex = strData.Find(_T("//"), 0);
	if (!(nIndex == -1))
	{
		strTemd = strData.Left(nIndex-1);
		strTemd.TrimLeft();
		strTemd.TrimRight();
		strTemd.Replace(_T(" "), _T(""));
		strTemd.Replace(_T("\r\n"), _T(""));
	}
	else
	{
		return strData;
	}

	return strTemd;
}

int CINIFile::ini_GetInt(CString strPath, CString strSection, CString strKey)
{
	int nValue = 0;
	return GetPrivateProfileInt(strSection, strKey, nValue, strPath);
}
