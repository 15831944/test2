#if !defined(AFX_PAGE2_H__CF6F6B5E_A39E_45CE_9E60_53B5A89CF8AE__INCLUDED_)
#define AFX_PAGE2_H__CF6F6B5E_A39E_45CE_9E60_53B5A89CF8AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Page.h"
#include "../Inc/String.h"
#include "../Inc/Console.h"

using namespace Leaf::String;
using namespace Leaf::Console;
using namespace std;
class CPage2 : public CPage
{ 
public:
	CPage2(CWnd* pParent = NULL); 
	virtual ~CPage2(void);

public:
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void				DoDataExchange(CDataExchange* pDX);
	virtual BOOL				OnInitDialog();
	afx_msg void				OnTimer(UINT nIDEvent);
	afx_msg void				OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

	afx_msg void				OnButton1();
	afx_msg void				OnButton2();
	afx_msg void				OnButton3();
	afx_msg void				OnButton4();
	afx_msg void				OnButton5();
	afx_msg void				OnButton6();
	afx_msg void				OnButton8();
	afx_msg void				OnButton7();
	afx_msg void				OnButton9();
	afx_msg void				OnButton10();
	afx_msg void				OnButton11();
	afx_msg void				OnButton12();
	afx_msg void				OnButton13();
	DECLARE_MESSAGE_MAP()

protected:
//	AString			m_Test;
//	void			DrawBK();
//	BOOL			CheckPE();
/*	CString			Tokenize(CString strSrc, CString strSeparator, int& nPos);*/

// 	bool			GetXmlDeclare(string szFileName, string &szVersion, string &szStandalone, string &szEncoding);
// 	bool			GetXmlNodeObj(TiXmlElement* RootElement, string &szNodeName, TiXmlElement* pNodeElement);
// 	bool			ReadXmlFile(string& szFileName);

	
// private:	 
// 	int					m_nFlag;
// 	CBitmap				m_hbitmap;
// 	HWND				m_hViewer;
};

#endif
