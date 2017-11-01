#include "stdafx.h"
#include "../dd.h"
#include "DlgPreViewCtrl.h"

IMPLEMENT_DYNAMIC(CDlgPreViewCtrl, CDialog)
CDlgPreViewCtrl::CDlgPreViewCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPreViewCtrl::IDD, pParent)
{
	m_dwOutPutSize      = 16;
	m_dwOutPutWndIndex  = 0;

	m_nCurScreenWidth   = GetSystemMetrics(SM_CXSCREEN);
	m_nCurScreenHeight  = GetSystemMetrics(SM_CYSCREEN);
}

CDlgPreViewCtrl::~CDlgPreViewCtrl()
{
}

void CDlgPreViewCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDlgPreViewCtrl, CDialog)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_SWITCHMULTI_CTRL,		OnSwitchMultiWnd)
END_MESSAGE_MAP()

BOOL CDlgPreViewCtrl::OnInitDialog()
{
	CDialog::OnInitDialog();

	if (!Init())
	{
		return FALSE;
	}

	return TRUE; 
}

int CDlgPreViewCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	DWORD dwIndex = 0;
	DWORD dwStyle = 0;

	CRect rcClient;
	GetClientRect(&rcClient);

	if (CDialog::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	m_pOutPutArray = new COutPutWndCtrl[m_dwOutPutSize];
	if (m_pOutPutArray == NULL)
	{
		return -1;
	}

	dwStyle = WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_VISIBLE;
	for (dwIndex=0; dwIndex<m_dwOutPutSize; dwIndex++)
	{
		if (!m_pOutPutArray[dwIndex].Create(dwStyle, rcClient, this, dwIndex+1))
		{
			continue;
		}
		
		m_pOutPutArray[dwIndex].SetWndChannel(dwIndex+1);

		m_pOutPutArray[dwIndex].SetWndBorder(TRUE, RGB(10,160,200));
		m_pOutPutArray[dwIndex].SetHoverColor(RGB(255, 0, 0), RGB(255,255,255));
	}

	m_rcPreviewBG.CopyRect(rcClient);
	return 0;
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
	ArrangeOutputs(M_MULTISCREEN_CTRL, m_dwOutPutSize);
	return TRUE;
}

BOOL CDlgPreViewCtrl::InitInfo()
{
	return TRUE;
}

LRESULT CDlgPreViewCtrl::OnSwitchMultiWnd(WPARAM wParam, LPARAM lParam)
{
	DWORD dwCurChannel = 0;
	UKH_WND_TYPE hWndType = M_EMPTYTYPE;

	switch(wParam)
	{
	case M_FULLSCREEN_CTRL:
		{
			dwCurChannel = lParam;
			hWndType = M_FULLSCREEN_CTRL;
		}
		break;
	case M_MULTISCREEN_CTRL:
		{
			dwCurChannel = m_dwOutPutSize;
			hWndType = M_MULTISCREEN_CTRL;
		}
		break;
	}

	ArrangeOutputs(hWndType, dwCurChannel);
	return 0;
}

BOOL CDlgPreViewCtrl::ArrangeOutputs(UKH_WND_TYPE hWndType, DWORD dwChannels)
{
	int nWidth   = 0;
	int nHeight  = 0;
	int nSqrtNum = 0;
	int nPlayIndex = 0;

	DWORD dwIndex = 0;
	DWORD dwWndChannel = 0;

	if (m_pOutPutArray == NULL)
	{
		return FALSE;
	}

	if (hWndType == M_EMPTYTYPE)
	{
		return FALSE;
	}

	if (dwChannels == 0)
	{
		return FALSE;
	}

	for (dwIndex=0; dwIndex<m_dwOutPutSize; dwIndex++)
	{
		m_pOutPutArray[dwIndex].ShowWindow(SW_HIDE);
	}

	if (hWndType == M_MULTISCREEN_CTRL)
	{
		nSqrtNum = (int)sqrt((double)dwChannels);

		nWidth  = (m_rcPreviewBG.Width() - OUTPUT_INTERVAL*(nSqrtNum-1))/nSqrtNum;
		nHeight = (m_rcPreviewBG.Height() - OUTPUT_INTERVAL*(nSqrtNum-1))/nSqrtNum;

		for(dwIndex=0; dwIndex<m_dwOutPutSize; dwIndex++)
		{
			dwWndChannel = m_pOutPutArray[dwIndex].GetWndChannel();
			if (dwWndChannel == 0)
			{
				continue;
			}

			nPlayIndex = dwWndChannel -1;
			m_pOutPutArray[nPlayIndex].MoveWindow((dwIndex%nSqrtNum)*(nWidth+OUTPUT_INTERVAL), (dwIndex/nSqrtNum)*(nHeight+OUTPUT_INTERVAL), nWidth, nHeight, TRUE);
			m_pOutPutArray[nPlayIndex].ShowWindow(SW_SHOW);
		}
	}
	else
	{
		nSqrtNum = 1;

		nWidth  = m_rcPreviewBG.Width();
		nHeight = m_rcPreviewBG.Height();

		for(dwIndex=0; dwIndex<m_dwOutPutSize; dwIndex++)
		{
			dwWndChannel = m_pOutPutArray[dwIndex].GetWndChannel();
			if (dwWndChannel == 0)
			{
				continue;
			}

			nPlayIndex = dwWndChannel -1;
			if (dwChannels == dwWndChannel)
			{
				m_pOutPutArray[nPlayIndex].MoveWindow(m_rcPreviewBG.left, m_rcPreviewBG.top, nWidth, nHeight, TRUE);
				m_pOutPutArray[nPlayIndex].ShowWindow(SW_SHOW);
				break;
			}
		}
	}

	return TRUE;
}
