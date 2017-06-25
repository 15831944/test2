#include "stdafx.h"
#include "CommonFun.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
 
CCommonFun::CCommonFun()
{
 
}
   
CCommonFun::~CCommonFun()
{

}


//////////////////////////////////////////////////////////////////////////
//
LONGLONG CCommonFun::GetUSTickCount()
{
	BOOL bResult = FALSE;

	LARGE_INTEGER nFreq;
	LARGE_INTEGER nLastTime1;
    LARGE_INTEGER nLastTime2;
	
	//获取时钟频率
	if (QueryPerformanceFrequency(&nFreq))
	{
		const int nBufSize = 256;
		TCHAR chBuf[nBufSize];
		wsprintf(chBuf,_T("LastTime=%I64d/r/n"),nFreq);
		OutputDebugString(chBuf);

		//获取定时器的值
		if (QueryPerformanceFrequency(&nLastTime1))
		{
			wsprintf(chBuf,_T("LastTime=%I64d/r/n"),nLastTime1);
            OutputDebugString(chBuf);
		}
		Sleep(0);

		if (QueryPerformanceFrequency(&nLastTime2))
		{
			wsprintf(chBuf,_T("LastTime=%I64d/r/n"),nLastTime2);
			OutputDebugString(chBuf);
		}

		 float fInterval = nLastTime2.QuadPart - nLastTime1.QuadPart;
		 sprintf_s(chBuf,_T("花费:%f/r/n"),fInterval/(float)nFreq.QuadPart);
         OutputDebugString(chBuf);
	}
	return 0;
}

// 
// void CCommonFun::Test1()
// {
// 	//1: //if (i%2==1)   // if(i&1)			//类同
// 	//2: DO=DO&（OXFFFFFFFF-(1 < <i));      //设置某类型变量的指定位数为0或1 
// 	//3: VC气球提示 
// 	//http://www.codejock.com/products/toolkitpro/
// 	//http://www.vckbase.com/document/viewdoc/?id=498
// }

BOOL CCommonFun::IsAdmin()
{
#define ACCESS_READ 1   
#define ACCESS_WRITE 2

	HANDLE hToken;   
	DWORD dwStatus; 
	DWORD dwAccessMask;   
	DWORD dwAccessDesired;   
	DWORD dwACLSize; 

	DWORD dwStructureSize = sizeof(PRIVILEGE_SET); 
	PACL  pACL = NULL;   
	PSID  psidAdmin = NULL;   
	BOOL  bReturn = FALSE; 

	PRIVILEGE_SET ps;   
	GENERIC_MAPPING GenericMapping;
	PSECURITY_DESCRIPTOR psdAdmin = NULL;   
	SID_IDENTIFIER_AUTHORITY SystemSidAuthority = SECURITY_NT_AUTHORITY;

	 if(!ImpersonateSelf(SecurityImpersonation)) 
	 {
		  goto LeaveIsAdmin;  
	 }

	 if (!OpenThreadToken(GetCurrentThread(), TOKEN_QUERY, FALSE, &hToken)) 
	 {
		 if (GetLastError() != ERROR_NO_TOKEN)   
		 {
			 goto LeaveIsAdmin;
		 }

		 if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
		 {
			 goto LeaveIsAdmin;
		 }

		 if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) 
		 {
			 goto LeaveIsAdmin;
		 }
	 }

	 if (!AllocateAndInitializeSid(&SystemSidAuthority, 2,SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,0, 0, 0, 0, 0, 0, &psidAdmin)) 
	 {
		goto LeaveIsAdmin;
	 }

	 psdAdmin = LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH);
	 if (psdAdmin == NULL)  
	 {
		goto LeaveIsAdmin;
	 }

	 if (!InitializeSecurityDescriptor(psdAdmin,SECURITY_DESCRIPTOR_REVISION)) 
	 {
		goto LeaveIsAdmin;
	 }

	 dwACLSize = sizeof(ACL) + sizeof(ACCESS_ALLOWED_ACE) + GetLengthSid(psidAdmin) - sizeof(DWORD);   

	 pACL = (PACL)LocalAlloc(LPTR, dwACLSize);   
	 if (pACL == NULL)  
	 {
		 goto LeaveIsAdmin;  
	 }

	 if (!InitializeAcl(pACL, dwACLSize, ACL_REVISION2))   
	 {
		 goto LeaveIsAdmin;
	 }

	 dwAccessMask= ACCESS_READ | ACCESS_WRITE;

	 if (!AddAccessAllowedAce(pACL, ACL_REVISION2, dwAccessMask, psidAdmin))   
	 {
		 goto LeaveIsAdmin;   
	 }

	 if (!SetSecurityDescriptorDacl(psdAdmin, TRUE, pACL, FALSE))   
	 {
		 goto LeaveIsAdmin;   
	 }

	 if(!SetSecurityDescriptorGroup(psdAdmin, psidAdmin, FALSE))   
	 {	
		 goto LeaveIsAdmin;   
	 }

	 if(!SetSecurityDescriptorOwner(psdAdmin, psidAdmin, FALSE))   
	 {	
		 goto LeaveIsAdmin;   
	 }

	 if (!IsValidSecurityDescriptor(psdAdmin))   
	 {	
		 goto LeaveIsAdmin;  
	 }

	 dwAccessDesired = ACCESS_READ;   

	 GenericMapping.GenericRead = ACCESS_READ;   
	 GenericMapping.GenericWrite = ACCESS_WRITE;   
	 GenericMapping.GenericExecute = 0;   
	 GenericMapping.GenericAll = ACCESS_READ | ACCESS_WRITE; 

	 if (!AccessCheck(psdAdmin, hToken, dwAccessDesired, &GenericMapping, &ps, &dwStructureSize, &dwStatus, &bReturn))  
	 {
		 goto LeaveIsAdmin; 
	 }

	 if(!RevertToSelf())
	 {
		 bReturn = FALSE; 
	 }

