#include "StdAfx.h"
#include "Driver.h"
#include "Character.h"

using namespace Leaf::Character;
using namespace Leaf::Driver;
CDriver::CDriver(LPCTSTR pszDriverPath, LPCTSTR pszLinkName)
{
#ifdef _UNICODE
	char cstr[256]={0};
	CConvert::UnicodeToANSI(cstr, pszLinkName, wcslen(pszLinkName));
	strncpy(m_szLinkName, cstr, 55);
#else
	strncpy_s(m_szLinkName, pszLinkName, 55);	//strncpy
#endif
	
	m_bStarted = FALSE;
	m_bCreateService = FALSE;
	m_hSCM = m_hService = NULL;
	m_hDriver = NULL;

	// 打开SCM管理器
	m_hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if(m_hSCM == NULL)
	{
		MessageBox(0, _T("打开服务控制管理器失败\n"),
			_T("可能是因为您不拥有Administrator权限\n"), 0);
		return;
	}

    // 创建或打开服务
#ifdef _UNICODE
	wchar_t szLinkName[56] ={0};
	CConvert::AnsiToUnicode(szLinkName, m_szLinkName, strlen(m_szLinkName));
#else
	char    szLinkName[56] ={0};
	strncpy_s(szLinkName, m_szLinkName, 55);	//strncpy
#endif
	
	m_hService = ::CreateService(m_hSCM, szLinkName, szLinkName, SERVICE_ALL_ACCESS,
		SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL,
		pszDriverPath, NULL, 0, NULL, NULL, NULL);

	if(m_hService == NULL)
	{
		// 创建服务失败，可能是因为服务已经存在，所以还要试图打开它
		int nError = ::GetLastError();
		if(nError == ERROR_SERVICE_EXISTS || nError == ERROR_SERVICE_MARKED_FOR_DELETE)
		{
			m_hService = ::OpenService(m_hSCM, szLinkName, SERVICE_ALL_ACCESS);
		}
	}
	else
	{
		m_bCreateService = TRUE;
	}
}

CDriver::~CDriver()
{
	// 关闭设备句柄
	if(m_hDriver != INVALID_HANDLE_VALUE)
		::CloseHandle(m_hDriver);
	// 如果创建了服务，就将之删除
	if(m_bCreateService)
	{
		StopDriver();
		::DeleteService(m_hService);
	}
	// 关闭句柄
	if(m_hService != NULL)
		::CloseServiceHandle(m_hService);
	if(m_hSCM != NULL)
		::CloseServiceHandle(m_hSCM);
}

BOOL CDriver::StartDriver()
{
	if(m_bStarted)
		return TRUE;
	if(m_hService == NULL)
		return FALSE;
	// 启动服务
	if(!::StartService(m_hService, 0, NULL))
	{
		int nError = ::GetLastError();
		if(nError == ERROR_SERVICE_ALREADY_RUNNING)
			m_bStarted = TRUE;
		else
			::DeleteService(m_hService);
	}
	else
	{
		// 启动成功后，等待服务进入运行状态
		int nTry = 0;
		SERVICE_STATUS ss;
		::QueryServiceStatus(m_hService, &ss);
		while(ss.dwCurrentState == SERVICE_START_PENDING && nTry++ < 80)
		{
			::Sleep(50);
			::QueryServiceStatus(m_hService, &ss);
		}
		if(ss.dwCurrentState == SERVICE_RUNNING)
			m_bStarted = TRUE;
	}
	return m_bStarted;
}

BOOL CDriver::StopDriver()
{
	if(!m_bStarted)
		return TRUE;
	if(m_hService == NULL)
		return FALSE;
	// 停止服务
	SERVICE_STATUS ss;
	if(!::ControlService(m_hService, SERVICE_CONTROL_STOP, &ss))
	{
		if(::GetLastError() == ERROR_SERVICE_NOT_ACTIVE)
			m_bStarted = FALSE;
	}
	else
	{
		// 等待服务完全停止运行
		int nTry = 0;
		while(ss.dwCurrentState == SERVICE_STOP_PENDING && nTry++ < 80)
		{
			::Sleep(50);
			::QueryServiceStatus(m_hService, &ss);
		}
		if(ss.dwCurrentState == SERVICE_STOPPED)
			m_bStarted = FALSE;
	}
	return !m_bStarted;
}

BOOL CDriver::OpenDevice()
{
	if(m_hDriver != INVALID_HANDLE_VALUE)
		return TRUE;

	// ""是Win32中定义本地计算机的方法，
	// m_szLinkName是设备对象的符号连接名称，后面章节会详细讨论
#ifdef _UNICODE
	wchar_t sz[256] = {0};
	wsprintf(sz, _T("\\\\.\\%s"), m_szLinkName);
#else
	char sz[256] = {0};
	sprintf_s(sz, "\\\\.\\%s", m_szLinkName);	//sprintf
#endif
	
	// 打开驱动程序所控制设备
	m_hDriver = ::CreateFile(sz,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	return (m_hDriver != INVALID_HANDLE_VALUE);
}

DWORD CDriver::IoControl(DWORD nCode, PVOID pInBuffer,
   DWORD nInCount, PVOID pOutBuffer, DWORD nOutCount)
{
	if(m_hDriver == INVALID_HANDLE_VALUE)
		return -1;
	// 向驱动程序发送控制代码
	DWORD nBytesReturn;
	BOOL bRet = ::DeviceIoControl(m_hDriver, nCode,
		pInBuffer, nInCount, pOutBuffer, nOutCount, &nBytesReturn, NULL);
	if(bRet)
		return nBytesReturn;
	else
		return -1;
}
