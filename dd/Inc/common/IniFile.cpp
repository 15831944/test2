// IniOperation.cpp : implementation file
//

#include "stdafx.h"
#include "IniFile.h"




using namespace Leaf::IO;
CIniFile::CIniFile()
{
	m_sFilename = _T("");
	m_sFilePath = CDirectory::GetAppPath().c_str(); 
	m_sFilename = m_sFilePath + DefaultConfig;
}

CIniFile::~CIniFile()
{
}

void CIniFile::Init(LPCTSTR m_sFilePathname)
{
	m_sFilename = m_sFilePathname;
}

int CIniFile::ReadInt(LPCTSTR m_sAPP, LPCTSTR m_sKey)
{
	return GetPrivateProfileInt(m_sAPP,m_sKey,0,m_sFilename);
}

float CIniFile::ReadFloat(LPCTSTR m_sApp,LPCTSTR m_sKey)
{
	CString str;
	LPTSTR  pstr;
	float   val=0;

	pstr = str.GetBuffer(MAX_PATH);
	GetPrivateProfileString(m_sApp,m_sKey,_T("0.0"),pstr,MAX_PATH,m_sFilename);
//	sscanf(pstr,_T("%f"),&val);
//	swscanf_s(pstr,_T("%f"),&val);    //swscanf
	str.ReleaseBuffer();
	return val;
}

long CIniFile::ReadLong(LPCTSTR m_sAPP, LPCTSTR m_sKey)
{
	CString  str;
	LPSTR  pstr;
	long     val;

	pstr = str.GetBuffer(MAX_PATH);
	GetPrivateProfileString(m_sAPP,m_sKey,NULL,pstr,MAX_PATH,m_sFilename);
	val  = atol(pstr);
//	val  = _wtol(pstr);
	str.ReleaseBuffer();
	return val;
}

bool CIniFile::ReadBool(LPCTSTR m_sAPP, LPCTSTR m_sKey)
{
	CString str;
	LPTSTR  pstr;
	bool    boolValue;
	
	pstr = str.GetBuffer(MAX_PATH);
	GetPrivateProfileString(m_sAPP,m_sKey,NULL,pstr,MAX_PATH,m_sFilename);
//	boolValue = static_cast<int>(pstr);            //Convert.ToBoolean(obj);Convert.ToInt32(obj)
	if (_ttoi(static_cast<LPCTSTR>(pstr)))         //_wtoi;i=atoi(T2A(str));
	{
		boolValue = true;
	}
	else
	{
		boolValue = false;
	}
	str.ReleaseBuffer();
	return boolValue;
}

CString CIniFile::ReadCString(LPCTSTR m_sApp,TCHAR* m_sKey)//LPCTSTR
{
	CString str;
	LPTSTR  pstr;

	pstr = str.GetBuffer(MAX_PATH);
	GetPrivateProfileString(m_sApp,m_sKey,NULL,pstr,MAX_PATH,m_sFilename);
	
	str.ReleaseBuffer();
	return str;
}

/**
COLORREF   cl;
red   =   cl   &   0xFF;
green   =   (cl   > >   8)   &   0xFF;
blue   =   (cl   > >   16)   &   0xFF;
**/

COLORREF CIniFile::ReadRGB(LPCTSTR m_sApp, LPCTSTR m_sKey)
{
	CString  str;
	LPTSTR   pstr;
	COLORREF val;

	pstr = str.GetBuffer(MAX_PATH);
	GetPrivateProfileString(m_sApp,m_sKey,NULL,pstr,MAX_PATH,m_sFilename);
	val  = HexToRGB(pstr);
	str.ReleaseBuffer();
	return val;
}

COLORREF CIniFile::HexToRGB(const CString &cszHex)
{
	int nR, nG, nB;

	CString  strInfo = cszHex;
	CString* pstr;
	int isubstrs;
	pstr = SplitString(strInfo,',',isubstrs);
	if (isubstrs != 3)
	{
		MessageBox(NULL,_T("错误的颜色格式!"),_T("警告"),MB_ICONWARNING|MB_OK);
		return 0;
	}
	else
	{
		CString cszR = _T("0x")+pstr[0];
		CString cszG = _T("0x")+pstr[1];
		CString cszB = _T("0x")+pstr[2];
/*		CString cszR,cszG,cszB;
		cszR.Format(_T("0x%s"),pstr[0]);
		cszG.Format(_T("0x%s"),pstr[1]);
		cszB.Format(_T("0x%s"),pstr[2]);*/

		nR = strtol(cszR, NULL, 16);	//wcstol
		nG = strtol(cszG, NULL, 16);
		nB = strtol(cszB, NULL, 16);

	}
	COLORREF crColor = RGB(nR, nG, nB);
	return crColor;
}


CString* CIniFile::SplitString(CString cszHex, char split, int& iSubStrs)
{
	int iPos=0;
	int iNums=0;

	CString strTemp=cszHex;
	CString strRight;

	while(iPos!=-1)
	{
		iPos = strTemp.Find(split);
		if (iPos == -1)
		{
			break;
		}

		strRight = strTemp.Mid(iPos+1,cszHex.GetLength());
		strTemp  = strRight;
		iNums++;
	}

	if (iNums == 0)
	{
		iSubStrs =1;
		return NULL;
	}

	iSubStrs = iNums +1;
	CString* pStrSplit;
	pStrSplit = new CString[iSubStrs];
	strTemp = cszHex;
	CString strLeft;

	for (int i=0; i<iNums; i++)
	{
		iPos = strTemp.Find(split);
		strLeft  = strTemp.Left(iPos);
		strRight = strTemp.Mid(iPos+1,strTemp.GetLength());
		strTemp  = strRight;
		pStrSplit[i] = strLeft;
	}
	pStrSplit[iNums] = strTemp;
	return pStrSplit;
}


/*
void CIniOperation::ReadArray(CString m_sApp,CString m_sKey,int* m_Val,long nums)
{
	int         i;
	CString		m_sNo;

	for (i=1;i<=nums;i++)
	{
		m_sNo.Format("")
	}
}*/


void CIniFile::Write(CString m_sApp,CString m_sKey,int m_Val)
{
	CString str;
	str.Format(_T("%d"),m_Val);
	::WritePrivateProfileString(m_sApp,m_sKey,str,m_sFilename);
}

void CIniFile::Write(CString m_sApp,CString m_sKey,float m_Val)
{
	CString str;
	str.Format(_T("%f"),m_Val);
	::WritePrivateProfileString(m_sApp,m_sKey,str,m_sFilename);
}

void CIniFile::Write(CString m_sApp,CString m_sKey,TCHAR* m_Val)//CString
{
	::WritePrivateProfileString(m_sApp,m_sKey,m_Val,m_sFilename);
}

void CIniFile::Write(CString m_sApp,CString m_sKey,bool m_Val)
{
	int nSign;
	if (m_Val)
	{
		nSign = 1;
	}
	else
	{
		nSign = 0;
	}
	CString str;
	str.Format(_T("%d"),nSign);
	::WritePrivateProfileString(m_sApp,m_sKey,str,m_sFilename);
}


void CIniFile::Write(CString m_sApp,CString m_sKey,COLORREF m_Val)
{
	int nR, nG, nB;
	nR = m_Val & 0xFF;
	nG = (m_Val >> 8)  &0xFF;
	nB = (m_Val >> 16) &0xff;

	CString str;
	str.Format(_T("%d,%d,%d"),nR,nG,nB);
	::WritePrivateProfileString(m_sApp,m_sKey,str,m_sFilename);
}