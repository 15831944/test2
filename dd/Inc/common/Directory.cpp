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

bool CDirectory::IsDirectory(const char* pszFilePath)
{
	bool bRet = false;

	if (pszFilePath == NULL)
	{
		return false;
	}

#ifdef _WIN_32_
	DWORD dwState;
	dwState = GetFileAttributes(pszFilePath);
	if (dwState == INVALID_FILE_ATTRIBUTES )
	{
		return false;
	}

	if (dwState&FILE_ATTRIBUTE_DIRECTORY)
	{
		bRet = true;
	}
	else
	{
		bRet = false;
	}
#else
	struct stat S_stat;
	if (lstat(pszFilePath, &S_stat) < 0) 
	{
		return false;
	}

	if (S_ISDIR(S_stat.st_mode))
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

bool CDirectory::IsDirExists(const char* pszFilePath)
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

#ifdef _WIN_32_
	HANDLE  hFindFile;
	WIN32_FIND_DATA fd;

	char szFindPath[MAX_PATH] = {0};

	hFindFile = FindFirstFile(szFindPath, &fd);
	if (hFindFile == NULL || hFindFile == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	do 
	{
		if (strcmp(fd.cFileName, _T(".")) == 0 || strcmp(fd.cFileName, _T("..")) == 0)
		{
			continue;
		}

		if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			if (!bFlag)
			{
			}
			else
			{

			}
		}
		else
		{

		}
	} while (FindNextFile(hFindFile, &fd));

	if (hFindFile)
	{
		FindClose(hFindFile);
		hFindFile = NULL;
	}
#else
#endif

	return bRet;
}

/*
bool CDirectory::ParseDirPath1(const char* pszDirPath, DIR_STRUCT* pDirList)
{
	bool bRet = false;
	v_uint32_t uIndex = 0;

	std::string strfield;
	std::list<std::string> vecPartList;
	std::list<std::string>::iterator iterPartList;

	DIR_STRUCT *pPrevDir = NULL;
	DIR_STRUCT *pNextDir = NULL;

	if (pszDirPath == NULL)
	{
		return false;
	}

	if (!ParseDirPath2(pszDirPath, vecPartList))
	{
		return false;
	}

	if (vecPartList.size() == 0)
	{
		return false;
	}
	else
	{
#ifndef _WIN_32_
		DIR_STRUCT* pDirStruct = new DIR_STRUCT;
		if (pDirStruct == NULL)
		{
			return false;
		}
		memset(pDirStruct, 0x0, sizeof(DIR_STRUCT));

		strcpy(pDirStruct->szDirName, "root");
		strcpy(pDirStruct->szDirPath, "/");

		pDirStruct->uIndex = 0;

		pDirStruct->prev = NULL;
		pDirStruct->next = NULL;
#endif
	}

	iterPartList = vecPartList.begin();
	for (iterPartList; iterPartList != vecPartList.end(); iterPartList++, uIndex++)
	{
		strfield = *iterPartList;

		DIR_STRUCT* pDirStruct = new DIR_STRUCT;
		if (pDirStruct == NULL)
		{
			continue;
		}
		memset(pDirStruct, 0x0, sizeof(DIR_STRUCT));

#ifdef _WIN_32_
		if (uIndex == 0)
		{
			strcpy(pDirStruct->szDirName, strfield.c_str());
			strfield += "\\";
			strcpy(pDirStruct->szDirPath, strfield.c_str());

			pDirStruct->uIndex = uIndex;

			pDirStruct->prev = NULL;
			pDirStruct->next = NULL;

			pDirList->prev = pDirStruct;

		}
#endif
	}
}
*/
bool CDirectory::ParseDirPath2(const char* pszDirPath, std::list<std::string> &vecPartList)
{
	bool bRet = false;

	int nlen = 0;
	int npos = 0;

	char* p = NULL;
	string strString;
	char szPath[0x20] = {0};

#ifdef _WIN_32_
	char* pszChar = _T("\\");
#else
	char* pszChar = _T("/");
#endif

	char* pSrcDirPath = (char*)pszDirPath;
	if (pSrcDirPath == NULL)
	{
		return false;
	}

	nlen = strlen(pSrcDirPath);
	if (nlen <= 0)
	{
		return false;
	}

	while(nlen > 0)
	{
		strString = "";
		memset(szPath, 0x0, 0x20);

		p = strstr(pSrcDirPath, pszChar);
		if (p == NULL)
		{
			strString = pSrcDirPath;
			vecPartList.push_back(strString);
			break;
		}

		npos = p - pSrcDirPath;
		if (npos == -1)
		{
			continue;
		}

		memcpy(szPath, pSrcDirPath, npos);

		strString = szPath;
		vecPartList.push_back(strString);

		nlen = nlen - (npos+1);
		pSrcDirPath  = pSrcDirPath + (npos+1);
	}

	return true;
}