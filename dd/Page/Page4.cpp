#include "stdafx.h"
#include "../dd.h"
#include "Page4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPage4::CPage4(CWnd* pParent /*=NULL*/)
	: CPage(CPage4::IDD, pParent)
{
}


void CPage4::DoDataExchange(CDataExchange* pDX)
{
	CPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage4, CPage)
END_MESSAGE_MAP()

BOOL CPage4::OnInitDialog() 
{
	CDialog::OnInitDialog();

	return TRUE; 
}
