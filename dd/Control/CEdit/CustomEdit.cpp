// CustomEdit.cpp : implementation file
//

#include "stdafx.h"
#include "CustomEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomEdit

CCustomEdit::CCustomEdit()
{
	m_font.CreateFont(
		20,
		0,
		0,
		0,
		FW_NORMAL,
		TRUE,
		FALSE,
		0,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_SWISS,
		_T("Calibri"));

	m_hIcon=NULL;
	m_bIcon=FALSE;
	m_colText=RGB(127,127,127);
	m_Colour=RGB(255,255,0);
}

CCustomEdit::~CCustomEdit()
{
	DestroyIcon();
}


BEGIN_MESSAGE_MAP(CCustomEdit, CEdit)
	//{{AFX_MSG_MAP(CCustomEdit)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomEdit message handlers

void CCustomEdit::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rect;
	GetClientRect(&rect);
 

	dc.FillSolidRect(rect,GetSysColor(COLOR_WINDOW));
	DWORD dwMargins = GetMargins();               //获取编辑控件左右边距(像素);双字的低字位为左边距，高字位为右边距;
	if (m_hIcon)
	{ 
		int width=GetSystemMetrics(SM_CXSMICON);  //以像素显示下图标尺寸，出现在窗口标题栏上;
		int height=GetSystemMetrics(SM_CYSMICON);

		::DrawIconEx(
			dc.m_hDC,
			rect.right-width-1,
			1,
			m_hIcon,
			width,
			height,
			0,
			NULL,
			DI_NORMAL);
		rect.left += LOWORD(dwMargins) + 1;
		rect.right -= (width + 7);
	}
	else
	{
		rect.left += (LOWORD(dwMargins) + 1);
		rect.right -= (HIWORD(dwMargins) + 1);
	}

	CString text;
	GetWindowText(text);
	CFont* oldFont = NULL;
 
	rect.top += 1;

	if(text.GetLength() == 0)
	{		
		if(this != GetFocus() && m_strText.GetLength() > 0)
		{
			oldFont = dc.SelectObject(&m_font);
			COLORREF color = dc.GetTextColor();
			dc.SetTextColor(m_colText);
			dc.DrawText(m_strText, rect, DT_LEFT|DT_SINGLELINE|DT_EDITCONTROL);
			dc.SetTextColor(color);
			dc.SelectObject(oldFont);
		}
	}
	else
	{
		oldFont = dc.SelectObject(GetFont());
		dc.DrawText(text, rect, DT_SINGLELINE|DT_INTERNAL|DT_EDITCONTROL);
		dc.SelectObject(oldFont);
	}
}

void CCustomEdit::OnSize(UINT nType, int cx, int cy) 
{
	CEdit::OnSize(nType, cx, cy);
	RecalcLayout();
}

HBRUSH CCustomEdit::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	CDC* dc = GetDC(); //获取画布对象
	CRect rect;
	GetClientRect(rect); //获取客户区域
	rect.InflateRect(1,1,1,1);//将客户区域增大一个像素
	CBrush brush (m_Colour);//创建画刷
	dc->FrameRect(rect,&brush);//
	return NULL;
//	HBRUSH hbr = CEdit::OnCtlColor(pDC, pWnd, nCtlColor);
//	return hbr;
}


void CCustomEdit::RecalcLayout()
{
/*	int width = GetSystemMetrics(SM_CXSMICON);
	if (m_hIcon)
	{
		DWORD dwMargins = GetMargins();
		SetMargins(LOWORD(dwMargins), width + 6);
	}*/
}

void CCustomEdit::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
//	RecalcLayout();
//	ModifyStyleEx(0, WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE |  WS_EX_RIGHT);
	CEdit::PreSubclassWindow();
}

LRESULT CCustomEdit::OnSetFont(WPARAM wParam, LPARAM lParam)
{
	DefWindowProc(WM_SETFONT, wParam, lParam);
	
	RecalcLayout();
	
	return 0;
}

void CCustomEdit::DestroyIcon()
{
	if (m_bIcon || m_hIcon!=NULL)
	{
		::DestroyIcon(m_hIcon);
	}
}


void CCustomEdit::SetCurIcon(HICON hIcon, BOOL redraw)
{
	DestroyIcon();
	m_hIcon=hIcon;
	m_bIcon=FALSE;
	RecalcLayout();
	if (redraw)
	{
		Invalidate(TRUE);
	}
}

void CCustomEdit::SetCurIcon(UINT id,BOOL redraw)
{
	DestroyIcon();
	m_hIcon=(HICON)::LoadImage(
		AfxGetResourceHandle(),
		MAKEINTRESOURCE(id),
		IMAGE_ICON,
		16,
		16,
		LR_DEFAULTCOLOR|LR_LOADTRANSPARENT);
	ASSERT(m_hIcon != NULL);

	m_bIcon=TRUE;
	RecalcLayout();
	if (redraw)
	{
		Invalidate(TRUE);
	}
}

void CCustomEdit::SetCurText(CString strText,BOOL redraw)
{
	m_strText=strText;
	if (redraw)
	{
		Invalidate(TRUE);
	}
}

void CCustomEdit::SetCurText(LPCTSTR szText,BOOL redraw)
{
	m_strText=szText;
	if (redraw)
	{
		Invalidate(TRUE);
	}
}

void CCustomEdit::SetCurFont(CFont& font, BOOL redraw)
{
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));

	font.GetLogFont(&lf);
	SetCurFont(&lf);

	if (redraw)
	{
		Invalidate(TRUE);
	}
}

void CCustomEdit::SetCurFont(const LOGFONT* lpLogFont, BOOL redraw)
{
	m_font.DeleteObject();
	m_font.CreateFontIndirect(lpLogFont);
	if (redraw)
	{
		Invalidate(TRUE);
	}
}


