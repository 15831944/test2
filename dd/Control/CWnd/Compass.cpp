#include "stdafx.h"
#include "Compass.h"

static int g_point_array[12][2] = {
	{-14, 30},	//-14, 30
	{-5,  38},
	{0,   46},
	{5,   38},
	{14,  30},
	{4,   34},
	{4,  -36},
	{14, -46},
	{0,  -40},
	{-14,-46},	//-14, -46
	{-4, -36},
	{-4,  34}
};

DECLARE_MESSAGE(CPM_SET_ANGLE)
Compass::Compass()
{
	m_angle = 0.0;
	m_bArrowVisible = FALSE;

	m_arryDisplay.Add(new displayinfo(0.0, _T("N"), 100.0, TRUE));
	m_arryDisplay.Add(new displayinfo(90.0, _T("E"), 90.0, FALSE));
	m_arryDisplay.Add(new displayinfo(180.0, _T("S"), 90.0, FALSE));
	m_arryDisplay.Add(new displayinfo(270.0, _T("W"), 90.0, FALSE));

	m_arryDisplay.Add(new displayinfo( 45.0, _T("NE"), 80.0, FALSE));
	m_arryDisplay.Add(new displayinfo(135.0, _T("SE"), 80.0, FALSE));
	m_arryDisplay.Add(new displayinfo(225.0, _T("SW"), 80.0, FALSE));
	m_arryDisplay.Add(new displayinfo(315.0, _T("NW"), 80.0, FALSE));
}

Compass::~Compass()
{
}

BEGIN_MESSAGE_MAP(Compass, CWnd)
	//{{AFX_MSG_MAP(Compass)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_ENABLE()
	ON_WM_LBUTTONDOWN()	
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL Compass::hasclass = Compass::RegisterWindowClass();

