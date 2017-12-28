#if !defined(AFX_DDDLG_H__0A0ED49C_4E34_4FD4_A624_4CCEE2BA4D21__INCLUDED_)
#define AFX_DDDLG_H__0A0ED49C_4E34_4FD4_A624_4CCEE2BA4D21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "Page/Page1.h"
#include "Page/Page2.h"
#include "Page/Page3.h"
#include "Page/Page4.h"

#include "Control/CButton/xSkinButton.h"
#include "Control/CWnd/dialogheader.h"

#include "./Inc/common/ETSLayout.h"
#include "./Inc/common/ResizeCtrl.h"
#include "./Inc/common/ResizableDialog.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////
//
class CDdDlg : public CDialog
{
public:
	CDdDlg(CWnd* pParent = NULL);	

public:
	enum { IDD = IDD_DD_DIALOG };
	CxSkinButton				m_Btn1;
	CxSkinButton				m_Btn2;
	CxSkinButton				m_Btn3;
	CxSkinButton				m_Btn4;

public:
	virtual BOOL				PreTranslateMessage(MSG* pMsg);

protected:
	virtual void				DoDataExchange(CDataExchange* pDX);	

protected:
	HICON						m_hIcon;

	virtual BOOL				OnInitDialog();
	afx_msg void				OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void				OnPaint();
	afx_msg HCURSOR				OnQueryDragIcon();

	afx_msg void				OnSize(UINT nType, int cx, int cy);
	afx_msg void				OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT				OnNcHitTest(CPoint point);

	afx_msg void				OnButton1();
	afx_msg void				OnButton2();
	afx_msg void				OnButton3();
	afx_msg void				OnButton4();
	DECLARE_MESSAGE_MAP()

protected:
	void						Init();
	void						InitCtrl();
	void						InitInfo();

	void						InitDlgHeader();
	void						InitSubDlg();

	void						DrawTitle(CDC* pDC);
	void						ShowSubDlg(int nIndex, LPCTSTR szTitle);
protected:
	CDialogHeader				m_HeaderCtrl;
 	CPage1						m_Page1;
	CPage2						m_Page2;
 	CPage3						m_Page3;
	CPage4						m_Page4;

private:
	CRect						m_rcPage;
	CRect						m_rcCaption;
	
	CPtrArray					m_pArPage;
	int							m_nPrevPage;
	int							m_nCaption;
};

#endif 
