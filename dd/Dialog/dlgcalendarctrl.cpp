#include "stdafx.h"
#include "../dd.h"
#include "DlgCalendarCtrl.h"

typedef struct CalendarDataItem
{
	bool bMarked;
	CStringArray csLines;
}CalendarDataItem;

CMapPtrToPtr	g_CalendarData;

IMPLEMENT_DYNAMIC(CDlgCalendarCtrl, CDialog)
CDlgCalendarCtrl::CDlgCalendarCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCalendarCtrl::IDD, pParent)
{

}

CDlgCalendarCtrl::~CDlgCalendarCtrl()
{
	POSITION pos = g_CalendarData.GetStartPosition();	 
	while (pos)
	{
		CalendarDataItem* p; time_t date;
		g_CalendarData.GetNextAssoc(pos, (void*&)date, (void*&)p);
		delete p;
	}
}

void CDlgCalendarCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCalendarCtrl, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

int CDlgCalendarCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
	{
		return -1;
	}

	VERIFY(m_hCalendarCtrl.Create(WS_CHILD|WS_VISIBLE|WS_VSCROLL,
		CRect(0,0,0,0),
		this,
		1, 
		(LPFN_CALENDAR_DATA_CALLBACK)CalendarDataCallback));

	return 0;
}

BOOL CDlgCalendarCtrl::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_hCalendarCtrl.Reset();
	return TRUE; 
}

BOOL CDlgCalendarCtrl::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_ESCAPE||pMsg->wParam==13)
		{
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgCalendarCtrl::OnPaint()
{
	CPaintDC dc(this); 
}

BOOL CDlgCalendarCtrl::OnEraseBkgnd(CDC* pDC) 
{
	if(m_hCalendarCtrl && ::IsWindow(m_hCalendarCtrl.m_hWnd))
	{
		CRect clip;
		m_hCalendarCtrl.GetWindowRect(&clip);
		ScreenToClient(&clip);
		pDC->ExcludeClipRect(&clip);
		pDC->GetClipBox(&clip);
		pDC->FillSolidRect(clip, RGB(255,255,255));
		return FALSE;
	}

	return TRUE;
//	return CDialog::OnEraseBkgnd(pDC);
}

void CDlgCalendarCtrl::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	ResizeUI();
}

void CDlgCalendarCtrl::PostNcDestroy() 
{
//	delete this;
	CDialog::PostNcDestroy();
}

HRESULT CDlgCalendarCtrl::CalendarDataCallback(CCalendarCtrl* pWnd, time_t date)
{
	if(pWnd)
	{ 
		CalendarDataItem* p = NULL;
		if(g_CalendarData.Lookup((void*)date, (void*&)p))
		{
			CCalendarCell* pCell = pWnd->GetCell(date);
			pCell->bMark = p->bMarked;
			pCell->csaLines.Copy(p->csLines);

		}
	}

	return 0;
}

void CDlgCalendarCtrl::ResizeUI()
{
	if(m_hCalendarCtrl && ::IsWindow(m_hCalendarCtrl.m_hWnd))
	{
		CRect rect;
		GetClientRect(rect);
		m_hCalendarCtrl.MoveWindow(rect);
	}
}