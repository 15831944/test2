#ifndef __SCROLLWNDMSG_H__
#define __SCROLLWNDMSG_H__

class CScrollWndMsg : CWnd
{
public:
	CScrollWndMsg();
	~CScrollWndMsg();

public:
	BOOL					Create(DWORD dwStyle, const CRect &pWndRect, CWnd* pParent, UINT nWndId);

	void					SetFont(int nSize, LPCTSTR lpszFaceName);
	void					SetWndText(LPCTSTR lpszWndText, COLORREF color = NULL);
	void					SetWndTipText(LPCTSTR lpszWndTipText, COLORREF color = NULL);
	void					SetWndBorder(BOOL bWndBorder, COLORREF color = NULL);
	
	void					SetWndBkColor(COLORREF color = NULL);
	void					SetTextColor(COLORREF crNormalText, COLORREF crSelText);
	void					SetSelColor(COLORREF crSelBorder, COLORREF crSelFill);
	void					SetHoverColor(COLORREF crHoverBorder, COLORREF crHoverFill);
	
	void					SetScrollPause();
	void					SetScrollSpeed(DWORD dwSpan);
	void					SetScrollShowPos(DWORD dx, DWORD dy);
	void					ClearScrollText();
	
protected:
	//static BOOL				hasclass;
	//static BOOL				RegisterWindowClass();
	
protected:
	//virtual BOOL 			PreTranslateMessage(MSG* pMsg);
	afx_msg void 			OnPaint();
	afx_msg BOOL			OnEraseBkgnd(CDC* pDC);
	afx_msg void 			OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()
	
protected:
	UINT					m_nWndId;
	DWORD					m_dwStyple;
	
	CDC 					m_BkMemDC;
	CBitmap*				m_pBkBitmap;
	CFont 					m_cFont;
	
#pragma pack(1)
	typedef struct _STRUCT_ICONS
	{
		HICON		hIcon;
		DWORD		dwWidth;
		DWORD		dwHeight;
	}STRUCT_ICONS;
#pragma pack()
	STRUCT_ICONS			m_csIcons[2];
	
private:
	BOOL					m_bBorder;
	BOOL					m_bBkBitmap;	
	BOOL 					m_bWndBorder;	
	
	COLORREF				m_crWndBk;
	COLORREF				m_crWndBorder;	
	COLORREF				m_crNormalText;	
	COLORREF				m_crSelText;
	COLORREF				m_crHoverText;
	COLORREF				m_crDisableText;
	
	COLORREF				m_crSelBorder;
	COLORREF				m_crSelFill;
	
	COLORREF				m_crHoverBorder;
	COLORREF				m_crHoverFill;
};

#endif