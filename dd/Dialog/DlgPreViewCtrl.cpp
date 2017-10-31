#include "stdafx.h"
#include "../dd.h"
#include "DlgPreViewCtrl.h"

IMPLEMENT_DYNAMIC(CDlgPreViewCtrl, CDialog)
CDlgPreViewCtrl::CDlgPreViewCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreViewCtrl::IDD, pParent)
{
	m_nCurWndNum   = 0;
	m_nCurWndIndex = 0;

	m_nCurScreenWidth  = -1;
	m_nCurScreenHeight = -1;
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
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL CDlgPreViewCtrl::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!Init())
	{
		return FALSE;
	}

	//ModifyStyle(0, WS_CLIPCHILDREN);
	return TRUE; 
}

BOOL CDlgPreViewCtrl::Init()
{
	if (!InitCtrl())
	{
		return FALSE;
	}
	
	if (!InitInfo())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDlgPreViewCtrl::InitCtrl()
{
	int nIndex = 0;
	DWORD dwStyle = 0;
	DWORD dwWndId = 0;

	CRect rcOutput;
	CRect rcClient;
	GetClientRect(&rcClient);

	m_nCurScreenWidth  = GetSystemMetrics(SM_CXSCREEN);
	m_nCurScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	rcOutput.CopyRect(&rcClient);
	dwStyle = WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE;

	for (nIndex=0; nIndex<MAX_OUTPUTS_CTRL; nIndex++)
	{
		if (!m_dlgOutPut[nIndex].Create(dwStyle, rcOutput, this, nIndex+1))
		{
			continue;
		}

		m_dlgOutPut[nIndex].SetWndChannel(nIndex+1);
		m_dlgOutPut[nIndex].SetWndBorder(TRUE, RGB(10,160,200));
		m_dlgOutPut[nIndex].SetHoverColor(RGB(255, 0, 0), RGB(255,255,255));
	}

	m_nCurWndNum = 32;
	GetClientRect(&m_rcPreviewBG);
	ArrangeOutputs(m_nCurWndNum);
	return TRUE;
}

BOOL CDlgPreViewCtrl::InitInfo()
{
	return TRUE;
}

LRESULT CDlgPreViewCtrl::OnSwitchMultiWnd(WPARAM wParam, LPARAM lParam)
{
	DWORD dwCurChannel = 0;

	switch(wParam)
	{
	case M_FULLSCREEN_CTRL:
		{
			dwCurChannel = lParam;
		}
		break;
	case M_MULTISCREEN_CTRL:
		{
			dwCurChannel = lParam;
		}
		break;
	}

	//ArrangeOutputs(m_nCurWndNum);
	return 0;
}

void CDlgPreViewCtrl::ArrangeOutputs(int nNumber)
{
	int nIndex = 0;
	int nPlayIndex = 0;

	int nWidth   = 0;
	int nHeight  = 0;
	int nSqrtNum = 0;

	if (nNumber == 0)
	{
		return;
	}

	nSqrtNum = (int)sqrt((double)nNumber);
	for (nIndex=0; nIndex<MAX_OUTPUTS_CTRL; nIndex++)
	{
		m_dlgOutPut[nIndex].ShowWindow(SW_HIDE);
	}

	if (0)
	{
		nWidth = (m_nCurScreenWidth - OUTPUT_INTERVAL*(nSqrtNum-1))/nSqrtNum;
		nHeight = (m_nCurScreenHeight - OUTPUT_INTERVAL*(nSqrtNum-1))/nSqrtNum;

		for(nIndex=0; nIndex<nNumber; nIndex++)
		{
			m_dlgOutPut[nIndex].MoveWindow((nIndex%nSqrtNum)*(nWidth+OUTPUT_INTERVAL), (nIndex/nSqrtNum)*(nHeight+OUTPUT_INTERVAL), nWidth, nHeight, TRUE);
			m_dlgOutPut[nIndex].ShowWindow(SW_SHOW);
		}
	}
	else
	{
		nWidth = (m_rcPreviewBG.Width() - OUTPUT_INTERVAL*(nSqrtNum-1))/nSqrtNum;
		nHeight = (m_rcPreviewBG.Height() - OUTPUT_INTERVAL*(nSqrtNum-1))/nSqrtNum;

		for(nIndex=0; nIndex<nNumber; nIndex++)
		{
			if (0)
			{
				nPlayIndex = m_nCurWndIndex;
			}
			else
			{
				nPlayIndex = nIndex;
			}
			
			m_dlgOutPut[nPlayIndex].MoveWindow((nIndex%nSqrtNum)*(nWidth+OUTPUT_INTERVAL), (nIndex/nSqrtNum)*(nHeight+OUTPUT_INTERVAL), nWidth, nHeight, TRUE);
			m_dlgOutPut[nPlayIndex].ShowWindow(SW_SHOW);
		}
	}
}
