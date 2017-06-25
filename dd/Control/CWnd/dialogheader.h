#if !defined(AFX_DIALOGHEADER_H__F13F1054_6222_4BB4_A527_1D17F402B558__INCLUDED_)
#define AFX_DIALOGHEADER_H__F13F1054_6222_4BB4_A527_1D17F402B558__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dialogheader.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDialogHeader window
#define DEFAULTTITLEFONTSIZE	15
#define DEFAULTDESCFONTSIZE		13

#define DEFAULTICONOFFSET		10
#define DEFAULTTITLEOFFSET		10
#define DEFAULTDESCOFFSET		10

#define DEFAULTTEXTALIGN		DT_LEFT
#define DEFAULTHEADERHEIGHT		60

#define DEFAULTBLANKICON		TRUE


class CDialogHeader : public CWnd
{
// Construction
public:
	CDialogHeader();

// Attributes
public:
	COLORREF			GetBackgroundColor() const		{ return m_cBackground;}
	void				SetBackgroundColor(const COLORREF color);

	CString				GetDescStr() const				{ return m_sDesc; }
	void				SetDescText(const LPCTSTR text);

	CString				GetTitleText() const			{ return m_sTitle; }
	void				SetTitleText(const LPCTSTR text);

	int					GetTitleFontSize() 				{ return m_nTitleFontSize; }
	void				SetTitleFontSize(const int TitleSize=DEFAULTTITLEFONTSIZE);

	int					GetDescFontSize() const			{ return m_nDescFontSize; }
	void				SetDescFontSize(const int DescSize=DEFAULTDESCFONTSIZE);

	int					GetHeaderHeight() const			{ return m_nHeaderHeight; }
	void				SetHeaderHeight(const int height=0); 
	

	HICON				GetIconHandle() const			{ return m_hIcon;}
	void				SetIconHandle(const HICON icon);

	int					GetIconOffset() const			{ return m_nIconOffset; }
	void				SetIconOffset(const int offset=DEFAULTICONOFFSET);

	int					GetTitleOffset() const			{ return m_nTitleOffset; }
	void				SetTitleOffset(const int offset=DEFAULTTITLEOFFSET);

	int					GetDescOffset()	const			{ return m_nDescOffset; }
	void				SetDescOffset(const int offset=DEFAULTDESCOFFSET);

	UINT				GetTextAlign() const			{ return m_uAlign; }
	void				SetTextAlign(const UINT align=DEFAULTTEXTALIGN);

	BOOL				GetBlankIcon() const			{ return m_bBlankIcon; }
	void				SetBlankIcon(const BOOL blank=DEFAULTBLANKICON);
protected:
	void				RepaintHeader();
	void				UpdateFont(CFont& font,const LONG lfWeight,const int Size);
// Operations
public:
	void				Init(void* ptrWnd);
	void				MoveCtrls(void* ptrWnd);
	void				SetBMPRes(const UINT rID=-1);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDialogHeader)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDialogHeader();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDialogHeader)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	COLORREF			m_cBackground;							//������ɫ
	int					m_nHeaderHeight;						//���ڸ߶�
	CString				m_sDesc;								//��ע�ַ�
	CString				m_sTitle;								//�����ַ�

	BOOL				m_bFonts;
	CFont				m_NormalFont;							//��ͨ����
	CFont				m_BoldFont;								//������
	int					m_nTitleFontSize;						//���������С	
	int					m_nDescFontSize;						//��ע�����С
	
	HICON				m_hIcon;								//ͼ�����
	int					m_nIconOffset;							//ͼ��ƫ��ֵ
	int					m_nTitleOffset;							//����ƫ��ֵ
	int					m_nDescOffset;							//��עƫ��ֵ

	UINT				m_uAlign;								//����
	BOOL				m_bBlankIcon;
	//////////////////////////////////////////////////////////////////////////
	int					m_nIconWidth;
	int					m_nIconHeight;

	int					m_nxEdge;
	int					m_nyEdge;

	UINT				m_bmpID;
	CBitmap				m_bmpHead;
	CSize				m_sizBmp;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGHEADER_H__F13F1054_6222_4BB4_A527_1D17F402B558__INCLUDED_)
