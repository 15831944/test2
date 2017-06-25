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
	BOOL						m_bWndSel;						//�����Ƿ�ѡ�п���
	BOOL						m_bWndBorder;					//���ڱ߿�״̬����
	BOOL						m_bWndHover;					//��������Ƿ��ƶ�����	
	BOOL						m_bWndBkBmp;					//���ڱ�������
	BOOL						m_bWndMultiScreen;				//�����Ƿ�ȫ������

	CBitmap*					m_pBkBmp;

	COLORREF					m_clrWndBorder;					//���ڱ߿���ɫ
	COLORREF					m_clrWndBk;						

	COLORREF					m_clrHoverBorder;				//��������ƶ����ı߿���ɫ
	COLORREF					m_clrHoverFill;					//��������ƶ��������ɫ

	COLORREF					m_clrSelBorder;					//����ѡ��ı߿���ɫ	
	COLORREF					m_clrSelFill;					//����ѡ��������ɫ

	DWORD						m_dwChannel;					//���ڵ�ͨ�����
	int							m_nCurWndNum;						
};
