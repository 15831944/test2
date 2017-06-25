#if !defined(AFX_PAGE3_H__0FC0F890_432C_403F_8643_CE5CCB2AFCAA__INCLUDED_)
#define AFX_PAGE3_H__0FC0F890_432C_403F_8643_CE5CCB2AFCAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Page.h"

class CPage3 : public CPage
{
public:
	CPage3(CWnd* pParent = NULL);    
	void DisplayCodeInfo();

public:
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
};

#endif 
