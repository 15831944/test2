// Directory.cpp: implementation of the CDirectory class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Directory.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


using namespace Leaf::IO;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirectory::CDirectory()
{

}

CDirectory::~CDirectory()
{

}

//////////////////////////////////////////////////////////////////////////
//文件目录管理

CString CDirectory::GetAppPath()
{
	CString  strAppPath;
	TCHAR    szModuleFileName[MAX_PATH +1];
	ZeroMemory(szModuleFileName, MAX_PATH +1);
	
	::GetModuleFileName(NULL, szModuleFileName, sizeof(szModuleFileName)/sizeof(TCHAR));
	//_splitpath     //_tcsrchr
/*	TCHAR     szDrive[_MAX_DRIVE];
	ZeroMemory(szDrive, _MAX_DRIVE);
	TCHAR     szDir[_MAX_DIR];
	ZeroMemory(szDir, _MAX_DIR);
	_tsplitpath(szModuleFileName, szDrive, szDir, NULL, NULL);
	_tcscpy(szModuleFileName, szDrive);
	_tcscat(szModuleFileName, szDir);
	strAppPath = CString(szModuleFileName);
	*/
	strAppPath = CString(szModuleFileName);
	int nPos   = strAppPath.ReverseFind('\\');
	strAppPath = strAppPath.Left(nPos);
	return strAppPath;
}


BOOL CDirectory::IsFileExists(LPCTSTR lpszFileName)
{
/*
	DWORD dwAttributes = GetFileAttributes(lpszFileName);
	if(dwAttributes == 0xFFFFFFFF)
	{
		return FALSE;
	} 

	if((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
	{
		return bIsDirCheck;
	}
	else
	{
		return !bIsDirCheck;
	}
*/	
	WIN32_FIND_DATA fd;
	BOOL bRet = FALSE;
	HANDLE hFind = FindFirstFile(lpszFileName, &fd);
	
	if ((hFind != INVALID_HANDLE_VALUE) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
	{
		bRet = TRUE;
	}
	FindClose(hFind);
	return bRet;
}
bool CDirectory::FolderExists(CString s)
{
	DWORD attr;
	attr = GetFileAttributes(s);
	return (attr != (DWORD)(-1)) && (attr & FILE_ATTRIBUTE_DIRECTORY);
}

bool CDirectory::CreateDir(CString p)
{
	int len = p.GetLength();
	if (len < 2)
	{
		return false;
	}

	if ('\\' == p[len-1])
	{
		p   = p.Left(len-1);
		len = p.GetLength();
	}

	if (len <= 0)
	{
		return false;
	}

	if (len <= 3)
	{
		if (FolderExists(p))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	if (FolderExists(p))
	{
		return true;
	}

	CString Parent;
	Parent = p.Left(p.ReverseFind('\\'));
	if (Parent.GetLength() <= 0)
	{
		return false;
	}

	bool bRet = CreateDir(Parent);
	if (bRet)
	{
		SECURITY_ATTRIBUTES sa; 
		sa.nLength=sizeof(SECURITY_ATTRIBUTES); 
		sa.lpSecurityDescriptor=NULL;   
	    sa.bInheritHandle=0;
		bRet = (bool)(CreateDirectory(p,&sa) == TRUE);
		return true;
	}
	else{return FALSE;}
}

bool CDirectory::DeleteDirectory(TCHAR* sDirName)
{
	CFileFind file;
	char sFileFind[200];

	sprintf_s(sFileFind,"%s\\*.*",sDirName);	//sprintf
	BOOL IsFinded =file.FindFile((LPCTSTR)sFileFind);
	while(IsFinded)
	{
		IsFinded =file.FindNextFile();
		if (!file.IsDots())
		{
			TCHAR sFileName[200];
			strcpy_s(sFileName,file.GetFileName().GetBuffer(200));//strcpy //wcscpy
			if (file.IsDirectory())
			{
				TCHAR sDir[200];
				sprintf_s(sDir,_T("%s\\%s"),sDirName,sFileName);//sprintf //wsprintf
				DeleteDirectory(sDir);
			}
			else
			{
				TCHAR sTDir[200];
				wsprintf(sTDir,_T("%s\\%s"),sDirName,sFileName);
				DeleteDirectory(sTDir);
			}
		}
	}
	file.Close();
	if (!RemoveDirectory(sDirName))
	{
		AfxMessageBox(_T("文件删除失败!"));
		TCHAR sTmpDir[200] = _T("");
		wsprintf(sTmpDir,_T("rmdir /s /q %s"),sDirName);
		AfxMessageBox(sTmpDir);
//		WinExec(_T("rmdir /s /q "))
		return false;
	}
	else
	{
		AfxMessageBox(_T("文件删除成功!"));
		return true;
	}
}


//目录选择
bool CDirectory::SelectMenu(HWND hWnd,TCHAR*pPath,TCHAR*pDisplayString)
{
	ITEMIDLIST *ppidl;
	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP ,&ppidl); 
	if ( ppidl == NULL)   
    {   
        AfxMessageBox(_T("Start browsing path failure "));   
        return false;
    }   
	TCHAR path[255] = _T("");
	BROWSEINFO *bi = new BROWSEINFO; 
	bi->hwndOwner = hWnd;   //this->GetSafeHwnd();
	bi->pidlRoot  = ppidl;
	bi->pszDisplayName = path;
	bi->lpszTitle = pDisplayString;  //_T("Select Dir...");
	bi->lpfn      = NULL;
	bi->ulFlags   = BIF_BROWSEINCLUDEFILES; //| 0x0040 ;  //0x0040 BIF_NEWDIALOGSTYLE
	bi->lParam    = 0;
	bi->iImage    = 0; 
	ppidl = SHBrowseForFolder(bi);
	if ( !SHGetPathFromIDList(ppidl,path))   
    {   
        delete bi;   
        return false; 
    }
	delete bi;
	//	wcscpy(pPath,path);
	CString s = path ;
	if ( s.Right( 1 ) != _T("\\") )
	{
		s+= _T("\\") ;
	}
//	wcscpy(pPath,CString2TCHAR(s));
	
	return true;
}

//////////////////////////////////////////////////////////////////////////
