#pragma once

class CDlgOutPutCtrl : public CDialog
{
	DECLARE_DYNAMIC(CDlgOutPutCtrl)
public:
	CDlgOutPutCtrl(CWnd* pParent = NULL);  
	virtual ~CDlgOutPutCtrl();

	void						SetWndChannel(DWORD dwChannel);
	DWORD						GetWndChannel();

	void						SetMultiScreen(BOOL bFlag);
public:
	enum { IDD = IDD_OUTPUT_DIALOG };

protected:
	virtual void				DoDataExchange(CDataExchange* pDX);   
	virtual BOOL				OnInitDialog();
	afx_msg void				OnPaint();
	afx_msg BOOL				OnEraseBkgnd(CDC* pDC);
	afx_msg void				OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void				OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void				OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void				OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	void						SetWndBorder(BOOL bWndBorder, COLORREF clrWndBorder);
	void						SetWndBkColor(COLORREF clrWndBk);	
	
	void						SetHoverColor(COLORREF clrHoverBorder, COLORREF clrHoverFill);
	void						SetSelColor(COLORREF clrSelBorder, COLORREF clrSelFill);

	void						SetBkBmp(LPCTSTR lpBitmapName);
	void						SetBkBmp(UINT nIDBmp);

private:
	BOOL						m_bWndSel;						//窗口是否选中开关
	BOOL						m_bWndBorder;					//窗口边框状态开关
	BOOL						m_bWndHover;					//窗口鼠标是否移动开关	
	BOOL						m_bWndBkBmp;					//窗口背景开关
	BOOL						m_bWndMultiScreen;				//窗口是否全屏开关

	CBitmap*					m_pBkBmp;

	COLORREF					m_clrWndBorder;					//窗口边框颜色
	COLORREF					m_clrWndBk;						

	COLORREF					m_clrHoverBorder;				//窗口鼠标移动过的边框颜色
	COLORREF					m_clrHoverFill;					//窗口鼠标移动过填充颜色

	COLORREF					m_clrSelBorder;					//窗口选择的边框颜色	
	COLORREF					m_clrSelFill;					//窗口选择的填充颜色

	DWORD						m_dwChannel;					//窗口的通道序号
	int							m_nCurWndNum;						
};
