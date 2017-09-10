#include "stdafx.h"
#include "ScrollWndMsg.h"

CScrollWndMsg::CScrollWndMsg()
{
}

CScrollWndMsg::~CScrollWndMsg()
{
}

//////////////////////////////////////////////////////////////////////////
//
BEGIN_MESSAGE_MAP(CScrollWndMsg, CWnd)
	//{{AFX_MSG_MAP(CScrollWndMsg)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CScrollWndMsg::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;	
//	return CWnd::OnEraseBkgnd(pDC);
}

void CScrollWndMsg::OnPaint() 
{
	CPaintDC dc(this); 
}

void CScrollWndMsg::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd::OnMouseMove(nFlags, point);
}
//////////////////////////////////////////////////////////////////////////
//
BOOL CScrollWndMsg::Create(DWORD dwStyle, const CRect &pWndRect, CWnd* pParent, UINT nWndId)
{
	if (pParent->GetSafeHwnd() == NULL)
	{
		return FALSE;
	}

	if (!CWnd::Create(_T("SCROLL_CLASS_NAME"), NULL, dwStyle, pWndRect, pParent, nWndId))
	{
		return FALSE;
	}

	return TRUE;
}

void CScrollWndMsg::SetFont(int nSize, LPCTSTR lpszFaceName)
{
}

void CScrollWndMsg::SetWndText(LPCTSTR lpszWndText, COLORREF color)
{
}

void CScrollWndMsg::SetWndTipText(LPCTSTR lpszWndTipText, COLORREF color)
{
}

void CScrollWndMsg::SetWndBorder(BOOL bWndBorder, COLORREF color)
{
}

void CScrollWndMsg::SetWndBkColor(COLORREF color)
{
}

void CScrollWndMsg::SetTextColor(COLORREF crNormalText, COLORREF crSelText)
{
}

void CScrollWndMsg::SetSelColor(COLORREF crSelBorder, COLORREF crSelFill)
{
}

void CScrollWndMsg::SetHoverColor(COLORREF crHoverBorder, COLORREF crHoverFill)
{
}

void CScrollWndMsg::SetScrollPause()
{
}

void CScrollWndMsg::SetScrollSpeed(DWORD dwSpan)
{
}

void CScrollWndMsg::SetScrollShowPos(DWORD dx, DWORD dy)
{
}

void CScrollWndMsg::ClearScrollText()
{
}