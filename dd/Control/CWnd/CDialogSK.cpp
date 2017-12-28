#include "StdAfx.h"
#include "CDialogSK.h"

#include <math.h>

#define LWA_COLORKEY 			1 				// Use color as the transparency color.
#define LWA_ALPHA    			2 				// Use bAlpha to determine the opacity of the layer
#define WS_EX_LAYERED 			0x00080000 

#define SafeDelete(pData)		{ try { delete pData; } catch (...) { ASSERT(FALSE); } pData=NULL; }
#define SafeRelease(pObject)	{ if (pObject!=NULL) { pObject->Release(); pObject=NULL; } }

typedef BOOL (WINAPI *lpfnSetLayeredWindowAttributes) (HWND hWnd, COLORREF cr, BYTE bAlpha, DWORD dwFlags);
lpfnSetLayeredWindowAttributes g_pSetLayeredWindowAttributes;

#pragma comment(lib,"Gdiplus.lib")
/////////////////////////////////////////////////////////////////////////////
//
IMPLEMENT_DYNAMIC(CDialogSK, CDialog)
CDialogSK::CDialogSK(CWnd* pParent /*=NULL*/)
{
	Initialize();
}

CDialogSK::~CDialogSK()
{
	Finalize();
}

CDialogSK::CDialogSK(UINT uResourceID, CWnd* pParent)
			:CDialog(uResourceID, pParent)
{
	Initialize();
}

CDialogSK::CDialogSK(LPCTSTR pszResourceID, CWnd* pParent)
			:CDialog(pszResourceID, pParent)
{
	Initialize();
}

void CDialogSK::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDialogSK, CDialog)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//
BOOL CDialogSK::OnInitDialog()
{
    CDialog::OnInitDialog();
	return TRUE;
}

BOOL CDialogSK::PreTranslateMessage( MSG* pMsg )
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}
	
	if (m_bHotKeyMode == TRUE)
	{
		if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_ESCAPE) || (pMsg->wParam == VK_RETURN) )
		{
			return TRUE;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDialogSK::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	if (m_pImage == NULL)
	{
		return;
	}

	Invalidate();	
}

BOOL CDialogSK::OnEraseBkgnd(CDC* pDC) 
{
	DrawBitmap(pDC);
	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}

void CDialogSK::OnLButtonDown(UINT nFlags, CPoint point) 
{
    if (m_bEasyMove)
	{
        PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	}

    CDialog::OnLButtonDown(nFlags, point);
}

/////////////////////////////////////////////////////////////////////////////
//
BOOL CDialogSK::SetBitmap(int nBitmap, LPCTSTR lpszType)
{
	BOOL bRet = FALSE;

	HGLOBAL pGlobal = NULL;
	LPVOID  pBuffer = NULL;
	LPVOID  pImageBuffer = NULL;
	LPCTSTR lpszResourceName = NULL;
		
	do 
	{
		if (m_pImage != NULL) 
		{
			bRet = FALSE;
			break;
		}

		lpszResourceName = MAKEINTRESOURCE(nBitmap);
		if (lpszResourceName == NULL)
		{
			bRet = FALSE;
			break;
		}

		HINSTANCE hInstResource = ::AfxFindResourceHandle(lpszResourceName, lpszType);	//AfxGetResourceHandle(); //AfxGetInstanceHandle();//AfxFindResourceHandle(lpszResourceName, lpszType);
		if (hInstResource == NULL)
		{
			bRet = FALSE;
			break;
		}

		HRSRC hResource = ::FindResource(hInstResource, lpszResourceName, lpszType);
		if (hResource == NULL)
		{
			bRet = FALSE;
			break;
		}

		DWORD dwImageSize=::SizeofResource(hInstResource,hResource);
		pImageBuffer=::LockResource(::LoadResource(hInstResource,hResource));
		if (pImageBuffer == NULL)
		{
			bRet = FALSE;
			break;
		}

		pGlobal = ::GlobalAlloc(GMEM_FIXED, dwImageSize);	//GMEM_FIXED	//GMEM_MOVEABLE
		if (pGlobal == NULL)
		{
			bRet = FALSE;
			break;
		}

		pBuffer = ::GlobalLock(pGlobal);
		if (pBuffer == NULL)
		{
			bRet = FALSE;
			break;
		}

		CopyMemory(pBuffer, pImageBuffer, dwImageSize);

		IStream* pStream = NULL;
		if (::CreateStreamOnHGlobal(pGlobal, TRUE, &pStream) != S_OK)
		{
			bRet = FALSE;
			break;
		}

		m_pImage=Bitmap::FromStream(pStream);
		SafeRelease(pStream);

		if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok))
		{
			return FALSE;
		}

		bRet = TRUE;
	} while (FALSE);

	if (pImageBuffer != NULL)
	{
		::FreeResource(pImageBuffer);
		pImageBuffer = NULL;
	}

	if (pBuffer != NULL)
	{
		::GlobalUnlock(pGlobal);
	}

	if (pGlobal != NULL)
	{
		::GlobalFree(pGlobal);
		pGlobal = NULL;
	}

	return bRet;
}

