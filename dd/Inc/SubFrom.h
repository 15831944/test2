// SubFrom.h: interface for the CSubFrom class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUBFROM_H__0CFBA5B7_82AF_417F_A635_0390AC7C3133__INCLUDED_)
#define AFX_SUBFROM_H__0CFBA5B7_82AF_417F_A635_0390AC7C3133__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxtempl.h>

class CSubFrom  
{
public:
	CSubFrom();
	virtual ~CSubFrom();

public:
	bool CreateSubForm(UINT id,CWnd* pParentWnd);
	bool ShowSubForm(int ix = -1);
	bool SetActive(int ix);
	void SetPosRect(const CRect& rect);
protected:
	 CArray<CDialog*, CDialog*> m_Forms;
	 int   m_nActiveForm;
	 CRect m_Rect; 
	 bool m_bPos;
	 int   AddForm(CDialog* dlg);
};

#endif // !defined(AFX_SUBFROM_H__0CFBA5B7_82AF_417F_A635_0390AC7C3133__INCLUDED_)
