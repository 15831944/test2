#include "stdafx.h"
#include "../dd.h"
#include "DlgOutPutCtrl.h"

#include "DlgPreViewCtrl.h"

IMPLEMENT_DYNAMIC(CDlgOutPutCtrl, CDialog)
CDlgOutPutCtrl::CDlgOutPutCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOutPutCtrl::IDD, pParent)
{
	m_bWndSel = FALSE;
	m_bWndHover = FALSE;
	m_bWndBorder = FALSE;
	m_bWndBkBmp = FALSE;
	m_bWndMultiScreen = FALSE;

	m_pBkBmp = NULL;

	m_nCurWndNum = -1;

	m_clrHoverBorder = RGB(169, 216, 236);
	m_clrHoverFill   = RGB(229, 238, 245);
	m_clrSelBorder   = RGB(169, 216, 236);
	m_clrSelFill	 = RGB(0,   0,   180);
	m_clrWndBorder = RGB(141, 141, 141);
}

CDlgOutPutCtrl::~CDlgOutPutCtrl()
{
	if (m_pBkBmp)
	{
		delete m_pBkBmp;
		m_pBkBmp = NULL;
	}
}

void CDlgOutPutCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgOutPutCtrl, CDialog)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


BOOL CDlgOutPutCtrl::OnInitDialog()
{
	CDialog::OnInitDialog();


	return TRUE; 
}

void CDlgOutPutCtrl::OnPaint()
{
	CPaintDC dc(this); 

	CPen   BorderPen, *pOldPen(NULL);
	CBrush FillBrush, *pOldBrush(NULL);

	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(1,1);


// 	if (m_bWndSel)
// 	{
// 		FillBrush.CreateSolidBrush(m_clrSelFill);
// 		pOldBrush = dc.SelectObject(&FillBrush);
// 
// 		BorderPen.CreatePen(PS_SOLID, 1, m_clrSelBorder);
// 		pOldPen = dc.SelectObject(&BorderPen);
// 
// 		dc.RoundRect(&rect, CPoint(5,5));
// 
// 		dc.SelectObject(pOldPen);
// 		dc.SelectObject(pOldBrush);
// 
// 		BorderPen.DeleteObject();
// 		FillBrush.DeleteObject();
// 	}

	if (m_bWndHover)
	{
		FillBrush.CreateSolidBrush(m_clrHoverFill);
		pOldBrush = dc.SelectObject(&FillBrush);

		BorderPen.CreatePen(PS_SOLID, 1, m_clrHoverBorder);
		pOldPen = dc.SelectObject(&BorderPen);

		dc.RoundRect(&rect, CPoint(5,5));

		dc.SelectObject(pOldPen);
		dc.SelectObject(pOldBrush);

		BorderPen.DeleteObject();
		FillBrush.DeleteObject();
	}
}


BOOL CDlgOutPutCtrl::OnEraseBkgnd(CDC* pDC)
{
	CPen pen, *pOldPen(NULL);

	CRect rect;
	GetClientRect(&rect);
	rect.DeflateRect(1,1);

	if (m_bWndBorder)
	{
		pen.CreatePen(PS_SOLID, 1, m_clrWndBorder);
		pOldPen = pDC->SelectObject(&pen);

		pDC->Rectangle(&rect);

		pDC->SelectObject(pOldPen);
		pen.DeleteObject();
	}	

	return TRUE;
//	return CDialog::OnEraseBkgnd(pDC);
}


void CDlgOutPutCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	static DWORD dwRet = 0;

	CRect rect;
	GetClientRect(&rect);

	if (rect.PtInRect(point))
	{//鼠标移进窗口
		dwRet++;					//防止窗口连续闪烁
		SetCapture();

		if (dwRet == 1)
		{
			m_bWndHover = TRUE;
			InvalidateRect(&rect);	
		}
		else
		{
			return;
		}
	}
	else
	{//鼠标移出窗口
		dwRet=0;
		ReleaseCapture();

		m_bWndHover = FALSE;	
		InvalidateRect(&rect);
	}

	CDialog::OnMouseMove(nFlags, point);
}


void CDlgOutPutCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CDlgPreViewCtrl* pDlg = (CDlgPreViewCtrl*)GetParent();
	if (pDlg == NULL)
	{
		return;
	} 

	if (pDlg->GetViewerNums() > 1)
	{//多屏状态-->全屏
		m_bWndMultiScreen = FALSE;
		
		m_nCurWndNum = pDlg->GetViewerNums();
		::PostMessage(pDlg->GetSafeHwnd(), WM_SWITCHMULTI_CTRL, M_FULLSCREEN_CTRL, m_dwChannel);
	}
	else
	{//全屏状态-->多屏
		m_bWndMultiScreen = TRUE;
		::PostMessage(pDlg->GetSafeHwnd(), WM_SWITCHMULTI_CTRL, M_MULTISCREEN_CTRL, m_nCurWndNum);
	}

	CDialog::OnLButtonDblClk(nFlags, point);
}


void CDlgOutPutCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(&rect);

	if (rect.PtInRect(point))
	{
		m_bWndSel = TRUE;
		InvalidateRect(&rect);
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgOutPutCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	CMenu menu;
	CDialog::OnRButtonDown(nFlags, point);
}
//////////////////////////////////////////////////////////////////////////
//
void CDlgOutPutCtrl::SetWndBorder(BOOL bWndBorder, COLORREF clrWndBorder)
{
	m_bWndBorder = bWndBorder;
	m_clrWndBorder = clrWndBorder;
}

void CDlgOutPutCtrl::SetWndBkColor(COLORREF clrWndBk)
{
	m_clrWndBk = clrWndBk;
}

void CDlgOutPutCtrl::SetHoverColor(COLORREF clrHoverBorder, COLORREF clrHoverFill)
{
	m_clrHoverBorder = clrHoverBorder;
	m_clrHoverFill = clrHoverFill;
}

void CDlgOutPutCtrl::SetSelColor(COLORREF clrSelBorder, COLORREF clrSelFill)
{
	m_clrSelBorder = clrSelBorder;
	m_clrSelFill = clrSelFill;
}

void CDlgOutPutCtrl::SetBkBmp(LPCTSTR lpBitmapName)
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

void CDlgOutPutCtrl::SetBkBmp(UINT nIDBmp)
{
	m_pBkBmp->LoadBitmap(nIDBmp);
	m_bWndBkBmp = TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
void CDlgOutPutCtrl::SetWndChannel(DWORD dwChannel)
{
	m_dwChannel = dwChannel;
}

DWORD CDlgOutPutCtrl::GetWndChannel()
{
	return m_dwChannel;
}

void CDlgOutPutCtrl::SetMultiScreen(BOOL bFlag)
{

}