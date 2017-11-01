#include "stdafx.h"
#include "OutPutWndCtrl.h"

COutPutWndCtrl::COutPutWndCtrl()
{
	m_nCurWndNum	  = -1;
	m_dwWndId		  = -1;
	m_dwHoverRet	  = 0;

	m_bShowing		  = FALSE;
	m_bWndSel		  = FALSE;
	m_bWndHover		  = FALSE;
	m_bWndBorder	  = FALSE;
	m_bWndBkBmp		  = FALSE;
	m_bWndMultiScreen = FALSE;

	m_clrHoverBorder  = RGB(169, 216, 236);
	m_clrHoverFill    = RGB(229, 238, 245);
	m_clrSelBorder    = RGB(169, 216, 236);
	m_clrSelFill	  = RGB(0,   0,   180);
	m_clrWndBorder    = RGB(141, 141, 141);

	m_pBkBmp		  = NULL;
	m_pParentWnd	  = NULL;
}

COutPutWndCtrl::~COutPutWndCtrl()
{
	if (m_pBkBmp)
	{
		delete m_pBkBmp;
		m_pBkBmp = NULL;
	}
}

BEGIN_MESSAGE_MAP(COutPutWndCtrl, CWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()

	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

BOOL COutPutWndCtrl::PreTranslateMessage(MSG* pMsg)
{
	return CWnd::PreTranslateMessage(pMsg);
}

void COutPutWndCtrl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
}

void COutPutWndCtrl::OnPaint()
{
	CPaintDC dc(this); 

	CPen   BorderPen, *pOldPen(NULL);
	CBrush FillBrush, *pOldBrush(NULL);

	CRect rcWnd;
	GetClientRect(&rcWnd);
	rcWnd.DeflateRect(1,1);

	if (m_bWndSel)
	{
		FillBrush.CreateSolidBrush(m_clrSelFill);
		pOldBrush = dc.SelectObject(&FillBrush);

		BorderPen.CreatePen(PS_SOLID, 1, m_clrSelBorder);
		pOldPen = dc.SelectObject(&BorderPen);

		dc.RoundRect(&rcWnd, CPoint(5,5));

		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);

		BorderPen.DeleteObject();
		FillBrush.DeleteObject();
	}

	if (m_bWndHover)
	{
		FillBrush.CreateSolidBrush(m_bWndSel ? m_clrSelFill : m_clrHoverFill);
		pOldBrush = dc.SelectObject(&FillBrush);

		BorderPen.CreatePen(PS_SOLID, 1, m_clrHoverBorder);
		pOldPen = dc.SelectObject(&BorderPen);

		dc.RoundRect(&rcWnd, CPoint(5,5));

		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);

		BorderPen.DeleteObject();
		FillBrush.DeleteObject();
	}
}

BOOL COutPutWndCtrl::OnEraseBkgnd(CDC* pDC)
{
	CPen pen, *pOldPen(NULL);

	CRect rcWnd;
	GetClientRect(&rcWnd);
	rcWnd.DeflateRect(1,1);

	if (m_bWndBorder)
	{
		pen.CreatePen(PS_SOLID, 1, m_clrWndBorder);
		pOldPen = pDC->SelectObject(&pen);

		pDC->Rectangle(&rcWnd);

		pDC->SelectObject(pOldPen);
		pen.DeleteObject();
	}	

	return TRUE;
//	return CWnd::OnEraseBkgnd(pDC);
}

void COutPutWndCtrl::OnShowWindow(BOOL bShow, UINT nStatus)
{
	m_bShowing = bShow;
	CWnd::OnShowWindow(bShow, nStatus);
}

void COutPutWndCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if (m_pParentWnd == NULL)
	{
		return;
	}

	if (!m_bWndMultiScreen)
	{
		m_bWndMultiScreen = TRUE;
		::PostMessage(m_pParentWnd->GetSafeHwnd(), WM_SWITCHMULTI_CTRL, M_FULLSCREEN_CTRL, m_dwChannel);
	}
	else
	{
		m_bWndMultiScreen = FALSE;
		::PostMessage(m_pParentWnd->GetSafeHwnd(), WM_SWITCHMULTI_CTRL, M_MULTISCREEN_CTRL, m_dwChannel);
	}

