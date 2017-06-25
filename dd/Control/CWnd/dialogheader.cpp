// dialogheader.cpp : implementation file
//

#include "stdafx.h"

#include "dialogheader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogHeader

CDialogHeader::CDialogHeader()
{
	m_hIcon  = NULL;
	m_bmpID  = -1;
	m_sTitle = _T("");
	m_sDesc  = _T("");

	m_bFonts = FALSE;
	m_nTitleFontSize = DEFAULTTITLEFONTSIZE;
	m_nDescFontSize  = DEFAULTDESCFONTSIZE;

	m_nIconOffset    = DEFAULTICONOFFSET;
	m_nTitleOffset   = DEFAULTTITLEOFFSET;
	m_nDescOffset    = DEFAULTDESCOFFSET;
	m_uAlign         = DEFAULTTEXTALIGN;
	m_nHeaderHeight	 = DEFAULTHEADERHEIGHT;
	m_bBlankIcon	 = DEFAULTBLANKICON;

	m_cBackground    = GetSysColor(COLOR_WINDOW);
	m_nIconWidth     = ::GetSystemMetrics(SM_CXICON);
	m_nIconHeight    = ::GetSystemMetrics(SM_CYICON);

	m_nxEdge		 = ::GetSystemMetrics(SM_CXEDGE);
	m_nyEdge		 = ::GetSystemMetrics(SM_CYEDGE);
}

CDialogHeader::~CDialogHeader()
{
}


BEGIN_MESSAGE_MAP(CDialogHeader, CWnd)
	//{{AFX_MSG_MAP(CDialogHeader)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDialogHeader message handlers

BOOL CDialogHeader::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;	
//	return CWnd::OnEraseBkgnd(pDC);
}

