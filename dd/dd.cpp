#include "stdafx.h"
#include "dd.h"
#include "ddDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDdApp
BEGIN_MESSAGE_MAP(CDdApp, CWinApp)
	//{{AFX_MSG_MAP(CDdApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDdApp construction
CDdApp::CDdApp()
{
}

/////////////////////////////////////////////////////////////////////////////
//
CDdApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CDdApp initialization
BOOL CDdApp::InitInstance()
{
	AfxEnableControlContainer();

 	WNDCLASS wc; 
 	::GetClassInfo(AfxGetInstanceHandle(), _T("#32770"), &wc); 
 	wc.lpszClassName = _T("dd"); 
 	AfxRegisterClass(&wc);

#if (_MSC_VER <= 1200)

#ifdef _AFXDLL
	Enable3dControls();			
#else
	Enable3dControlsStatic();	
#endif

#endif



	CDdDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	return FALSE;
}





















