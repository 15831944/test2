#include "stdafx.h"
#include "SystemUtility.h"

using namespace Leaf::System;
CSystemUtility::CSystemUtility()
{
}

CSystemUtility::~CSystemUtility()
{
}


//////////////////////////////////////////////////////////////////////////
//

BOOL CSystemUtility::EnableDebugPriv(LPCTSTR lpszPrivilegeName,BOOL bEnable)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES tkp;
	HANDLE hProcess = GetCurrentProcess();
	if (OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken))
	{
		if (LookupPrivilegeValue(NULL, lpszPrivilegeName, &tkp.Privileges[0].Luid))  //SE_DEBUG_NAME
		{
			tkp.PrivilegeCount = 1;
			tkp.Privileges[0].Attributes = (bEnable) ? SE_PRIVILEGE_ENABLED : 0;//SE_PRIVILEGE_ENABLED;
			BOOL bREt = AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, 0);
			if (bREt)
			{
				return TRUE;
			}
			CloseHandle(hToken);
		}
	}
	return FALSE;
}