void CDialogHeader::OnPaint() 
{
	CPaintDC dc(this); 
	CRect rect, rcEffect;
	CRect rcText;
	GetClientRect(&rect);

	rcEffect.left = rect.left;
	rcEffect.top  = rect.bottom -2;
	rcEffect.right  = rect.right;
	rcEffect.bottom = rect.bottom;
	dc.FillSolidRect(rect.left, rect.top, rect.Width(), rect.Height()-m_nxEdge, m_cBackground);
	dc.Draw3dRect(rcEffect, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHIGHLIGHT));

	//////////////////////////////////////////////////////////////////////////
	//
	if (m_hIcon != NULL)
	{
		dc.DrawIcon(m_nIconOffset, m_nIconOffset, m_hIcon);
	}

	if (!m_bFonts)
	{
		UpdateFont(m_NormalFont, FW_NORMAL, m_nDescFontSize);
		UpdateFont(m_BoldFont, FW_BOLD, m_nTitleFontSize);
	}

	if (m_bmpID != -1)
	{
		CDC dcBmp;
		dcBmp.CreateCompatibleDC(&dc);
		CBitmap* pOldBmp = dcBmp.SelectObject(&m_bmpHead);
		dc.BitBlt(rcEffect.right-m_sizBmp.cx, 0, m_sizBmp.cx, m_sizBmp.cy, &dcBmp, 0, 0, SRCCOPY);
		dcBmp.SelectObject(pOldBmp);
	}

	dc.SelectObject(&m_BoldFont);
	rcText.left = rect.left + m_nTitleOffset;
	if ((m_hIcon!=NULL) && (m_bBlankIcon!=NULL))
	{
		rcText.left += m_nIconWidth +m_nIconOffset;
	}
	rcText.top = rect.top + m_nIconOffset;
	rcText.right = rect.right - m_nIconOffset -m_nyEdge;
	rcText.bottom = rcText.top + m_nTitleFontSize;

	if (m_uAlign == DT_CENTER)
	{
		rcText.right = rcText.right - (rcText.left - rect.left);
	}
	DrawText(dc.m_hDC,m_sTitle,m_sTitle.GetLength(),rcText,
	         m_uAlign | DT_WORDBREAK | DT_END_ELLIPSIS | DT_EDITCONTROL);
	dc.SelectObject (&m_NormalFont);

	if (m_uAlign == DT_LEFT)
	{
		rcText.left = rcText.left + m_nDescOffset;
	}
	if (m_uAlign == DT_RIGHT)
	{
		rcText.right = rcText.right - m_nDescOffset;
	}
	rcText.top = rcText.bottom;
	rcText.bottom = rect.bottom;
	DrawText(dc.m_hDC,m_sDesc,m_sDesc.GetLength(),rcText,
	         m_uAlign | DT_WORDBREAK | DT_END_ELLIPSIS | DT_EDITCONTROL);
}
//////////////////////////////////////////////////////////////////////////
//
void CDialogHeader::Init(void* ptrWnd)
{
	CRect rect;
	CWnd* pWnd = (CWnd*)ptrWnd;

	if ((NULL==pWnd) || (NULL==pWnd->m_hWnd))
	{
		return ;
	}

	SetHeaderHeight(m_nHeaderHeight);
	pWnd->GetWindowRect(&rect);
	pWnd->ScreenToClient(&rect);
	pWnd->SetWindowPos(NULL, 
					   0, 0, 
					   rect.Width(), rect.Height() + m_nHeaderHeight,
		               SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	CreateEx(NULL, NULL, NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP, NULL, NULL, rect.Width(), m_nHeaderHeight, pWnd->m_hWnd, 0, 0);
}

void CDialogHeader::MoveCtrls(void* ptrWnd)
{
	CRect rect;
	CWnd* pWnd = (CWnd*)ptrWnd;
	CWnd* pwndChild = NULL;

	if ((NULL==pWnd) || (NULL== pWnd->m_hWnd))
	{
		return;
	}
	pwndChild = pWnd->GetWindow(GW_CHILD);
	while(pwndChild)
	{
		if (pwndChild != this)
		{
			pwndChild->GetWindowRect(&rect);
			ScreenToClient(&rect);

			pwndChild->SetWindowPos(NULL, rect.left, rect.top+m_nHeaderHeight, rect.Width(), rect.Height(), SWP_NOZORDER | SWP_NOACTIVATE);
		}
		pwndChild = pwndChild->GetNextWindow();
	}
}

void CDialogHeader::SetBMPRes(const UINT rID/* =-1 */)
{
	m_bmpID = rID;
	if (rID != -1)
	{
		if (!m_bmpHead.LoadBitmap(rID))
		{
			m_bmpID = -1;
		}

		BITMAP bmp;
		m_bmpHead.GetBitmap(&bmp);
		m_sizBmp.cx = bmp.bmWidth;
		m_sizBmp.cy = bmp.bmHeight;
	}
	RepaintHeader();
}

void CDialogHeader::RepaintHeader()
{
	if (NULL != m_hWnd)
	{
		Invalidate();
	}
}

void CDialogHeader::UpdateFont(CFont& font,const LONG lfWeight,const int Size)
{
	font.DeleteObject();
	font.CreateFont(Size, 0, 0, 0, lfWeight, 0, 0, 0,
					ANSI_CHARSET, OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS, PROOF_QUALITY,
					VARIABLE_PITCH|0X04|FF_DONTCARE, 
					_T("Tahoma"));
}
//////////////////////////////////////////////////////////////////////////
//
void CDialogHeader::SetBackgroundColor(const COLORREF color)
{
	m_cBackground = color;
	RepaintHeader();
}

void CDialogHeader::SetDescText(const LPCTSTR text)
{
	m_sDesc = text;
	RepaintHeader();
}

void CDialogHeader::SetTitleText(const LPCTSTR text)
{
	m_sTitle = text;
	RepaintHeader();
}

void CDialogHeader::SetTitleFontSize(const int TitleSize/* =DEFAULTTITLEFONTSIZE */)
{
	if (TitleSize < 10)
	{
		m_nTitleFontSize = 10;
	}
	else
	{
		m_nTitleFontSize = TitleSize;
	}

	m_bFonts=FALSE;
	RepaintHeader();
}

void CDialogHeader::SetDescFontSize(const int DescSize/* =DEFAULTDESCFONTSIZE */)
{
	if (DescSize < 10)
	{
		m_nDescFontSize = 10;
	}
	else
	{
		m_nDescFontSize = DescSize;
	}
	m_bFonts=FALSE;
	RepaintHeader();
}

void CDialogHeader::SetHeaderHeight(const int height/* =0 */)
{
	int	minIcon=0;
	int	minText=0;
	int min=0;

	minIcon = (2 * m_nIconOffset) + m_nIconHeight + m_nyEdge;
	minText = (2 * m_nIconOffset) + m_nTitleFontSize + m_nDescFontSize + 2 + m_nyEdge;

	if (minIcon < minText)
	{
		min = minText;
	}
	else
	{
		min = minIcon;
	}

	if (height < min)
	{
		m_nHeaderHeight = min;
	}
	else
	{
		m_nHeaderHeight = height;
	}
	RepaintHeader();
}

void CDialogHeader::SetIconHandle(const HICON icon)
{
	m_hIcon = icon;
	RepaintHeader();
}

void CDialogHeader::SetIconOffset(const int offset/* =DEFAULTICONOFFSET */)
{
	if (offset < 2)
	{
		m_nIconOffset = 2;
	}
	else
	{
		m_nIconOffset = offset;
	}
	RepaintHeader();
}

void CDialogHeader::SetTitleOffset(const int offset/* =DEFAULTTITLEOFFSET */)
{
	if (offset < 2)
	{
		m_nTitleOffset = 2;
	}
	else
	{
		m_nTitleOffset = offset;
	}
	RepaintHeader();
}

void CDialogHeader::SetDescOffset(const int offset/* =DEFAULTDESCOFFSET */)
{
	m_nDescOffset = offset;
	RepaintHeader();
}

void CDialogHeader::SetTextAlign(const UINT align/* =DEFAULTTEXTALIGN */)
{
	if ((align != DT_LEFT) && (align != DT_CENTER) && (align != DT_RIGHT))
	{
		m_uAlign = DT_LEFT;
	}
	else
	{
		m_uAlign = align;
	}
	RepaintHeader();
}

void CDialogHeader::SetBlankIcon(const BOOL blank/* =DEFAULTBLANKICON */)
{
	m_bBlankIcon = blank;
	RepaintHeader();
}

//////////////////////////////////////////////////////////////////////////
//