// 	if (pDlg->GetViewerNums() > 1)
// 	{//多屏状态-->全屏
// 		m_bWndMultiScreen = FALSE;
// 		
// 		m_nCurWndNum = pDlg->GetViewerNums();
// 		::PostMessage(pDlg->GetSafeHwnd(), WM_SWITCHMULTI_CTRL, M_FULLSCREEN_CTRL, m_dwChannel);
// 	}
// 	else
// 	{//全屏状态-->多屏
// 		m_bWndMultiScreen = TRUE;
// 		::PostMessage(pDlg->GetSafeHwnd(), WM_SWITCHMULTI_CTRL, M_MULTISCREEN_CTRL, m_nCurWndNum);
// 	}

	CWnd::OnLButtonDblClk(nFlags, point);
}

void COutPutWndCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rcWnd;
	GetClientRect(&rcWnd);

	if (rcWnd.PtInRect(point))
	{
		if (!m_bWndSel)
		{
			m_bWndSel = TRUE;
			InvalidateRect(&rcWnd);
		}
		else
		{
			m_bWndSel = FALSE;
			InvalidateRect(&rcWnd);
		}
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void COutPutWndCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	CMenu menu;
	CWnd::OnRButtonDown(nFlags, point);
}

void COutPutWndCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rcWnd;
	GetClientRect(&rcWnd);

	if (rcWnd.PtInRect(point))
	{//鼠标移进窗口
		m_dwHoverRet++;					//防止窗口连续闪烁
		SetCapture();

		if (m_dwHoverRet == 1)
		{
			m_bWndHover = TRUE;
			InvalidateRect(&rcWnd);	
		}
		else
		{
			return;
		}
	}
	else
	{//鼠标移出窗口
		m_dwHoverRet=0;
		ReleaseCapture();

		m_bWndHover = FALSE;	
		InvalidateRect(&rcWnd);
	}

	CWnd::OnMouseMove(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////
//public:
BOOL COutPutWndCtrl::Create(DWORD dwStyle, const CRect &pWndRect, CWnd* pParent, UINT nWndId)
{
	if (!CWnd::CreateEx(NULL, NULL, NULL, dwStyle, pWndRect, pParent, nWndId))
	{
		return FALSE;
	}

	m_dwWndId = nWndId;
	m_pParentWnd = pParent;
	return TRUE;
}

void COutPutWndCtrl::SetWndChannel(DWORD dwChannel)
{
	m_dwChannel = dwChannel;
}

DWORD COutPutWndCtrl::GetWndChannel()
{
	return m_dwChannel;
}

void COutPutWndCtrl::SetMultiScreen(BOOL bFlag)
{
}

void COutPutWndCtrl::SetWndBorder(BOOL bWndBorder, COLORREF clrWndBorder)
{
	m_bWndBorder = bWndBorder;
	m_clrWndBorder = clrWndBorder;
}

void COutPutWndCtrl::SetWndBkColor(COLORREF clrWndBk)
{
	m_clrWndBk = clrWndBk;
}

void COutPutWndCtrl::SetHoverColor(COLORREF clrHoverBorder, COLORREF clrHoverFill)
{
	m_clrHoverBorder = clrHoverBorder;
	m_clrHoverFill = clrHoverFill;
}

void COutPutWndCtrl::SetSelColor(COLORREF clrSelBorder, COLORREF clrSelFill)
{
	m_clrSelBorder = clrSelBorder;
	m_clrSelFill = clrSelFill;
}

void COutPutWndCtrl::SetBkBmp(LPCTSTR lpBitmapName)
{
	HBITMAP hBitmap = (HBITMAP)::LoadImage(NULL,
										   lpBitmapName,
										   IMAGE_BITMAP,
										   0,
										   0,
										   LR_LOADFROMFILE);

	m_pBkBmp = CBitmap::FromHandle(hBitmap);
	m_bWndBkBmp = TRUE;
}

void COutPutWndCtrl::SetBkBmp(UINT nIDBmp)
{
	m_pBkBmp->LoadBitmap(nIDBmp);
	m_bWndBkBmp = TRUE;
}