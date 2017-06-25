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

	// ��SCM������
	m_hSCM = ::OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if(m_hSCM == NULL)
	{
		MessageBox(0, _T("�򿪷�����ƹ�����ʧ��\n"),
			_T("��������Ϊ����ӵ��AdministratorȨ��\n"), 0);
		return;
	}

    // ������򿪷���
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
		// ��������ʧ�ܣ���������Ϊ�����Ѿ����ڣ����Ի�Ҫ��ͼ����
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
	// �ر��豸���
	if(m_hDriver != INVALID_HANDLE_VALUE)
		::CloseHandle(m_hDriver);
	// ��������˷��񣬾ͽ�֮ɾ��
	if(m_bCreateService)
	{
		StopDriver();
		::DeleteService(m_hService);
	}
	// �رվ��
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
	// ��������
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
		// �����ɹ��󣬵ȴ������������״̬
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
	// ֹͣ����
	SERVICE_STATUS ss;
	if(!::ControlService(m_hService, SERVICE_CONTROL_STOP, &ss))
	{
		if(::GetLastError() == ERROR_SERVICE_NOT_ACTIVE)
			m_bStarted = FALSE;
	}
	else
	{
		// �ȴ�������ȫֹͣ����
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

	// ""��Win32�ж��屾�ؼ�����ķ�����
	// m_szLinkName���豸����ķ����������ƣ������½ڻ���ϸ����
#ifdef _UNICODE
	wchar_t sz[256] = {0};
	wsprintf(sz, _T("\\\\.\\%s"), m_szLinkName);
#else
	char sz[256] = {0};
	sprintf_s(sz, "\\\\.\\%s", m_szLinkName);	//sprintf
#endif
	
	// �����������������豸
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
	// �����������Ϳ��ƴ���
	DWORD nBytesReturn;
	BOOL bRet = ::DeviceIoControl(m_hDriver, nCode,
		pInBuffer, nInCount, pOutBuffer, nOutCount, &nBytesReturn, NULL);
	if(bRet)
		return nBytesReturn;
	else
		return -1;
}
