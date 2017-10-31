#pragma once

#include "../Control/CWnd/OutPutWndCtrl.h"
class CDlgPreViewCtrl : public CDialog
{
	DECLARE_DYNAMIC(CDlgPreViewCtrl)
public:
	CDlgPreViewCtrl(CWnd* pParent = NULL);  
	virtual ~CDlgPreViewCtrl();

	int							GetViewerNums()		{ return m_nCurWndNum; }
	
public:
	enum { IDD = IDD_PREVIEW_DIALOG };

protected:
	virtual void				DoDataExchange(CDataExchange* pDX);   
	virtual BOOL				OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg	LRESULT				OnSwitchMultiWnd(WPARAM wParam, LPARAM lParam);
	
protected:
	BOOL						Init();
	BOOL						InitCtrl();
	BOOL						InitInfo();

	void						ArrangeOutputs(int nNumber);

protected:
	COutPutWndCtrl				m_dlgOutPut[MAX_OUTPUTS_CTRL];

private:
	CRect						m_rcPreviewBG;

	int							m_nCurScreenWidth;
	int							m_nCurScreenHeight;

	int							m_nCurWndNum;
	int							m_nCurWndIndex;
};
