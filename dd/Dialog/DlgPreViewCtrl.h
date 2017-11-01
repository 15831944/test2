#pragma once

#include "../Control/CWnd/OutPutWndCtrl.h"
class CDlgPreViewCtrl : public CDialog
{
	DECLARE_DYNAMIC(CDlgPreViewCtrl)
public:
	CDlgPreViewCtrl(CWnd* pParent = NULL);  
	virtual ~CDlgPreViewCtrl();

public:
	enum { IDD = IDD_PREVIEW_DIALOG };

protected:
	virtual void				DoDataExchange(CDataExchange* pDX);   
	virtual BOOL				OnInitDialog();

	afx_msg int					OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	afx_msg	LRESULT				OnSwitchMultiWnd(WPARAM wParam, LPARAM lParam);
	
protected:
	BOOL						Init();
	BOOL						InitCtrl();
	BOOL						InitInfo();

	BOOL						ArrangeOutputs(UKH_WND_TYPE hWndType, DWORD dwChannels);

protected:
	COutPutWndCtrl*				m_pOutPutArray;

private:
	CRect						m_rcPreviewBG;

	int							m_nCurScreenWidth;
	int							m_nCurScreenHeight;

	DWORD						m_dwOutPutSize;
	DWORD						m_dwOutPutWndIndex;
};
