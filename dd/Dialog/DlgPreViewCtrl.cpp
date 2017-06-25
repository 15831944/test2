#include "stdafx.h"
#include "../dd.h"
#include "DlgPreViewCtrl.h"


IMPLEMENT_DYNAMIC(CDlgPreViewCtrl, CDialog)
CDlgPreViewCtrl::CDlgPreViewCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreViewCtrl::IDD, pParent)
{
	m_iCurScreenWidth  = -1;
	m_iCurScreenHeight = -1;

	m_iCurWndNum   = 4;
	m_iCurWndIndex = 0;
}

CDlgPreViewCtrl::~CDlgPreViewCtrl()
{
}

void CDlgPreViewCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPreViewCtrl, CDialog)
	ON_MESSAGE(WM_SWITCHMULTI_CTRL,		OnSwitchMultiWnd)
END_MESSAGE_MAP()

BOOL CDlgPreViewCtrl::OnInitDialog()
{
	CDialog::OnInitDialog();

	Init();
	return TRUE; 
}


void CDlgPreViewCtrl::Init()
{
	InitCtrl();
	InitInfo();
}

void CDlgPreViewCtrl::InitCtrl()
{
	int i = 0;

	m_iCurScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
	m_iCurScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	for (i=0; i<MAX_OUTPUTS_CTRL; i++)
	{
		m_dlgOutPut[i].SetWndChannel(i);
		m_dlgOutPut[i].Create(IDD_DIG_OUTPUT, this);
		m_dlgOutPut[i].SetWndBorder(TRUE, RGB(10,160,200));
		m_dlgOutPut[i].SetHoverColor(RGB(255, 0, 0), RGB(255,255,255));
	}

	GetClientRect(&m_rectPreviewBG);

	ArrangeOutputs(m_iCurWndNum);
}

void CDlgPreViewCtrl::InitInfo()
{
	
}


LRESULT CDlgPreViewCtrl::OnSwitchMultiWnd(WPARAM wParam, LPARAM lParam)
{
	m_iCurWndNum = lParam;

	ArrangeOutputs(m_iCurWndNum);
	return 0;
}


void CDlgPreViewCtrl::ArrangeOutputs(int iNumber)
{
	int i = 0;
	int iPlayIndex = 0;

	int iSqrtNum = 0;
	int iWidth   = 0;
	int iHeight  = 0;

	if (iNumber == 0)
	{
		return;
	}

	iSqrtNum = (int)sqrt((double)iNumber);
	for (i=0; i<MAX_OUTPUTS_CTRL; i++)
	{
		m_dlgOutPut[i].ShowWindow(SW_HIDE);
	}

	if (0)
	{
		iWidth = (m_iCurScreenWidth - OUTPUT_INTERVAL*(iSqrtNum-1))/iSqrtNum;
		iHeight = (m_iCurScreenHeight - OUTPUT_INTERVAL*(iSqrtNum-1))/iSqrtNum;

		for(i=0; i<iNumber; i++)
		{
			m_dlgOutPut[i].MoveWindow((i%iSqrtNum)*(iWidth+OUTPUT_INTERVAL), (i/iSqrtNum)*(iHeight+OUTPUT_INTERVAL), iWidth, iHeight, TRUE);
			m_dlgOutPut[i].ShowWindow(SW_SHOW);
		}
	}
	else
	{
		iWidth = (m_rectPreviewBG.Width() - OUTPUT_INTERVAL*(iSqrtNum-1))/iSqrtNum;
		iHeight = (m_rectPreviewBG.Height() - OUTPUT_INTERVAL*(iSqrtNum-1))/iSqrtNum;

		for(i=0; i<iNumber; i++)
		{
			if (0)
			{
				iPlayIndex = m_iCurWndIndex;
			}
			else
			{
				iPlayIndex = i;
			}
			
			m_dlgOutPut[iPlayIndex].MoveWindow((i%iSqrtNum)*(iWidth+OUTPUT_INTERVAL), (i/iSqrtNum)*(iHeight+OUTPUT_INTERVAL), iWidth, iHeight, TRUE);
			m_dlgOutPut[iPlayIndex].ShowWindow(SW_SHOW);
		}
	}
	
}
