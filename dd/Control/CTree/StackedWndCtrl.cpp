#include "stdafx.h"
#include "StackedWndCtrl.h"

CStackedWndCtrl::CStackedWndCtrl()
{
}

CStackedWndCtrl::~CStackedWndCtrl()
{
}

BEGIN_MESSAGE_MAP(CStackedWndCtrl, CStatic)
	//{{AFX_MSG_MAP(CStackedWndCtrl)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CStackedWndCtrl::PreSubclassWindow() 
{
	CStatic::PreSubclassWindow();
}

void CStackedWndCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
}

BOOL CStackedWndCtrl::AddPane(CWnd* pWndItem, CWnd* pParentWnd)
{
	if(pWndItem == NULL)
	{
		return FALSE;
	}
	
	if(pParentWnd == NULL)
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL CStackedWndCtrl::ShowPane()
{
	return TRUE;
}