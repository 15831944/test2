#include "stdafx.h"
#include "ToolbarWndCtrl.h"

CToolbarWndCtrl::CToolbarWndCtrl()
{
}

CToolbarWndCtrl::~CToolbarWndCtrl()
{
}

BEGIN_MESSAGE_MAP(CToolbarWndCtrl, CWnd)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_SHOWWINDOW()

	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

BOOL CToolbarWndCtrl::PreTranslateMessage(MSG* pMsg)
{
	return CWnd::PreTranslateMessage(pMsg);
}

void CToolbarWndCtrl::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
}

void CToolbarWndCtrl::OnPaint()
{
	CPaintDC dc(this); 
}

BOOL CToolbarWndCtrl::OnEraseBkgnd(CDC* pDC)
{
	CRect rcWnd;
	GetClientRect(&rcWnd);
	rcWnd.DeflateRect(0, 1, 5, 6);

	if (m_bWndBorder)
	{
		CPen pen, *pOldPen(NULL);

		pen.CreatePen(PS_SOLID, 1, m_clrWndBorder);
		pOldPen = pDC->SelectObject(&pen);

		pDC->Rectangle(&rcWnd);

		pDC->SelectObject(pOldPen);
		pen.DeleteObject();
	}

	if (m_bBkBitmap && m_pBkBitmap != NULL)
	{
		CDC MemDC;
		MemDC.CreateCompatibleDC(pDC);

		CBitmap bitmap;
		CBitmap *pOldBitmap = m_pBkBitmap;

		BITMAP bmp;
		pOldBitmap->GetBitmap(&bmp);

		pDC->StretchBlt(rcWnd.left, rcWnd.top, rcWnd.Width(), rcWnd.Height(), &MemDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

		if (MemDC.GetSafeHdc())
		{
			MemDC.SelectObject(pOldBitmap);
			MemDC.DeleteDC();
		}
	}
	else
	{
		CBrush BkBrush, *pOldBrush(NULL);
		BkBrush.CreateSolidBrush(m_clrWndBk);

		pOldBrush = pDC->SelectObject(&BkBrush);
		pDC->PatBlt(rcWnd.left, rcWnd.top, rcWnd.Width(), rcWnd.Height(), PATCOPY);

		pDC->SelectObject(pOldBrush);
		BkBrush.DeleteObject();
	}

	return TRUE;
}

void CToolbarWndCtrl::OnShowWindow(BOOL bShow, UINT nStatus)
{
}

void CToolbarWndCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
}

void CToolbarWndCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
}

void CToolbarWndCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
}

void CToolbarWndCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
}

//////////////////////////////////////////////////////////////////////////
//
BOOL CToolbarWndCtrl::Create(DWORD dwStyle, const CRect &pWndRect, CWnd* pParent, UINT nWndId)
{
	if (!CWnd::CreateEx(NULL, NULL, NULL, dwStyle, pWndRect, pParent, nWndId))
	{
		return FALSE;
	}

	return TRUE;
}

void CToolbarWndCtrl::SetWndBkColor(COLORREF color)
{
	m_clrWndBk =  color;
}

void CToolbarWndCtrl::SetWndBkBitmap(UINT nIDBitmap)
{
	m_pBkBitmap->LoadBitmap(nIDBitmap);
	m_bBkBitmap = TRUE;
}

void CToolbarWndCtrl::SetWndBkBitmap(LPCTSTR lpBitmapName)
{
	HBITMAP hBitmap = (HBITMAP)::LoadImage(NULL,
		lpBitmapName,
		IMAGE_BITMAP,
		0,
		0,
		LR_LOADFROMFILE);

	m_pBkBitmap = CBitmap::FromHandle(hBitmap);	
	m_bBkBitmap = TRUE;
}

void CToolbarWndCtrl::SetWndBorder(BOOL bWndBorder, COLORREF color)
{
	m_bWndBorder = bWndBorder;
	m_clrWndBorder =  color;
}

void CToolbarWndCtrl::SetFont(int nHeight, LPCTSTR lpszFaceName)
{
	HFONT hfont;

	LOGFONT lf;
	ZeroMemory(&lf, sizeof(lf));

	lf.lfHeight = nHeight;
	lf.lfWeight = FW_BOLD;
	_tcscpy_s(lf.lfFaceName, lpszFaceName);

	hfont = CreateFontIndirect(&lf);
	if (m_pFont != NULL && m_pFont->m_hObject)
	{
		m_pFont->DeleteObject();
	}

	m_pFont = CFont::FromHandle(hfont);
	m_bRefreshText = TRUE;
	Invalidate(TRUE);
}

void CToolbarWndCtrl::SetWndText(LPCTSTR lpszWndText, CONST RECT *lprcText, COLORREF color)
{
	CRect rcText;
	if (lpszWndText == NULL || *lpszWndText == '\0')
	{
		return;
	}

	if (strcmp(lpszWndText, m_strWndText.GetBuffer(0)) != 0)
	{
		m_strWndText = lpszWndText;
	}

	if (lprcText != NULL)
	{
		rcText = lprcText;
		if (!rcText.EqualRect(&m_rcText))
		{
			m_rcText = lprcText;
		}
	}

	m_clrNormalText = color;
}

void CToolbarWndCtrl::SetTextColor(COLORREF clrNormalText, COLORREF clrSelText)
{
	m_clrNormalText =  clrNormalText;
	m_clrSelText = clrSelText;
}

void CToolbarWndCtrl::SetWndTipText(LPCTSTR lpszWndTipText, COLORREF color)
{
	m_strWndTipText = lpszWndTipText;
	m_clrWndTipText =  color;
}

void CToolbarWndCtrl::SetSelColor(COLORREF clrSelBorder, COLORREF clrSelFill)
{
	m_clrSelBorder = clrSelBorder;
	m_clrSelFill = clrSelFill;
}

void CToolbarWndCtrl::SetHoverColor(COLORREF clrHoverBorder, COLORREF clrHoverFill)
{
	m_clrHoverBorder = clrHoverBorder;
	m_clrHoverFill = clrHoverFill;
}