BOOL CDialogSK::SetBitmap(LPCTSTR lpszFileName)
{
	if (m_pImage != NULL) 
	{
		return FALSE;
	}

	CT2CW strFileName(lpszFileName);
	m_pImage=Bitmap::FromFile((LPCWSTR)strFileName);

	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok)) 
	{
		return FALSE;
	}

    return TRUE;
}

void CDialogSK::DestroyImage()
{
	if (m_pImage!=NULL)
	{
		SafeDelete(m_pImage);
	}
}

void CDialogSK::SetStyle(LayOutStyle style)
{
    if(m_loStyle == LO_RESIZE)
    {
		if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok))
		{
			return;
		}

        SetWindowPos(0, 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), SWP_NOMOVE|SWP_NOREPOSITION );
    }
	
	m_loStyle = style;
}

void CDialogSK::SetHotKeyMode(BOOL bMode)
{
	m_bHotKeyMode = bMode;
}

void CDialogSK::EnableEasyMove(BOOL pEnable)
{
	m_bEasyMove = pEnable;
}

void CDialogSK::GetBitmapSize(int &iWidth,int &iHeight)
{
	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok))
	{
		return;
	}

	iWidth  = m_pImage->GetWidth();
	iHeight = m_pImage->GetHeight();
}