BOOL Compass::RegisterWindowClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = (HINSTANCE)GetModuleHandle(NULL); //AfxGetResourceHandle();

	if (!(::GetClassInfo(hInst, COMPASS_CLASS_NAME, &wndcls)))
	{
		wndcls.style = CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.cbClsExtra  = 0;
		wndcls.cbWndExtra  = 0;
		wndcls.hInstance   = hInst;
		wndcls.hIcon       = NULL;
		wndcls.hCursor     = NULL;
		wndcls.hbrBackground = (HBRUSH)(COLOR_3DFACE + 1);	//COLOR_BTNFACE
		wndcls.lpszMenuName	 = NULL;
		wndcls.lpszClassName = COMPASS_CLASS_NAME;

		if(!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}

BOOL Compass::Create(DWORD dwStyle, const RECT &rect, CWnd* pParentWnd, UINT nID)
{
	ASSERT(pParentWnd->GetSafeHwnd());

	if (!CWnd::Create(COMPASS_CLASS_NAME, NULL, dwStyle, rect, pParentWnd, nID))
	{
		return FALSE;
	}

	return TRUE;
}


BOOL Compass::OnEraseBkgnd(CDC* pDC)
{
	CRgn rgn;
	CSaveDC sdc(pDC);

	CreateClipRegion(rgn);
	pDC->SelectClipRgn(&rgn, RGN_DIFF);

	return CWnd::OnEraseBkgnd(pDC);
}

void Compass::OnPaint()
{
	CPaintDC dc(this);	

	int nIndex = 0;

	CRgn rgn;
	CRect rect;
	CRect rcPoint;
	CFont* pFont = NULL;
	
	CBrush FillBrush(::GetSysColor(COLOR_INFOBK));
	CBrush NeedleBrush(RGB(255,0,0));
	
	CPen BorderPen(PS_SOLID, BORDER_WIDTH, RGB(0,0,0));
	CPen EnablePen(PS_SOLID, 0, RGB(0, 0, 0));
	CPen DisablePen(PS_SOLID, 0, RGB(128,128,128));

	rect = CreateClipRegion(rgn);
	CPoint center(rect.left+rect.Width()/2, rect.top+rect.Height()/2);
	rect -= center;
	int radius = rect.Width()/2;

	CSaveDC sdc1(dc);
	
	dc.SelectClipRgn(&rgn);
	dc.FillRgn(&rgn, &FillBrush);
	dc.SetBkMode(TRANSPARENT);

	//坐标系转换
	MapDC(dc);

	//画边框线
	{
		CSaveDC sdc2(dc);
	
		dc.SelectClipRgn(NULL);
		dc.SelectStockObject(HOLLOW_BRUSH);

		dc.SelectObject(&BorderPen);
		dc.Ellipse(-radius, -radius, radius, radius);

		rect.InflateRect(-BORDER_WIDTH, -BORDER_WIDTH);
		radius = rect.Width() / 2;
	}

	//
	dc.SelectObject(IsWindowEnabled() ? &EnablePen : &DisablePen);

	//Draw N-S Line
	dc.MoveTo(0, radius);
	dc.LineTo(0, -radius);
	//Draw E-W Line
	dc.MoveTo(-radius, 0);
	dc.LineTo(radius, 0);

	// Draw SW-NE line
	dc.MoveTo((int)(radius * sin(DegreesToRadians(GeographicToGeometric(225.0)))), 
		(int)(radius * cos(DegreesToRadians(GeographicToGeometric(225.0)))) );
	dc.LineTo((int)(radius * sin(DegreesToRadians(GeographicToGeometric( 45.0)))),
		(int)(radius * cos(DegreesToRadians(GeographicToGeometric( 45.0)))) );
	// Draw NW-SE line
	dc.MoveTo((int)(radius * sin(DegreesToRadians(GeographicToGeometric(315.0)))), 
		(int)(radius * cos(DegreesToRadians(GeographicToGeometric(315.0)))) );
	dc.LineTo((int)(radius * sin(DegreesToRadians(GeographicToGeometric(135.0)))),
		(int)(radius * cos(DegreesToRadians(GeographicToGeometric(135.0)))) );

	dc.SetTextColor(IsWindowEnabled() ? ENABLED_COLOR : DISABLED_COLOR);

	double size = 0.15 * (double)rect.Width();
	double CurrentFontSize = 0.0; // current font size

	CSize textSize;
	CString strDisplay = _T("");

	m_innerRadius = radius;
	for (nIndex=0; nIndex<m_arryDisplay.GetSize(); nIndex++)
	{
		CSaveDC sdc3(dc);

		dc.SetBkMode(OPAQUE);
		dc.SetBkColor(::GetSysColor(COLOR_INFOBK));

		if (m_arryDisplay[nIndex]->GetSize() != CurrentFontSize)
		{
			if (pFont != NULL)
			{
				delete pFont;
				pFont = NULL;
			}

			pFont = m_arryDisplay[nIndex]->CreateFont(size, _T("Times New Roman"));
		}

		dc.SelectObject(pFont);

		CurrentFontSize = m_arryDisplay[nIndex]->GetSize();
		strDisplay = m_arryDisplay[nIndex]->GetText();

		int x = (int)(radius * cos(DegreesToRadians(GeographicToGeometric(m_arryDisplay[nIndex]->GetAngle()))));
		int y = (int)(radius * sin(DegreesToRadians(GeographicToGeometric(m_arryDisplay[nIndex]->GetAngle()))));

		textSize = dc.GetTextExtent(strDisplay);

		double theta = m_arryDisplay[nIndex]->GetAngle();
		if(theta == 0.0)
		{
			dc.SetTextAlign(TA_TOP | TA_LEFT);

			x -= textSize.cx / 2;
			m_innerRadius = radius - textSize.cy;
		}
		else if (theta < 90.0)
		{
			dc.SetTextAlign(TA_TOP | TA_RIGHT);
		}
		else if (theta == 90.0)
		{
			dc.SetTextAlign(TA_TOP | TA_RIGHT);
			y += textSize.cy / 2;
		}
		else if (theta < 180.0)
		{
			dc.SetTextAlign(TA_BOTTOM | TA_RIGHT);
		}
		else if (theta == 180.0)
		{
			dc.SetTextAlign(TA_BOTTOM | TA_LEFT);
			x -= textSize.cx / 2;
		}
		else if (theta < 270.0)
		{
			dc.SetTextAlign(TA_BOTTOM | TA_LEFT);
		}
		else if (theta == 270)
		{
			dc.SetTextAlign(TA_TOP | TA_LEFT);
			y += textSize.cy / 2;
		}
		else
		{
			dc.SetTextAlign(TA_TOP | TA_LEFT);
		}

		dc.TextOut(x, y, strDisplay);
	}

	if (pFont != NULL)
	{
		delete pFont;
		pFont = NULL;
	}

	//Draw the arrow
	if (IsWindowEnabled() && m_bArrowVisible)
	{
		rcPoint.SetRectEmpty();

		if (!SetPointRect(&rcPoint))
		{
			return;
		}

		dc.SelectObject(&NeedleBrush);

		if (!SetPointTrans(m_angle, ((double)abs(rcPoint.Height())/(2.0*(double)radius)), FALSE, &rcPoint))
		{
			return;
		}
	
		SetPointDraw(dc, 0.0, 0.0);
	}
}

void Compass::OnEnable(BOOL bEnable) 
{
	CWnd::OnEnable(bEnable);
	InvalidateRect(NULL);
}

void Compass::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRgn rgn;
	CreateClipRegion(rgn);

	if (rgn.PtInRegion(point))
	{
		SetCapture();
		NotifyParent(point);
		return;
	}

	CWnd::OnLButtonDown(nFlags, point);
}

void Compass::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (GetCapture() != NULL)
	{
		NotifyParent(point);
		ReleaseCapture();
	}

	CWnd::OnLButtonUp(nFlags, point);
}

