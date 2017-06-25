#include "stdafx.h"
#include "../dd.h"
#include "DlgCompassCtrl.h"


DECLARE_MESSAGE(CPM_SET_ANGLE)
IMPLEMENT_DYNAMIC(CDlgCompassCtrl, CDialog)
CDlgCompassCtrl::CDlgCompassCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCompassCtrl::IDD, pParent)
{

}

CDlgCompassCtrl::~CDlgCompassCtrl()
{
}

void CDlgCompassCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMPASS, m_Compass);
}

BEGIN_MESSAGE_MAP(CDlgCompassCtrl, CDialog)
	ON_WM_PAINT()
	ON_REGISTERED_MESSAGE(CPM_SET_ANGLE, OnCompassChange)
END_MESSAGE_MAP()


BOOL CDlgCompassCtrl::OnInitDialog()
{
	CDialog::OnInitDialog();

//	m_Compass.SubclassDlgItem(IDC_COMPASS, this);
	m_Compass.EnableWindow(TRUE);
	m_Compass.SetShow(TRUE);
	return TRUE; 
}

BOOL CDlgCompassCtrl::PreTranslateMessage(MSG* pMsg)
{
	return CDialog::PreTranslateMessage(pMsg);
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