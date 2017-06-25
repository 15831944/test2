#pragma once

#include "DlgOutPutCtrl.h"

class CDlgPreViewCtrl : public CDialog
{
	DECLARE_DYNAMIC(CDlgPreViewCtrl)
public:
	CDlgPreViewCtrl(CWnd* pParent = NULL);  
	virtual ~CDlgPreViewCtrl();

	int							GetViewerNums()		{ return m_iCurWndNum; }
	
public:
	enum { IDD = IDD_PREVIEW_DIALOG };

protected:
	virtual void				DoDataExchange(CDataExchange* pDX);   
	virtual BOOL				OnInitDialog();
	DECLARE_MESSAGE_MAP()
	afx_msg	LRESULT				OnSwitchMultiWnd(WPARAM wParam, LPARAM lParam);

	void						Init();
	void						InitCtrl();
	void						InitInfo();

	void						ArrangeOutputs(int iNumber);
protected:
	CDlgOutPutCtrl				m_dlgOutPut[MAX_OUTPUTS_CTRL];

private:
	CRect						m_rectPreviewBG;

	int							m_iCurScreenWidth;
	int							m_iCurScreenHeight;

	int							m_iCurWndNum;
	int							m_iCurWndIndex;
};
