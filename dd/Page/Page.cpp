#include "stdafx.h"
#include "../dd.h"
#include "Page.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CPage::CPage(UINT nIDTemplate,CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
	m_brush.CreateSolidBrush(RGB(213,228,242)); 
}

BEGIN_MESSAGE_MAP(CPage, CDialog)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CPage::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_ESCAPE||pMsg->wParam==13)
		{
			return TRUE;
		}
	}
	else
	{
		if (pMsg->message==WM_LBUTTONDBLCLK)
		{
			if (pMsg->wParam==NM_DBLCLK)
			{
				return TRUE;
			}
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}


void CPage::OnPaint() 
{
	CPaintDC dc(this); 

	CRect rcRect;
	GetClientRect(&rcRect);
	CMemDC memDC(&dc, &rcRect);

	CDC bitmapDC;
	bitmapDC.CreateCompatibleDC(&dc);

	CBitmap bmp;
	bmp.LoadBitmap(IDB_BACKGROUND);

	CBitmap *pOldBitmap = bitmapDC.SelectObject(&bmp);
	memDC->BitBlt(0,0,rcRect.Width(), rcRect.Height(), &bitmapDC, 0, 0, SRCCOPY);

	bitmapDC.SelectObject(pOldBitmap);
	bmp.DeleteObject();


// 	CBitmap bmpStretch;
// 	bmpStretch.Attach(StretchBitmap((HBITMAP)bmp.GetSafeHandle(), rClient.Width(), rClient.Height()));
// 	::DeleteObject((HBITMAP)bmp.Detach());
}


HBRUSH CPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_STATIC ) 
	{
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkMode(TRANSPARENT); 
		hbr=(HBRUSH)m_brush;
	}
	return hbr;
}
