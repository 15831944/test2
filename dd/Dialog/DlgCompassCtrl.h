#pragma once

#include "../Control/CWnd/CDialogSK.h"
#include "../Control/CWnd/Compass.h"

class CDlgCompassCtrl : public CDialogSK
{
	DECLARE_DYNAMIC(CDlgCompassCtrl)
public:
	CDlgCompassCtrl(CWnd* pParent = NULL);  
	virtual ~CDlgCompassCtrl();

public:
	enum { IDD = IDD_COMPASS_DIALOG };

protected:
	virtual void						DoDataExchange(CDataExchange* pDX);    
	virtual BOOL						PreTranslateMessage(MSG* pMsg);
	virtual BOOL						OnInitDialog();

	afx_msg void 						OnPaint();
	DECLARE_MESSAGE_MAP()	

	afx_msg LRESULT						OnCompassChange(WPARAM, LPARAM);

protected:
	BOOL								InitCtrl();
	BOOL								InitInfo();

	BOOL								CreateChildWnd();
	BOOL								InitWndSkin();

protected:
	Compass								m_Compass;
};
