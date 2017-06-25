#if !defined(AFX_RANDOMFXSTATIC_H__159B4606_20C9_47AC_B2E0_4812A44720D9__INCLUDED_)
#define AFX_RANDOMFXSTATIC_H__159B4606_20C9_47AC_B2E0_4812A44720D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RandomFXStatic.h : header file
//

#include "CoolFXStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CRandomFXStatic window

class CRandomFXStatic : public CCoolFXStatic
{
// Construction
public:
	CRandomFXStatic(BOOL alwaysAnimate = FALSE);

public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRandomFXStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CRandomFXStatic();

public:
	static int GetHighestSetBit(int num);

protected:
	BOOL alwaysAnimate;
	virtual void InitFX(HBITMAP hBitmap);

	// Generated message map functions
protected:
	//{{AFX_MSG(CRandomFXStatic)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RANDOMFXSTATIC_H__159B4606_20C9_47AC_B2E0_4812A44720D9__INCLUDED_)
