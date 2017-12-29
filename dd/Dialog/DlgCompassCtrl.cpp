#include "stdafx.h"
#include "../dd.h"
#include "DlgCompassCtrl.h"

//////////////////////////////////////////////////////////////////////////
//
DECLARE_MESSAGE(CPM_SET_ANGLE)
IMPLEMENT_DYNAMIC(CDlgCompassCtrl, CDialogSK)

CDlgCompassCtrl::CDlgCompassCtrl(CWnd* pParent /*=NULL*/)
	: CDialogSK(CDlgCompassCtrl::IDD, pParent)
{

}

CDlgCompassCtrl::~CDlgCompassCtrl()
{
}

void CDlgCompassCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogSK::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPASS, m_Compass);
}

BEGIN_MESSAGE_MAP(CDlgCompassCtrl, CDialogSK)
	ON_WM_PAINT()
	ON_REGISTERED_MESSAGE(CPM_SET_ANGLE,		OnCompassChange)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////
//
BOOL CDlgCompassCtrl::OnInitDialog()
{
	CDialogSK::OnInitDialog();

	if (!InitCtrl())
	{
		return FALSE;
	}

	if (!InitInfo())
	{
		return FALSE;
	}
;
	return TRUE; 
}

BOOL CDlgCompassCtrl::PreTranslateMessage(MSG* pMsg)
{
	return CDialogSK::PreTranslateMessage(pMsg);
}

void CDlgCompassCtrl::OnPaint()
{
	CPaintDC dc(this); 
}

LRESULT CDlgCompassCtrl::OnCompassChange(WPARAM wParam, LPARAM lParam)
{
	double angle = GeometricToGeographic(RadiansToDegrees(atan2((double)lParam, (double)(int)wParam)));
	if(angle < 0)
	{
		angle = 360 + angle;
	}

	m_Compass.SetAngle(angle);
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//
BOOL CDlgCompassCtrl::InitCtrl()
{
	CRect rcClient;
	GetClientRect(&rcClient);

	if (!InitWndSkin())
	{
		return FALSE;
	}

	if (!CreateChildWnd())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDlgCompassCtrl::InitInfo()
{
	return TRUE;
}

BOOL CDlgCompassCtrl::InitWndSkin()
{
	EnableEasyMove(FALSE);
	SetStyle(LO_DEFAULT);
	SetBitmap("D:\\background.bmp");	//IDB_BITMAP_BKGND	//"D:\\background.bmp"

	return TRUE;
}

BOOL CDlgCompassCtrl::CreateChildWnd()
{
	//m_Compass.SubclassDlgItem(IDC_COMPASS, this);
	m_Compass.EnableWindow(TRUE);
	m_Compass.SetShow(TRUE);

	return TRUE;
}