#pragma once

class CStackedWndCtrl : public CStatic
{
public:
	CStackedWndCtrl();
	virtual ~CStackedWndCtrl();
	
protected:
	DECLARE_MESSAGE_MAP()
	virtual void 			PreSubclassWindow();
	afx_msg void 			OnSize(UINT nType, int cx, int cy);
	
public:
	BOOL					AddPane(CWnd* pWndItem, CWnd* pParentWnd);
	BOOL					ShowPane();
};