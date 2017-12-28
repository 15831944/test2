#ifndef __COMPASS_H__
#define __COMPASS_H__

#include "../../Inc/common/DtoR.h"

#define  COMPASS_CLASS_NAME		_T("CompassWnd")

#define BORDER_WIDTH			2
#define ENABLED_COLOR			RGB(0,0,0)
#define DISABLED_COLOR			RGB(128,128,128)

#define CPM_SET_ANGLE_MSG _T("CPM_SET_ANGLE-{66F100A0-BBB9-11d5-A044-006067718D04}")
#define DECLARE_MESSAGE(x) static UINT x = ::RegisterWindowMessage(x##_MSG);

class displayinfo
{
public:
	displayinfo(double angle, LPCTSTR strDisplay, double size, BOOL bSpecial) 
	{
		m_size  = size;
		m_angle = angle;

		m_bSpecial = bSpecial;
		m_strDisplay = strDisplay;
	}

	virtual ~displayinfo() {}

public:
	double						GetSize()	{ return m_size; }
	double						GetAngle()  { return m_angle; }

	CString						GetText()   { return m_strDisplay; }
	CFont*						CreateFont(double basesize, LPCTSTR facename)
	{
		CFont* pFont = new CFont;

		pFont->CreateFont((int)(basesize * m_size / 100.0),		// font height
						  0,					// font width
						  0,					// escapement
						  0,					// orientation
						  m_bSpecial ? FW_BOLD : FW_NORMAL,		// weight
						  m_bSpecial,           // italic
						  FALSE,                // underline
						  FALSE,                // strikeout
						  ANSI_CHARSET,         // character set
						  OUT_TT_PRECIS,        // output precision
						  CLIP_TT_ALWAYS,       // clip precision
						  PROOF_QUALITY,        // quality
						  VARIABLE_PITCH | FF_DONTCARE,			// pitch and family
						  facename);
		return pFont;
	}

protected:
	BOOL						m_bSpecial;

	double						m_angle;
	double						m_size;

	CString						m_strDisplay;
};

//////////////////////////////////////////////////////////////////////////
//
class Compass : public CWnd
{
public:
	Compass();
	virtual ~Compass();
	
public:
	BOOL						Create(DWORD dwStyle, const RECT &rect, CWnd* pParentWnd, UINT nID);

	void						SetShow(BOOL bShow);
	void						SetAngle(double angle);

	BOOL						GetShow() { return m_bArrowVisible; }

protected:
	static BOOL					hasclass;
	static BOOL					RegisterWindowClass();

protected:
	//{{AFX_MSG(CDisplayWindow)
	afx_msg void				OnPaint();
	afx_msg BOOL				OnEraseBkgnd(CDC* pDC);
	afx_msg void				OnEnable(BOOL bEnable);
	afx_msg void				OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void				OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void				OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void						MapDC(CDC& dc);
	void						NotifyParent(CPoint point);
	CRect						CreateClipRegion(CRgn & rgn);

	BOOL						SetPointRect(CRect* pRectPoint);
	BOOL						SetPointTrans(double angle, double scale, BOOL force, CRect* pRectPoint);
	void						SetPointDraw(CDC& dc, LONG x, LONG y);

	CPoint						RotatePoint(LONG x, LONG y, double angle, double scale);

protected:
	CFont						m_NorthFont;
	CFont						m_MajorFont;
	CFont						m_MinorFont;

	CArray<CPoint, CPoint>		m_arrayPoint;
	CArray<displayinfo*, displayinfo*>	m_arryDisplay;

private:
	BOOL						m_bArrowVisible;

	int							m_innerRadius;
	double						m_angle;
	double						m_scale;
};	

#endif