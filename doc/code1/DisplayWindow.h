#ifndef __DISPLAYWINDOW_H__
#define __DISPLAYWINDOW_H__

class CDisplayWindow : public CWnd
{
public:
	CDisplayWindow();
	virtual ~CDisplayWindow();
	
public:	
	BOOL						Create(CWnd* pParent, LPCTSTR lpszTitle);
	
public:
	//{{AFX_VIRTUAL(CDisplayWindow)
	virtual BOOL 				DestroyWindow();
	//}}AFX_VIRTUAL
	
protected:
	//{{AFX_MSG(CDisplayWindow)
	afx_msg void				OnPaint();
	afx_msg BOOL				OnEraseBkgnd(CDC* pDC);
	afx_msg void				OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void				OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void				OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void 				OnCancel();
	afx_msg void 				OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	
public:
	void						SetWndBorder(BOOL bWndBorder, COLORREF clrWndBorder);	
	void						SetWndBkColor(COLORREF clrWndBk);
	void						SetHoverColor(COLORREF clrHoverBorder, COLORREF clrHoverFill);
	void						SetSelColor(COLORREF clrSelBorder, COLORREF clrSelFill);
	
	void						SetBkBmp(LPCTSTR lpBitmapName);
	void						SetBkBmp(UINT nIDBmp);
	
private:
	BOOL						m_bWndSel;
	BOOL						m_bWndBorder;
	BOOL						m_bWndHover;	
	BOOL						m_bWndBkBmp;
	
	CBitmap*					m_pBkBmp;
	
	COLORREF					m_clrWndBorder;
	COLORREF					m_clrWndBk;

	COLORREF					m_clrHoverBorder;
	COLORREF					m_clrHoverFill;

	COLORREF					m_clrSelBorder;
	COLORREF					m_clrSelFill;
};
#endif