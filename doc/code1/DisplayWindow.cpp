#include "stdafx.h"
#include "DisplayWindow.h"

CDisplayWindow::CDisplayWindow()
{
}

CDisplayWindow::~CDisplayWindow()
{
}

BEGIN_MESSAGE_MAP(CDisplayWindow, CWnd)
	//{{AFX_MSG_MAP(CDisplayWindow)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CANCEL, OnCancel)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
//
BOOL CDisplayWindow::Create(CWnd* pParent, LPCTSTR lpszTitile)
{
	BOOL bRet = FALSE;
	
	LPCTSTR lpszClassName = AfxRegisterWndClass(CS_OWNDC|CS_HREDRAW|CS_VREDRAW,
												::LoadCursor(NULL, IDC_APPSTARTING),
												CBrush(::GetSysColor(COLOR_BTNFACE)));
												
	bRet = CreateEx(WS_EX_DLGMODALFRAME,
					lpszClassName,
					lpszTitile,
					WS_POPUP|WS_BORDER|WS_CAPTION|WS_SYSMENU,
					CW_USEDEFAULT, CW_USEDEFAULT,
					CW_USEDEFAULT, CW_USEDEFAULT,
					pParent->GetSafeHwnd(),
					0,
					NULL);	
	if(!bRet)
	{
		return FALSE;
	}	
	
	SetWindowPos(&wndTop, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
	return bRet;
}

void CDisplayWindow::OnPaint()
{
	CPaintDC dc(this);
}

BOOL CDisplayWindow::OnEraseBkgnd(CDC* pDC)
{
	return CWnd::OnEraseBkgnd(pDC);
}

void CDisplayWindow::OnMouseMove(UINT nFlags, CPoint point)
{
	CWnd::OnMouseMove(nFlags, point);
}

void CDisplayWindow::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDown(nFlags, point);
}

void CDisplayWindow::OnRButtonDown(UINT nFlags, CPoint point)
{
	CWnd::OnRButtonDown(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////
//
void CDisplayWindow::SetWndBorder(BOOL bWndBorder, COLORREF clrWndBorder)
{
	m_bWndBorder = bWndBorder;
	m_clrWndBorder = clrWndBorder;
}

void CDisplayWindow::SetWndBkColor(COLORREF clrWndBk)
{
	m_clrWndBk = clrWndBk;
}

void CDisplayWindow::SetHoverColor(COLORREF clrHoverBorder, COLORREF clrHoverFill)
{
	m_clrHoverBorder = clrHoverBorder;
	m_clrHoverFill = clrHoverFill;
}

void CDisplayWindow::SetSelColor(COLORREF clrSelBorder, COLORREF clrSelFill)
{
	m_clrSelBorder = clrSelBorder;
	m_clrSelFill = clrSelFill;
}

void CDisplayWindow::SetBkBmp(LPCTSTR lpBitmapName)
{
}

void CDisplayWindow::SetBkBmp(UINT nIDBmp)
{
}