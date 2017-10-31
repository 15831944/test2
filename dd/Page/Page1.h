#if !defined(AFX_PAGE1_H__487EE8D3_6F79_48C8_9D3F_65A46CF7F6F5__INCLUDED_)
#define AFX_PAGE1_H__487EE8D3_6F79_48C8_9D3F_65A46CF7F6F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Page.h"
#include "../Control/CStatic/CoolFXStatic.h"

using namespace Leaf::IO;
class CPage1 : public CPage
{
public:
	CPage1(CWnd* pParent = NULL); 
	~CPage1();

public:
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void					DoDataExchange(CDataExchange* pDX);    
	virtual BOOL					OnInitDialog();
	DECLARE_MESSAGE_MAP()

protected:
	void							Init();
	void							InitCtrl();
	void							InitInfo();

protected:
	CBitmap							m_hPictureBitmap;
	CCoolFXStatic					m_hPictureRuntime;
};

#endif 
