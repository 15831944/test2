#pragma once

#define	MAX_OUTPUTS_CTRL		64
#define	OUTPUT_INTERVAL			4

#define	WM_SWITCHMULTI_CTRL		WM_USER + 0x0101

typedef enum tagWndType{
	M_EMPTYTYPE					= 0,
	M_FULLSCREEN_CTRL			= 1,
	M_MULTISCREEN_CTRL			= 2
}UKH_WND_TYPE;

class COutPutWndCtrl : public CWnd
{
public:
	COutPutWndCtrl();  
	virtual ~COutPutWndCtrl();

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

	void						SetWndChannel(DWORD dwChannel);
	DWORD						GetWndChannel();

	void						SetMultiScreen(BOOL bFlag);

	void						SetWndBorder(BOOL bWndBorder, COLORREF clrWndBorder);
	void						SetWndBkColor(COLORREF clrWndBk);	
	
	void						SetHoverColor(COLORREF clrHoverBorder, COLORREF clrHoverFill);
	void						SetSelColor(COLORREF clrSelBorder, COLORREF clrSelFill);

	void						SetBkBmp(LPCTSTR lpBitmapName);
	void						SetBkBmp(UINT nIDBmp);

private:
	BOOL						m_bShowing;

	BOOL						m_bWndSel;						//�����Ƿ�ѡ�п���
	BOOL						m_bWndBorder;					//���ڱ߿�״̬����
	BOOL						m_bWndHover;					//��������Ƿ��ƶ�����	
	BOOL						m_bWndBkBmp;					//���ڱ�������
	BOOL						m_bWndMultiScreen;				//�����Ƿ�ȫ������

	CBitmap*					m_pBkBmp;
	CWnd*						m_pParentWnd;

	COLORREF					m_clrWndBorder;					//���ڱ߿���ɫ
	COLORREF					m_clrWndBk;						

	COLORREF					m_clrHoverBorder;				//��������ƶ����ı߿���ɫ
	COLORREF					m_clrHoverFill;					//��������ƶ��������ɫ

	COLORREF					m_clrSelBorder;					//����ѡ��ı߿���ɫ	
	COLORREF					m_clrSelFill;					//����ѡ��������ɫ

	DWORD						m_dwWndId;	
	DWORD						m_dwHoverRet;

	DWORD						m_dwChannel;					//���ڵ�ͨ�����
	int							m_nCurWndNum;					//		
};