void Compass::OnMouseMove(UINT nFlags, CPoint point)
{
	if (GetCapture() != NULL)
	{
		NotifyParent(point);
		return;
	}

	CWnd::OnMouseMove(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////
//
void Compass::MapDC(CDC & dc)
{
	CRect rect;
	GetClientRect(&rect);

	dc.SetMapMode(MM_ISOTROPIC);
	dc.SetWindowExt(rect.Width(), rect.Height());
	dc.SetViewportExt(rect.Width(), -rect.Height());

	CPoint center(rect.left+rect.Width()/2, rect.top+rect.Height()/2);
	dc.SetViewportOrg(center.x, center.y);
}

void Compass::NotifyParent(CPoint point)
{
	CClientDC dc(this);
	MapDC(dc);
	dc.DPtoLP(&point);

	GetParent()->SendMessage(CPM_SET_ANGLE, (WPARAM)point.x, (LPARAM)point.y);
}

CRect Compass::CreateClipRegion(CRgn& rgn)
{
	CRect rect;
	GetClientRect(&rect);

	int radius = min(rect.Width()/2, rect.Height()/2);
	
	CPoint center(rect.Width()/2, rect.Height()/2);
	rgn.CreateEllipticRgn(center.x-radius, center.y-radius, center.x+radius, center.y+radius);

	return CRect(center.x-radius, center.y-radius, center.x+radius, center.y+radius);
}

void Compass::SetShow(BOOL bShow)
{
	if (bShow == m_bArrowVisible)
	{
		return;
	}

	m_bArrowVisible = bShow;
	InvalidateRect(NULL);
}

void Compass::SetAngle(double angle)
{
	if (angle == m_angle)
	{
		return;
	}

	CRgn inner;

	CRect rect;
	GetClientRect(&rect);

	int radius = rect.Width()/2;
	m_angle = angle;

	CClientDC dc(this);
	MapDC(dc);

	CRect rr(-m_innerRadius, -m_innerRadius,m_innerRadius, m_innerRadius);
	dc.LPtoDP(&rr);
	rr.NormalizeRect();

	inner.CreateEllipticRgn(rr.left, rr.top, rr.right, rr.bottom);
	InvalidateRgn(&inner);
}

BOOL Compass::SetPointRect(CRect* pRectPoint)
{
	int nIndex = 0;

	int nLen = 0;
	int nCol = 0;
	int nRow = 0;

	CRect rcPoint;
	int nArray[2] = {0};

	if (pRectPoint == NULL)
	{
		return FALSE;
	}

	nLen = sizeof(g_point_array)/sizeof(int);
	nCol = sizeof(g_point_array[0])/sizeof(int);	//列
	nRow = nLen/nCol; //行

	rcPoint.SetRectEmpty();

	for (nIndex=0; nIndex<nRow; nIndex++)
	{
		memset(nArray, 0x0, sizeof(int)*2);
		memcpy(nArray, g_point_array[nIndex], sizeof(int)*nCol);

		if (nArray[0] < rcPoint.left)
		{
			rcPoint.left = nArray[0];
		}

		if (nArray[0] > rcPoint.right)
		{
			rcPoint.right = nArray[0];
		}

		if (nArray[1] < rcPoint.bottom)
		{
			rcPoint.bottom = nArray[1];
		}

		if (nArray[1] > rcPoint.top)
		{
			rcPoint.top = nArray[1];
		}
	}

	pRectPoint->CopyRect(&rcPoint);
	return TRUE;
}

BOOL Compass::SetPointTrans(double angle, double scale, BOOL force, CRect* pRectPoint)
{
	int nIndex = 0;

	int nLen = 0;
	int nCol = 0;
	int nRow = 0;

	CRect rcPoint;
	int nArray[2] = {0};

	if (pRectPoint == NULL)
	{
		return FALSE;
	}

	rcPoint.SetRectEmpty();

	if (!force && (angle == m_angle) && (scale == m_scale) && (m_arrayPoint.GetSize() == m_arryDisplay.GetSize()))
	{
		return FALSE;
	}

	m_angle = angle;
	m_scale = scale;

	m_arrayPoint.RemoveAll();

	nLen = sizeof(g_point_array)/sizeof(int);
	nCol = sizeof(g_point_array[0])/sizeof(int);	//列
	nRow = nLen/nCol; //行

	for (nIndex=0; nIndex<nRow; nIndex++)
	{
		memset(nArray, 0x0, sizeof(int)*2);
		memcpy(nArray, g_point_array[nIndex], sizeof(int)*nCol);

		CPoint pt = RotatePoint(nArray[0], nArray[1], -angle, scale);

		rcPoint.left = pt.x;
		rcPoint.right = pt.x;
		rcPoint.top  = pt.y;
		rcPoint.bottom = pt.y;

		m_arrayPoint.Add(pt);
	}

	pRectPoint->CopyRect(&rcPoint);
	return TRUE;
}

void Compass::SetPointDraw(CDC& dc, LONG x, LONG y)
{
	CSaveDC sdc(dc);

	CPoint org = dc.GetWindowOrg();
	dc.SetWindowOrg(-(int)x, -(int)y);

	CPoint* ptArray = m_arrayPoint.GetData();
	dc.Polygon(ptArray, m_arrayPoint.GetSize());
}

CPoint Compass::RotatePoint(LONG x, LONG y, double angle, double scale)
{
	CPoint pt;
	double theta = DegreesToRadians(angle);

	pt.x = (scale * (cos(theta) * x - sin(theta) * y) + 0.5);
	pt.y = (scale * (sin(theta) * x + cos(theta) * y) + 0.5);

	return pt;
}
