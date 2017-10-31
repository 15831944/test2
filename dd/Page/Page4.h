#if !defined(AFX_PAGE4_H__7F5FB35B_0D3C_4E14_9627_8B5CF84C572F__INCLUDED_)
#define AFX_PAGE4_H__7F5FB35B_0D3C_4E14_9627_8B5CF84C572F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Page.h"
class CPage4 : public CPage
{
public:
	CPage4(CWnd* pParent = NULL);   


public:
	enum { IDD = IDD_DIALOG4 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);   
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()	
};

#endif 
