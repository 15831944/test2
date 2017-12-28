#pragma once

#include <afxcmn.h>
#include <GdiPlus.h>

enum LayOutStyle
{
    LO_DEFAULT,
    LO_TILE,    // Tile the background picture
    LO_CENTER,  // Center the background picture
    LO_STRETCH, // Stretch the background picture to the dialog window size
    LO_RESIZE   // Resize the dialog so that it just fits the background 
};

using namespace Gdiplus;
class CDialogSK : public CDialog
{
	DECLARE_DYNAMIC(CDialogSK)
public:
    CDialogSK(CWnd* pParent = NULL);
    virtual  ~CDialogSK();

	CDialogSK(UINT uResourceID, CWnd* pParent = NULL);
	CDialogSK(LPCTSTR pszResourceID, CWnd* pParent = NULL);
	
protected:
	virtual void 					DoDataExchange(CDataExchange* pDX);
	virtual BOOL 					PreTranslateMessage(MSG* pMsg);
    virtual BOOL 					OnInitDialog();

	afx_msg BOOL 					OnEraseBkgnd(CDC* pDC);
	afx_msg void 					OnSize(UINT nType, int cx, int cy);
	afx_msg void 					OnLButtonDown(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	BOOL 							SetBitmap(int nBitmap,  LPCTSTR lpszType = RT_BITMAP);
    BOOL 							SetBitmap(LPCTSTR lpszFileName);

    void 							SetStyle(LayOutStyle style);
	void 							SetHotKeyMode(BOOL bMode = TRUE);

	 void 							EnableEasyMove (BOOL pEnable = TRUE);
	void 							GetBitmapSize(int &iWidth,int &iHeight);
	
    BOOL 							SetTransparent (BYTE bAlpha);
    BOOL 							SetTransparentColor (COLORREF col, BOOL bTrans = TRUE);
		
protected:	
	void 							Initialize();
	void							Finalize();

	void							DestroyImage();
	
	void							DrawBitmap(CDC *pDC);
	void 							SetupRegion(CDC *pDC, CBitmap &cBitmap, COLORREF TransColor);
	
private:
	BOOL 							m_bEasyMove;
	BOOL  							m_bHotKeyMode;
	
	Bitmap*							m_pImage;

	COLORREF 						m_color;
    LayOutStyle 					m_loStyle;  

	ULONG_PTR						m_bGdiplusToken;
};