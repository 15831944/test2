#include "stdafx.h"
#include "Directory.h"

using namespace Leaf::IO;
CDirectory::CDirectory()
{
}

CDirectory::~CDirectory()
{
}

//////////////////////////////////////////////////////////////////////////
//文件目录管理
std::string CDirectory::GetAppPath()
{
	int npos = 0;

	char szFilePath[MAX_PATH+1] = {0};
	char szModuleFileName[MAX_PATH +1] = {0};

	char* p = NULL;
	std::string  strAppPath;

#ifdef _WIN_32_
	::GetModuleFileName(NULL, szModuleFileName, sizeof(szModuleFileName)/sizeof(TCHAR));
#else

#endif

#ifndef __cplusplus 
	p = strrchr(szModuleFileName, '\\');
	if (p == NULL)
	{
		strAppPath = "";
	}
	else
	{
		npos = p - szModuleFileName;
		memcpy(szFilePath, szModuleFileName, nPos);

		strAppPath = szFilePath;
	}
#else
	strAppPath = szModuleFileName;
	npos = strAppPath.find_last_of("\\");

	strAppPath = strAppPath.substr(0, npos);
#endif

	return strAppPath;
}


bool CDirectory::IsDirExists(const char* pszDirName)
{
	bool bRet = false;

	if (pszFilePath == NULL)
	{
		return false;
	}

#ifdef _WIN_32_
#if 0
	DWORD dwAttributes = GetFileAttributes(lpszFileName);
	if(dwAttributes == 0xFFFFFFFF)
	{
		return false;
	} 

	if((dwAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
	{
		return bIsDirCheck;
	}
	else
	{
		return !bIsDirCheck;
	}
#else
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(pszFilePath, &fd);
	if ((hFind != INVALID_HANDLE_VALUE) && (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) )
	{
		bRet = true;
	}

	FindClose(hFind);
#endif
#else
	if ((_access(pszFilePath, 0)) != -1)
	{
		bRet = true;
	}
	else
	{
		bRet = false;
	}
#endif

	return bRet;
}

bool CDirectory::CreateDirectory(const char* pszDirPath, bool bFlag)
{
	bool bRet = false;

	int npos = 0;
	int nlen = 0;

	char* p = NULL;
	char szDirPath[MAX_PATH] = {0};

	if (pszDirPath == NULL || pszDirPath[1] == '\0')
	{
		return false;
	}

	nlen = strlen(pszDirPath);

#ifdef _WIN_32_
	
	p = strrchr((char*)pszDirPath, '\\');
	if (p == NULL)
	{
		return false;
	}

	npos = p - pszDirPath;
	if (npos == -1)
	{
		return false;
	}

	if (npos+1 == npos)
	{
		memcpy(szDirPath, pszDirPath, npos);
	}
	else
	{
		memcpy(szDirPath, pszDirPath, nlen);
	}

	if (IsDirExists(szDirPath))
	{
		return true;
	}

	SECURITY_ATTRIBUTES sa; 
	sa.nLength=sizeof(SECURITY_ATTRIBUTES); 
	sa.lpSecurityDescriptor=NULL;   
	sa.bInheritHandle=0;

	if (CreateDirectory(szDirPath, &sa))
	{
		bRet = true;
	}
	else
	{
		bRet = false;
	}
#else
#endif
	
	return bRet;
}

bool CDirectory::DeleteDirectory(const char* pszDirPath, bool bFlag)
{
	bool bRet = false;

	int npos = 0;
	int nlen = 0;

	char* p = NULL;
	char szDirPath[MAX_PATH] = {0};

	if (pszDirPath == NULL || pszDirPath[1] == '\0')
	{
		return false;
	}

	nlen = strlen(pszDirPath);

#ifdef _WIN_32_
	p = strrchr((char*)pszDirPath, '\\');
	if (p == NULL)
	{
		return false;
	}

	npos = p - pszDirPath;
	if (npos == -1)
	{
		return false;
	}

	if (npos+1 == npos)
	{
		memcpy(szDirPath, pszDirPath, npos);
	}
	else
	{
		memcpy(szDirPath, pszDirPath, nlen);
	}

	if (!IsDirExists(szDirPath))
	{
		return true;
	}

	if (!DeleteDirectory(szDirPath))
	{
		bRet = false;
	}
	else
	{
		bRet = true;
	}
#else
#endif

	return bRet;
}

bool CDirectory::CopyDirectory(const char* pszSrcDirPath, const char* pszDescDirPath)
{
	bool bRet = false;

	return bRet;
}

bool CDirectory::GetDirSize(const char* pszDirPath, v_uint64_t* pDirSize)
{
	bool bRet = false;

	return bRet;
}

//////////////////////////////////////////////////////////////////////////
//
bool CDirectory::EnumDirectory(const char* pszDirPath, std::list<std::string> &vecDirList, bool bFlag /* = false */)
{
	bool bRet = false;

	return bRet;
}