BOOL CDialogSK::SetTransparent (BYTE bAlpha)
{
    if (g_pSetLayeredWindowAttributes == NULL)
	{
        return FALSE;
	}

    if (bAlpha < 255)
    {
        SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
        g_pSetLayeredWindowAttributes(m_hWnd, 0, bAlpha, LWA_ALPHA);
    }
    else
    {
        SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
        ::RedrawWindow(m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
    }

    return TRUE;
}

BOOL CDialogSK::SetTransparentColor (COLORREF col, BOOL bTrans)
{
    if (g_pSetLayeredWindowAttributes == NULL)
	{
        return FALSE;
	}

    if (bTrans)
    {
        SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
		//SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_TRANSPARENT);
        g_pSetLayeredWindowAttributes(m_hWnd, col, 0, LWA_COLORKEY);
		
		m_color = col;
    }
    else
    {
        SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
        ::RedrawWindow(m_hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
    }

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
//
void CDialogSK::Initialize()
{
	m_bEasyMove = FALSE;
	m_bHotKeyMode = FALSE;

	m_pImage  = NULL;
	m_loStyle = LO_DEFAULT;

	Gdiplus::GdiplusStartupInput StartupInput; 
	GdiplusStartup(&m_bGdiplusToken,&StartupInput,NULL); 

    HMODULE hUser32 = GetModuleHandle(_T("USER32.DLL"));
    g_pSetLayeredWindowAttributes = (lpfnSetLayeredWindowAttributes)GetProcAddress(hUser32, "SetLayeredWindowAttributes");
}

void CDialogSK::Finalize()
{
	Gdiplus::GdiplusShutdown(m_bGdiplusToken);
}

void CDialogSK::DrawBitmap(CDC *pDC)
{
	INT nXDest = 0;
	INT nYDest = 0;

	INT nDestWidth  = 0;
	INT nDestHeight = 0;

	CRect   rect;
	GetClientRect(rect);

	if (pDC == NULL)
	{
		return;
	}
	
	if ((m_pImage==NULL)||(m_pImage->GetLastStatus()!=Ok))
	{
		return;
	}

	Graphics graphics(pDC->GetSafeHdc());
	
	if ( m_loStyle == LO_DEFAULT || m_loStyle == LO_RESIZE )
    {
		nDestWidth  = rect.Width();
		nDestHeight = rect.Height();

		graphics.DrawImage(m_pImage, nXDest, nYDest, nDestWidth, nDestHeight);
    }
	else if (m_loStyle == LO_TILE)
	{
		int ixOrg, iyOrg;
		
		for (iyOrg = 0; iyOrg < rect.Height(); iyOrg += m_pImage->GetHeight())
        {
            for (ixOrg = 0; ixOrg < rect.Width(); ixOrg += m_pImage->GetWidth())
            {
				nDestWidth  = rect.Width();
				nDestHeight = rect.Height();

				graphics.DrawImage(m_pImage, ixOrg, iyOrg, nDestWidth, nDestHeight);
            }
        }
	}
	else if (m_loStyle == LO_CENTER)
    {		
		int ixOrg = abs((rect.Width()  - (int)m_pImage->GetWidth())) / 2;
        int iyOrg = abs((rect.Height() - (int)m_pImage->GetHeight())) / 2;

		nDestWidth  = rect.Width();
		nDestHeight = rect.Height();
         
		graphics.DrawImage(m_pImage, ixOrg, iyOrg, nDestWidth, nDestHeight);
    }
	else if ( m_loStyle == LO_STRETCH)
    {
		nDestWidth  = rect.Width();
		nDestHeight = rect.Height();

		graphics.DrawImage(m_pImage, nXDest, nYDest, nDestWidth, nDestHeight);
    }
}

void CDialogSK::SetupRegion(CDC *pDC, CBitmap &cBitmap, COLORREF TransColor)
{
    CDC memDC;
    //创建与传入DC兼容的临时DC
    memDC.CreateCompatibleDC(pDC);
    
    CBitmap *pOldMemBmp=NULL;
    //将位图选入临时DC
    pOldMemBmp=memDC.SelectObject(&cBitmap);
    
    CRgn wndRgn;
    //创建总的窗体区域，初始region为0
    wndRgn.CreateRectRgn(0,0,0,0);
    
    
    BITMAP bit;   
    cBitmap.GetBitmap (&bit);//取得位图参数，这里要用到位图的长和宽     
    
    int y;
    for(y=0;y<=bit.bmHeight  ;y++)
    {
        CRgn rgnTemp; //保存临时region
        
        int iX = 0;
        do
        {
            //跳过透明色找到下一个非透明色的点.
            while (iX <= bit.bmWidth  && memDC.GetPixel(iX, y) == TransColor)
                iX++;
            
            //记住这个起始点
            int iLeftX = iX;
            
            //寻找下个透明色的点
            while (iX <= bit.bmWidth  && memDC.GetPixel(iX, y) != TransColor)
                ++iX;
            
            //创建一个包含起点与重点间高为1像素的临时“region”
            rgnTemp.CreateRectRgn(iLeftX, y, iX, y+1);
            
            //合并到主"region".
            wndRgn.CombineRgn(&wndRgn, &rgnTemp, RGN_OR);
            
            //删除临时"region",否则下次创建时和出错
            rgnTemp.DeleteObject();
        }while(iX <bit.bmWidth );
        iX = 0;
    }
    
    if(pOldMemBmp)
        memDC.SelectObject(pOldMemBmp);
    
    CWnd * pWnd = pDC->GetWindow();
    pWnd->SetWindowRgn(wndRgn,TRUE);    
    pWnd->SetForegroundWindow();    
	
}