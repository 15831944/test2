#pragma once

#include "../Control/CWnd/Compass.h"
class CDlgCompassCtrl : public CDialog
{
	DECLARE_DYNAMIC(CDlgCompassCtrl)
public:
	CDlgCompassCtrl(CWnd* pParent = NULL);  
	virtual ~CDlgCompassCtrl();

public:
	enum { IDD = IDD_COMPASS_DIALOG };

protected:
	Compass								m_Compass;

	virtual void						DoDataExchange(CDataExchange* pDX);    
	virtual BOOL						PreTranslateMessage(MSG* pMsg);
	virtual BOOL						OnInitDialog();
	afx_msg void 						OnPaint();
	DECLARE_MESSAGE_MAP()	

	afx_msg LRESULT						OnCompassChange(WPARAM, LPARAM);
};
