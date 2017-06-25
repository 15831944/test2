#include "stdafx.h"
#include "../dd.h"
#include "Page3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPage3::CPage3(CWnd* pParent /*=NULL*/)
	: CPage(CPage3::IDD, pParent)
{
}


void CPage3::DoDataExchange(CDataExchange* pDX)
{
	CPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage3, CPage)
END_MESSAGE_MAP()

BOOL CPage3::OnInitDialog() 
{
	CDialog::OnInitDialog();
	return TRUE; 
}
