#pragma once

class CToolbarWndCtrl : public CWnd
{
public:
	CToolbarWndCtrl();
	virtual ~CToolbarWndCtrl();
	
protected:
	virtual BOOL				PreTranslateMessage(MSG* pMsg);

	afx_msg void				OnSize(UINT nType, int cx, int cy);
	afx_msg void				OnPaint();
	afx_msg BOOL				OnEraseBkgnd(CDC* pDC);
	afx_msg void				OnShowWindow(BOOL bShow, UINT nStatus);
	
	afx_msg void				OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void				OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void				OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void				OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	BOOL						Create(DWORD dwStyle, const CRect &pWndRect, CWnd* pParent, UINT nWndId);

	void						SetWndBkColor(COLORREF color = NULL);
	void						SetWndBkBitmap(UINT nIDBitmap);
	void						SetWndBkBitmap(LPCTSTR lpBitmapName);
	void						SetWndBorder(BOOL bWndBorder, COLORREF color = NULL);

	void						SetFont(int nHeight, LPCTSTR lpszFaceName);
	void						SetWndText(LPCTSTR lpszWndText, CONST RECT *lprcText = NULL, COLORREF color = NULL);
	void						SetTextColor(COLORREF clrNormalText, COLORREF clrSelText);
	void						SetWndTipText(LPCTSTR lpszWndTipText, COLORREF color = NULL);

	void						SetSelColor(COLORREF clrSelBorder, COLORREF clrSelFill);
	void						SetHoverColor(COLORREF clrHoverBorder, COLORREF clrHoverFill);

protected:
	UINT						m_nWndId;
	UINT						m_nTimer;

	DWORD						m_dwStyple;
	DWORD						m_dwHoverRet;

	CBitmap*					m_pBkBitmap;
	CFont*						m_pFont;

	CRect						m_rcText;
	
private:
	BOOL						m_bInited;
	BOOL						m_bRefreshSkin;
	BOOL						m_bRefreshText;

	BOOL						m_bWndSel;
	BOOL 						m_bWndBorder;
	BOOL						m_bWndHover;
	BOOL						m_bBkBitmap;
	
	CString						m_strWndText;
	CString						m_strWndTipText;

	COLORREF					m_clrWndBk;
	COLORREF					m_clrWndBorder;

	COLORREF					m_clrNormalText;	
	COLORREF					m_clrWndTipText;

	COLORREF					m_clrSelText;
	COLORREF					m_clrHoverText;
	COLORREF					m_clrDisableText;

	COLORREF					m_clrSelBorder;
	COLORREF					m_clrSelFill;

	COLORREF					m_clrHoverBorder;
	COLORREF					m_clrHoverFill;
};