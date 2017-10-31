#include "stdafx.h"
#include "../dd.h"
#include "Page1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPage1::CPage1(CWnd* pParent /*=NULL*/)
	: CPage(CPage1::IDD, pParent)
{
}

CPage1::~CPage1()
{
}

void CPage1::DoDataExchange(CDataExchange* pDX)
{
	CPage::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPage1, CPage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// 
BOOL CPage1::OnInitDialog() 
{
	CDialog::OnInitDialog();
	Init();

	return TRUE; 
}

void CPage1::Init()
{
	InitInfo();
	InitCtrl();
}

void CPage1::InitCtrl()
{
	RECT ctrlRect = { 0 };
	this->GetWindowRect(&ctrlRect);
	ScreenToClient(&ctrlRect);

	m_hPictureRuntime.Create(_T(""), WS_CHILD | WS_VISIBLE, ctrlRect, this);
	m_hPictureBitmap.LoadBitmap(IDB_BITMAP_PAGE);
	m_hPictureRuntime.SetBitmap(m_hPictureBitmap);

	m_hPictureRuntime.intervalsPerRaindrop = 5;
	m_hPictureRuntime.SetFireAlpha(30);
	m_hPictureRuntime.SetPlasmaAlpha(30);
}


void CPage1::InitInfo()
{
	int renderWhich = 0;

	renderWhich = m_hPictureRuntime.GetRender();
	m_hPictureRuntime.SetRender(renderWhich |= CCoolFXStatic::RenderWater);
//	m_hPictureRuntime.SetRender(renderWhich |= CCoolFXStatic::RenderFire);
//	m_hPictureRuntime.SetRender(renderWhich |= CCoolFXStatic::RenderPlasma);

	m_hPictureRuntime.StartAnimation();
}
