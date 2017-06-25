#pragma once

#include "../Control/CWnd/CalendarCtrl.h"
class CDlgCalendarCtrl : public CDialog
{
	DECLARE_DYNAMIC(CDlgCalendarCtrl)
public:
	CDlgCalendarCtrl(CWnd* pParent = NULL);   
	virtual ~CDlgCalendarCtrl();

public:
	enum { IDD = IDD_CALENDAR_DIALOG };

protected:
	virtual void						DoDataExchange(CDataExchange* pDX);   
	virtual BOOL						PreTranslateMessage(MSG* pMsg);
	virtual void						PostNcDestroy();
	virtual BOOL						OnInitDialog();

	afx_msg void						OnPaint();
	afx_msg void						OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL						OnEraseBkgnd(CDC* pDC);
	afx_msg int							OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

protected:	
	void								ResizeUI();

	static HRESULT CALLBACK				CalendarDataCallback(CCalendarCtrl* pWnd, time_t date);

protected:
	CCalendarCtrl						m_hCalendarCtrl;
};
