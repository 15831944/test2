#include "stdafx.h"
#include "../dd.h"
#include "Page2.h"

#include "../Dialog/Dlgcalendarctrl.h"
#include "../Dialog/DlgCompassCtrl.h"
#include "../Dialog/DlgPreViewCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPage2::CPage2(CWnd* pParent /*=NULL*/)
	: CPage(CPage2::IDD, pParent)
{

}

CPage2::~CPage2()
{
}

void CPage2::DoDataExchange(CDataExchange* pDX)
{
	CPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPage2, CPage)
	ON_WM_TIMER()
	ON_WM_ACTIVATE()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnButton6)
	ON_BN_CLICKED(IDC_BUTTON8, OnButton8)
	ON_BN_CLICKED(IDC_BUTTON7, OnButton7)
	ON_BN_CLICKED(IDC_BUTTON9, OnButton9)
	ON_BN_CLICKED(IDC_BUTTON10, OnButton10)
	ON_BN_CLICKED(IDC_BUTTON11, OnButton11)
	ON_BN_CLICKED(IDC_BUTTON12, OnButton12)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// 
BOOL CPage2::OnInitDialog() 
{
	CDialog::OnInitDialog();
	return TRUE; 
}

void CPage2::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CPage::OnActivate(nState, pWndOther, bMinimized);
}

void CPage2::OnTimer(UINT nIDEvent) 
{
	CPage::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////
//
void CPage2::OnButton1() 
{
	CString str1 = "test1";
	CString str2 = "test2";
	str2 = str2;

	//1
// 	AString s1;
// 	AString s2('a');
// 	AString s3(str1.GetBuffer(0), str1.GetLength());
// 	AString s4(str2.GetBuffer(0), true);
// 	AString s5(s4);

	//2
	AString s1("test1");
 	AString s2("test2");
	AString s3("test3");

	AString s4;
	s4 += "abc";
}

//��Ƥ�����
void CPage2::OnButton2() 
{
}

void CPage2::OnButton3() 
{
}

void CPage2::OnButton4() 
{
}

void CPage2::OnButton5() 
{
}

//��������
void CPage2::OnButton6() 
{
}

//���̲���
void CPage2::OnButton7() 
{
	CDlgCompassCtrl dlg;
	dlg.DoModal();
}

void CPage2::OnButton8() 
{
}

void CPage2::OnButton9() 
{
}

void CPage2::OnButton10() 
{	
}

//��������
void CPage2::OnButton11() 
{
	CDlgCalendarCtrl dlg;
	dlg.DoModal();
}

/*
#if 0
#include <setupapi.h>
#include <cfgmgr32.h>   

#pragma comment(lib,"setupapi.lib")

void EnumNetCards()
{
	DWORD dwDevIndex=0;
	DWORD nSize =0,Status =0, Problem=0;
	HDEVINFO hDevInfoSet = NULL;					// �豸��Ϣ���
	SP_DEVINFO_DATA sDevInfoData;					// �豸��Ϣ�ṹ��
	char szDIS[MAX_PATH]={0};						// �豸ID
	//����ϵͳ��Ӳ����
	hDevInfoSet = SetupDiGetClassDevsA(NULL,
									   NULL,
									   NULL,
									   DIGCF_PRESENT|DIGCF_ALLCLASSES);
	if (hDevInfoSet != NULL)
	{
		//ö��Ӳ���������Ҫ�Ľӿ�
		sDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
		for(dwDevIndex=0; SetupDiEnumDeviceInfo(hDevInfoSet,dwDevIndex,&sDevInfoData); dwDevIndex++)
		{
			//��ȡÿ���豸��ʵ��ID
// 			if (SetupDiGetDeviceInstanceIdA(hDevInfoSet, &sDevInfoData, szDIS, sizeof(szDIS), &nSize))
// 			{
// 			}
			if (CM_Get_DevNode_Status(&Status, &Problem, sDevInfoData.DevInst, 0) != CR_SUCCESS)
			{ 
// 				if (GetRegistryProperty())
// 				{
// 				}
			}
		}
	}
}
#endif
*/

//����ͷ����
void CPage2::OnButton12() 
{
 	CDlgPreViewCtrl dlg;
 	dlg.DoModal();
}

//����̨����
void CPage2::OnButton13() 
{ 
/*            
	freopen("CONIN$",  "r+t", stdin );		// �����
	freopen("CONOUT$", "w+t", stdout );		// ����д
	freopen("CONOUT$", "w+t", stderr); 
	printf("Hello World��\r\n");			// д����
//	char ch = getchar();					// ������

	

	fclose(stderr);   
	fclose(stdout);   
    fclose(stdin);
	FreeConsole();                         // �ͷſ���̨��Դ
*/
	BOOL bRet = FALSE;
	static CConsole	Console;
	static BOOL bStatus = FALSE;

	if (!bStatus)
	{
		bRet = Console.Create("Test", TRUE);
		if (!bRet)
		{
			return;
		}

		bRet = Console.SetTitle("Debug Output");
		if (!bRet)
		{
			return;
		}

		bRet = Console.SetTextColor(0x05);
		if (!bRet)
		{
			return;
		}

		Console.ShowConsoleWnd(TRUE);

		Console.Write(_T("this is a test!"), -1);

		bStatus = TRUE;
	}
	else
	{
		Console.Clear();
		Console.Close();

		bStatus = FALSE;
	}	
}