// SubFrom.cpp: implementation of the CSubFrom class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SubFrom.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSubFrom::CSubFrom()
{
	m_nActiveForm = -1;
    m_Rect.right  = 0;
    m_Rect.top    = 0;
    m_Rect.bottom = 0;
    m_Rect.left   = 0;
	m_bPos=false;
}

CSubFrom::~CSubFrom()
{
	for (int i=0;i<m_Forms.GetUpperBound();i++)
	{
		CDialog* pDlg=m_Forms.GetAt(i);
		pDlg->DestroyWindow();
        delete pDlg;
	}
}

void CSubFrom::SetPosRect(const CRect& rect)
{
	m_Rect=rect;
	m_bPos=true;
}

int CSubFrom::AddForm(CDialog* dlg)
{
	return(m_Forms.Add(dlg));
}

bool CSubFrom::CreateSubForm(UINT id,CWnd* pParentWnd)
{
	CDialog* pDlg = new CDialog();
	ASSERT(pDlg != NULL);
	if (pDlg == NULL)
	{
		return false;
	}
	AddForm(pDlg);
	pDlg->Create(id,pParentWnd);

	CRect rcDlg;
	pDlg->GetWindowRect(&rcDlg);

	int x,y;
	if (m_bPos)
	{
		x=m_Rect.left-rcDlg.left+((m_Rect.Width()-rcDlg.Width())/2);
		y=m_Rect.top-rcDlg.top+((m_Rect.Height()-rcDlg.Height())/2);
	}
	else
	{
		x=m_Rect.left-rcDlg.left;
		y=m_Rect.top-rcDlg.top;
	}

//	pDlg->SetWindowPos(pParentWnd,x,y,rcDlg.Width(),rcDlg.Height(),SWP_NOZORDER);
	pDlg->SetWindowPos(&CWnd::wndNoTopMost,x,y,rcDlg.Width(),rcDlg.Height(),SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
	return true;
}

bool CSubFrom::ShowSubForm(int ix /* = -1 */)
{
	ASSERT(ix <= m_Forms.GetUpperBound());
	if (ix > m_Forms.GetUpperBound())
	{
		return false;
	}

	CDialog* pDlg;
	if (ix!=-1)
	{
		if (m_nActiveForm!=-1)
		{
			pDlg=m_Forms.GetAt(m_nActiveForm);
			ASSERT(pDlg != NULL);
			ASSERT(pDlg->m_hWnd != NULL);

			if ((pDlg==NULL)||(pDlg->m_hWnd==NULL))
			{
				return false;
			}
		}
		m_nActiveForm=ix;
	}
	else
	{
		if (m_nActiveForm==-1)
		{
			m_nActiveForm=0;
		}
	}

	pDlg=m_Forms.GetAt(m_nActiveForm);
	ASSERT(pDlg != NULL);
    ASSERT(pDlg->m_hWnd != NULL);
	if ((pDlg==NULL)||(pDlg->m_hWnd==NULL))
	{
		return false;
	}

//	pDlg->ShowWindow(SW_SHOW);
  //  pDlg->Invalidate();
 //   pDlg->RedrawWindow();
	return true;
}

bool CSubFrom::SetActive(int ix)
{
	if (ix > m_Forms.GetUpperBound()) 
	{
		return false;
	}
	m_nActiveForm=ix;
	return true;
}