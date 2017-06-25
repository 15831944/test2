///////////////////////////////////////////////////
// Driver.h�ļ�

#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <Winsvc.h> // Ϊ��ʹ��SCM����

namespace Leaf
{
	namespace Driver
	{
		
		class CDriver
		{
		public:
			// ���캯������������
			// ���캯����pszDriverPathΪ��������Ŀ¼��pszLinkNameΪ������������
			// ����Ĺ��캯���У�����ͼ������򿪷���
			CDriver(LPCTSTR pszDriverPath, LPCTSTR pszLinkName);
			// �����������������ֹͣ����
			virtual ~CDriver();
			
			// ����
			// �������Ƿ����
			virtual BOOL IsValid() { return (m_hSCM != NULL && m_hService != NULL); }
			
			// ����
			// ��������Ҳ����˵������DriverEntry������������
			virtual BOOL StartDriver();
			// �������񡣼����������DriverUnload���̽�������
			virtual BOOL StopDriver();
			
			// ���豸����ȡ�õ���������һ�����
			virtual BOOL OpenDevice();
			
			// ���豸���Ϳ��ƴ���
			virtual DWORD IoControl(DWORD nCode, PVOID pInBuffer,
				DWORD nInCount, PVOID pOutBuffer, DWORD nOutCount);
			// ʵ��
		protected:
			char m_szLinkName[56]; // ������������
			
			BOOL m_bStarted; // ָ�������Ƿ�����
			BOOL m_bCreateService; // ָ���Ƿ񴴽��˷���
			
			SC_HANDLE m_hSCM;   // SCM���ݿ���
			SC_HANDLE m_hService; // ������
			HANDLE m_hDriver; // �豸���
		};
	}
}


#endif // __DRIVER_H__