#if !defined(AFX_PAGE_H__071D7AFC_E3DB_4D17_A646_BAB3E6D3B059__INCLUDED_)
#define AFX_PAGE_H__071D7AFC_E3DB_4D17_A646_BAB3E6D3B059__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../Inc/MemDC.h"

class CPage : public CDialog
{
public:
	CPage(UINT nIDTemplate,CWnd* pParent = NULL);   

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

private:
	CBrush m_brush;
};

#endif 
