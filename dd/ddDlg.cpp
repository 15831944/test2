#include "stdafx.h"
#include "dd.h"
#include "ddDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
  
/////////////////////////////////////////////////////////////////////////////
//
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

public:
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void			DoDataExchange(CDataExchange* pDX);   

protected:
	afx_msg void			OnClose();
	afx_msg void			OnPaint();
	afx_msg void			OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);

	afx_msg void			OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void			OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void			OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

protected:
	CImageList				m_imgDrag;
	BOOL					m_bIsLButtonDown;
	POINT					m_ptOffset,m_ptMove;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	m_bIsLButtonDown	= FALSE;
	m_ptOffset.x		= 0;
	m_ptOffset.y		= 0;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_ACTIVATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

void CAboutDlg::OnPaint() 
{
	CPaintDC dc(this); 
	
	CBitmap		bmBkgnd;
	BITMAP		bmData;
	CDC*		pMemDC = new CDC;

	bmBkgnd.LoadBitmap(IDB_BITMAP_BKGND);
	bmBkgnd.GetBitmap(&bmData);
	pMemDC->CreateCompatibleDC(&dc);

	CBitmap		*pOldBitmap	= pMemDC->SelectObject(&bmBkgnd);
	dc.BitBlt(0, 0, bmData.bmWidth, bmData.bmHeight, pMemDC, 0, 0, SRCCOPY);
	pMemDC->SelectObject(pOldBitmap);

	delete	pMemDC;
}

void CAboutDlg::OnClose() 
{
	CDialog::OnClose();
}


void CAboutDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	CDialog::OnActivate(nState, pWndOther, bMinimized);
	
	if(nState==WA_INACTIVE)
	{
		m_bIsLButtonDown	= FALSE;
		
		CImageList::DragLeave(this);
		CImageList::EndDrag();
		ReleaseCapture();
	}
}

void CAboutDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect	rectPic;
	POINT	ptPut 	= point;
	
	GetDlgItem(IDC_STATIC_PIG)->GetWindowRect(&rectPic);
	ClientToScreen(&ptPut);
	if(rectPic.PtInRect(ptPut))
	{
		CBitmap		bitmapTemp, *pOldBitmap;
		CDC			*pDC	= GetDlgItem(IDC_STATIC_PIG)->GetDC(),
					*pMemDC	= new CDC;
		
		//创建位图内存
		bitmapTemp.CreateCompatibleBitmap(pDC, rectPic.Width(), rectPic.Height());
		pMemDC->CreateCompatibleDC(pDC);
		pOldBitmap	= pMemDC->SelectObject(&bitmapTemp);
		pMemDC->BitBlt(0, 0, rectPic.Width(), rectPic.Height(), pDC, 0, 0, SRCCOPY);
		pMemDC->SelectObject(pOldBitmap);
		delete	pMemDC;
		ReleaseDC(pDC);
		
		m_bIsLButtonDown	= TRUE;
		
		m_ptOffset.x	= ptPut.x-rectPic.left;
		m_ptOffset.y	= ptPut.y-rectPic.top;
		
		
		
		m_imgDrag.DeleteImageList();
		m_imgDrag.Create(rectPic.Width(), rectPic.Height(), ILC_COLOR32|ILC_MASK, 0, 1);
		m_imgDrag.Add(&bitmapTemp, RGB(0, 0, 0));
		m_imgDrag.BeginDrag(0, m_ptOffset);
		m_imgDrag.DragEnter(NULL, ptPut);
		
		SetCapture();
	}

	CDialog::OnLButtonDown(nFlags, point);
}

void CAboutDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if(m_bIsLButtonDown)
	{
		CRect	rectPic;
		CWnd*	pPic	= GetDlgItem(IDC_STATIC_PIG);
		
		ScreenToClient(&m_ptMove);
		pPic->GetWindowRect(rectPic);
		pPic->MoveWindow(m_ptMove.x-m_ptOffset.x, m_ptMove.y-m_ptOffset.y, rectPic.Width(), rectPic.Height());
		m_bIsLButtonDown	= FALSE;
		
		CImageList::DragLeave(this);
		CImageList::EndDrag();
		ReleaseCapture();
		pPic->Invalidate();
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CAboutDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_bIsLButtonDown)
	{
		CRect		rtClient, rtPicture;
		
		m_ptMove	= point;
		
		GetDlgItem(IDC_STATIC_PIG)->GetWindowRect(rtPicture);
		GetClientRect(rtClient);
		ClientToScreen(&rtClient);
		ClientToScreen(&m_ptMove);
		if(rtClient.left>m_ptMove.x-m_ptOffset.x)
			m_ptMove.x	= rtClient.left+m_ptOffset.x;
		if(rtClient.top>m_ptMove.y-m_ptOffset.y)
			m_ptMove.y	= rtClient.top+m_ptOffset.y;
		if(rtClient.right-rtPicture.Width()<m_ptMove.x-m_ptOffset.x)
			m_ptMove.x	= rtClient.right-rtPicture.Width()+m_ptOffset.x;
		if(rtClient.bottom-rtPicture.Height()<m_ptMove.y-m_ptOffset.y)
			m_ptMove.y	= rtClient.bottom-rtPicture.Height()+m_ptOffset.y;
		
		CImageList::DragMove(m_ptMove);
	}
	CDialog::OnMouseMove(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CDdDlg dialog
CDdDlg::CDdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDdDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nPrevPage  = -1;
	m_nCaption   = 24;
}

void CDdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON1, m_Btn1);
	DDX_Control(pDX, IDC_BUTTON2, m_Btn2);
	DDX_Control(pDX, IDC_BUTTON3, m_Btn3);
	DDX_Control(pDX, IDC_BUTTON4, m_Btn4);
}

BEGIN_MESSAGE_MAP(CDdDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()

	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDdDlg message handlers
BOOL CDdDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	Init();

//	ModifyStyle(0, WS_CLIPCHILDREN);
	return TRUE; 
}

BOOL CDdDlg::PreTranslateMessage(MSG* pMsg) 
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

void CDdDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CDdDlg::OnPaint() 
{
	CPaintDC dc(this);  
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
//		CBrush brhBorder(RGB(255, 0, 0));
//		dc.FrameRect(&m_rcInfo,&brhBorder);
		DrawTitle(&dc);
		CDialog::OnPaint();
	}
}

HCURSOR CDdDlg::OnQueryDragIcon()
{
	return CDialog::OnQueryDragIcon();
}

void CDdDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
}

LRESULT CDdDlg::OnNcHitTest(CPoint point)
{
	CRect rcClient;
	GetClientRect(&rcClient);
	ClientToScreen(&rcClient);

	return rcClient.PtInRect(point) ? HTCAPTION : CDialog::OnNcHitTest(point);    //无标题拖动
	return CDialog::OnNcHitTest(point);
}


void CDdDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x, point.y));     //无标题拖动
	CDialog::OnMButtonDown(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////
//
void CDdDlg::Init()
{
	InitCtrl();
	InitInfo();
}

void CDdDlg::InitCtrl()
{
	InitDlgHeader();
	InitSubDlg();
}

void CDdDlg::InitDlgHeader()
{

	m_HeaderCtrl.SetTitleText(_T("This is a Test!"));
	m_HeaderCtrl.SetDescText(_T("This is a Test! lysgwl@163.com"));
	m_HeaderCtrl.SetIconHandle(AfxGetApp()->LoadIcon(IDR_MAINFRAME));
	m_HeaderCtrl.SetBMPRes(IDB_HEADER_BAR);

	m_HeaderCtrl.Init(this);
	m_HeaderCtrl.MoveCtrls(this);
}

void CDdDlg::InitSubDlg()
{
	m_Btn1.SetToolTipText(_T("这是按钮一"));
	m_Btn1.SetSkin(IDB_BITMAP1,IDB_BITMAP2,IDB_BITMAP3,IDB_BITMAP4,IDB_BITMAP5,NULL,0,0,0);
	m_Btn1.SizeToContent();

	m_Btn2.SetToolTipText(_T("这是按钮二"));
	m_Btn2.SetSkin(IDB_BITMAP1,IDB_BITMAP2,IDB_BITMAP3,IDB_BITMAP4,IDB_BITMAP5,NULL,0,0,0);
	m_Btn2.SizeToContent();

	m_Btn3.SetToolTipText(_T("这是按钮三"));
	m_Btn3.SetSkin(IDB_BITMAP1,IDB_BITMAP2,IDB_BITMAP3,IDB_BITMAP4,IDB_BITMAP5,NULL,0,0,0);
	m_Btn3.SizeToContent();

	m_Btn4.SetToolTipText(_T("这是按钮四"));
	m_Btn4.SetSkin(IDB_BITMAP1,IDB_BITMAP2,IDB_BITMAP3,IDB_BITMAP4,IDB_BITMAP5,NULL,0,0,0);
	m_Btn4.SizeToContent();

	m_Page1.Create(IDD_DIALOG1,GetDlgItem(IDC_STATIC_DIALOG));
 	m_Page2.Create(IDD_DIALOG2,GetDlgItem(IDC_STATIC_DIALOG));
 	m_Page3.Create(IDD_DIALOG3,GetDlgItem(IDC_STATIC_DIALOG));
	m_Page4.Create(IDD_DIALOG4,GetDlgItem(IDC_STATIC_DIALOG));

	m_pArPage.Add(&m_Page1);
 	m_pArPage.Add(&m_Page2);
 	m_pArPage.Add(&m_Page3);
	m_pArPage.Add(&m_Page4);


	CRect rcStatic;	
	CRect rcDialog;
	GetDlgItem(IDC_STATIC_DIALOG)->GetWindowRect(&rcStatic);								//获取控件相对于屏幕坐标的位置;
	ScreenToClient(&rcStatic);															//转换为控件相对于父窗口的位置;

	m_rcCaption.SetRect(rcStatic.left,rcStatic.top,rcStatic.right,rcStatic.top+m_nCaption);			//rcCaption.bottom
	rcDialog.SetRect(rcStatic.left,m_rcCaption.bottom,rcStatic.right,rcStatic.bottom);

	GetDlgItem(IDC_STATIC_DIALOG)->MoveWindow(&rcDialog);
	for (int i=0;i<m_pArPage.GetSize();i++)
	{
		((CDialog*)m_pArPage[i])->SetWindowPos(&CWnd::wndNoTopMost,rcDialog.left,rcDialog.top,rcDialog.Width(),rcDialog.Height(),SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
	}

	ShowSubDlg(0, _T("Test1"));
}

void CDdDlg::InitInfo()
{}

void CDdDlg::DrawTitle(CDC* pDC)
{
	int i =0;
	COLORREF	clrEnd;
	COLORREF	clrStart;

	clrStart=RGB(255,150,0);
	clrEnd=RGB(150,150,0);
	int nStartR=GetRValue(clrStart);
	int nStartG=GetGValue(clrStart);
	int nStartB=GetBValue(clrStart);
	int nEndR=GetRValue(clrEnd);
	int nEndG=GetGValue(clrEnd);
	int nEndB=GetBValue(clrEnd);

	//////////////////////////////////////////////////////////////////////////
	//
	int nIncWidth = m_rcCaption.Width() - 3;
	double incR = ((double)abs(nStartR - nEndR)) / (double)(nIncWidth);
	double incG = ((double)abs(nStartG - nEndG)) / (double)(nIncWidth);
	double incB = ((double)abs(nStartB - nEndB)) / (double)(nIncWidth);
	//////////////////////////////////////////////////////////////////////////
	//
	int nCurR=nStartR;
	int nCurG=nStartG;
	int nCurB=nStartB;


	CRect rcDraw(m_rcCaption.left,m_rcCaption.top,m_rcCaption.left+1,m_rcCaption.bottom);
	int nSignR = (nStartR - nEndR) < 0 ? 1 : (-1);
	int	nSignG = (nStartG - nEndG) < 0 ? 1 : (-1);
	int	nSignB = (nStartB - nEndB) < 0 ? 1 : (-1);
	for (i=0;i<=m_rcCaption.Width();i++)
	{
		pDC->FillSolidRect(&rcDraw,RGB(nCurR,nCurG,nEndB));
		rcDraw.OffsetRect(1,0);

		int nTmpR = int(nStartR + nSignR * i * incR);
		int	nTmpG = int(nStartG + nSignG * i * incG);
		int	nTmpB = int(nStartB + nSignB * i * incB);

		nCurR = nSignR * (nTmpR - nEndR) < 0 ? nTmpR : nEndR;
		nCurG = nSignG * (nTmpG - nEndG) < 0 ? nTmpG : nEndG;
		nCurB = nSignB * (nTmpB - nEndB) < 0 ? nTmpB : nEndB;
	}
}


void CDdDlg::ShowSubDlg(int nIndex, LPCTSTR szTitle)
{
	if (nIndex <= m_pArPage.GetUpperBound())
	{
		if(m_nPrevPage != nIndex)
		{
			if (m_nPrevPage != -1)
			{
				((CDialog*)m_pArPage[m_nPrevPage])->ShowWindow(SW_HIDE);
			}
			((CDialog*)m_pArPage[nIndex])->ShowWindow(SW_SHOW);
			((CDialog*)m_pArPage[nIndex])->SetFocus();

			m_nPrevPage = nIndex;
			m_HeaderCtrl.SetDescText(szTitle);
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//
void CDdDlg::OnButton1() 
{
	int nCurSel=0;
	ShowSubDlg(nCurSel, _T("Test1"));
}

void CDdDlg::OnButton2() 
{
	int nCurSel=1;
	ShowSubDlg(nCurSel, _T("Test2"));
}

void CDdDlg::OnButton3() 
{
	int nCurSel=2;
	ShowSubDlg(nCurSel, _T("Test3"));
}

void CDdDlg::OnButton4() 
{
	int nCurSel=3;
	ShowSubDlg(nCurSel, _T("Test4"));
}
