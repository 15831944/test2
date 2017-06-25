#if !defined(AFX_CUSTOMEDIT_H__24A93EB1_4947_4CD8_B2D8_B0AB08490E9C__INCLUDED_)
#define AFX_CUSTOMEDIT_H__24A93EB1_4947_4CD8_B2D8_B0AB08490E9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCustomEdit window

class CCustomEdit : public CEdit
{
// Construction
public:
	CCustomEdit();
	virtual ~CCustomEdit();
// Attributes
public:
	void				SetCurIcon(HICON hIcon, BOOL redraw=TRUE);
	void				SetCurIcon(UINT id,BOOL redraw=TRUE);

	void				SetCurText(LPCTSTR szText,BOOL redraw=TRUE);
	void				SetCurText(CString strText,BOOL redraw=TRUE);

	void				SetCurFont(const LOGFONT* lpLogFont, BOOL redraw=TRUE);
	void				SetCurFont(CFont& font, BOOL redraw=TRUE);
// Operations
public:

protected:
	void				RecalcLayout();
	void				DestroyIcon();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCustomEdit)
	protected:
	virtual void		PreSubclassWindow();
	//}}AFX_VIRTUAL
	// Generated message map functions
protected:
	//{{AFX_MSG(CCustomEdit)
	afx_msg void		OnPaint();
	afx_msg void		OnSize(UINT nType, int cx, int cy);
	afx_msg HBRUSH		OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	afx_msg LRESULT		OnSetFont(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
private:
	BOOL				m_bIcon;
	CFont				m_font;
	HICON				m_hIcon;
	CString				m_strText;
	COLORREF			m_colText;
	COLORREF			m_Colour;  //±ß¿òÑÕÉ«
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CUSTOMEDIT_H__24A93EB1_4947_4CD8_B2D8_B0AB08490E9C__INCLUDED_)
