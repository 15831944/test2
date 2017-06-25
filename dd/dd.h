#if !defined(AFX_DD_H__8B484B86_AA4A_490E_B2F8_2D9BF63D559C__INCLUDED_)
#define AFX_DD_H__8B484B86_AA4A_490E_B2F8_2D9BF63D559C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CDdApp:
class CDdApp : public CWinApp
{ 
public:
	CDdApp();

public:
	//{{AFX_VIRTUAL(CDdApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CDdApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DD_H__8B484B86_AA4A_490E_B2F8_2D9BF63D559C__INCLUDED_)