LeaveIsAdmin:
	 if (pACL) LocalFree(pACL);   
	 if (psdAdmin) LocalFree(psdAdmin);   
	 if (psidAdmin) FreeSid(psidAdmin);

	 return bReturn; 
	 /*
		static HMODULE hModule = NULL;
		if( !hModule )
			hModule = LoadLibrary(_T("shell32.dll"));
		 if( !hModule )
			return TRUE;
		typedef BOOL (__stdcall *FunctionIsUserAdmin)();
		FunctionIsUserAdmin pfnIsUserAnAdmin = (FunctionIsUserAdmin)GetProcAddress(hModule, "IsUserAnAdmin");
		if (pfnIsUserAnAdmin)
			 return pfnIsUserAnAdmin();
		 return TRUE;
	 */
}

int CCommonFun::RunAdmin()
{
	return 0;
}

SYSTEMTIME CCommonFun::TimetToSystemTime(time_t t)
{
	FILETIME ft;
	SYSTEMTIME pst;

	LONGLONG nLL = Int32x32To64(t, 10000000) + 116444736000000000;
	ft.dwLowDateTime = (DWORD)nLL;
	ft.dwHighDateTime = (DWORD)(nLL >> 32);
	FileTimeToSystemTime(&ft, &pst);

	return pst;
}

time_t CCommonFun::SystemTimeToTimet(SYSTEMTIME st)
{
	FILETIME ft;
	SystemTimeToFileTime( &st, &ft );

	LONGLONG nLL;
	ULARGE_INTEGER ui;
	ui.LowPart = ft.dwLowDateTime;
	ui.HighPart = ft.dwHighDateTime;
	nLL = (ft.dwHighDateTime << 32) + ft.dwLowDateTime;
	time_t pt = (long)((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);

	return pt;
}

SYSTEMTIME CCommonFun::Time_tToSystemTime(time_t t)
{
	tm temptm = *localtime(&t);

	SYSTEMTIME st = {1900 + temptm.tm_year, 
					1 + temptm.tm_mon, 
					temptm.tm_wday, 
					temptm.tm_mday, 
					temptm.tm_hour, 
					temptm.tm_min, 
					temptm.tm_sec, 
					0};

	return st;
}

time_t CCommonFun::SystemTimeToTime_t( const SYSTEMTIME& st )
{
	tm temptm = {st.wSecond, 
				st.wMinute, 
				st.wHour, 
				st.wDay, 
				st.wMonth - 1, 
				st.wYear - 1900, 
				st.wDayOfWeek, 
				0, 
				0};

	return mktime(&temptm);

}