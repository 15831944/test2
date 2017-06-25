// CoolFXStatic.cpp : implementation file
//

#include "stdafx.h"
#include "CoolFXStatic.h"

// CCoolFXStatic
IMPLEMENT_DYNAMIC(CCoolFXStatic, CStatic)

CCoolFXStatic::CCoolFXStatic()
	: inited(FALSE)
	, bAnimate(TRUE)
	, bRenderWater(TRUE)
	, bRenderFire(FALSE)
	, bRenderPlasma(FALSE)
	, raindropTimer(0)
	, bRaindrop(TRUE)
	, raindropTimerInteval(1000)
	, intervalsPerRaindrop(2)
	, animationTimer(0)
	, animationTimerInteval(40)
	, mouseMoveBlobRadius(5)
	, mouseMoveBlobHeight(50)
	, mouseClickBlobRadius(50)
	, mouseClickBlobHeight(500)
{
	fire.m_iAlpha = 30;	// want a 30% alpha
	plasma.m_iAlpha = 30;	// 30 % alpha

	srand(::GetTickCount() + 20090707);
}

CCoolFXStatic::~CCoolFXStatic()
{
}


BEGIN_MESSAGE_MAP(CCoolFXStatic, CStatic)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CCoolFXStatic message handlers

void CCoolFXStatic::LoadRenderBitmap(HBITMAP hBitmap)
{
	bmpRenderSource.SetBitmap(hBitmap);
	bmpRenderTarget.SetBitmap(hBitmap);
	water.Create(bmpRenderSource.GetWidth(), bmpRenderSource.GetHeight());

	fire.m_iWidth = bmpRenderSource.GetWidth();
	fire.m_iHeight = bmpRenderSource.GetHeight();
	fire.InitFire();

	plasma.Create(bmpRenderSource.GetWidth(), bmpRenderSource.GetHeight());
}

void CCoolFXStatic::InitFX(HBITMAP hBitmap)
{
	if(hBitmap != NULL) {
		LoadRenderBitmap(hBitmap);
	}


	if(!inited && hBitmap != NULL) {
		animationTimer = SetTimer(ANIMATION_TIMER_ID, animationTimerInteval, NULL);
		OnTimer(ANIMATION_TIMER_ID);	// let's start, right now.
		inited = TRUE;
	}
}

void CCoolFXStatic::PreSubclassWindow()
{
	CStatic::PreSubclassWindow();

	LONG_PTR style = ::GetWindowLongPtr(this->GetSafeHwnd(), GWL_STYLE);
	style |= SS_NOTIFY;
	style |= SS_BITMAP;
	::SetWindowLongPtr(this->GetSafeHwnd(), GWL_STYLE, style);

	InitFX(GetBitmap());
}

HBITMAP CCoolFXStatic::SetBitmap(HBITMAP hBitmap)
{
	InitFX(hBitmap);

	return CStatic::SetBitmap(hBitmap);
}

BOOL CCoolFXStatic::Create(LPCTSTR lpszText, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	dwStyle |= SS_NOTIFY;
	dwStyle |= SS_BITMAP;
	return CStatic::Create(lpszText, dwStyle, rect, pParentWnd, nID);
}

void CCoolFXStatic::EndFX()
{
	if(animationTimer != 0) {
		KillTimer(animationTimer);
		animationTimer = 0;
	}

	if(raindropTimer != 0) {
		KillTimer(raindropTimer);
		raindropTimer = 0;
	}

	inited = FALSE;
}

void CCoolFXStatic::OnDestroy()
{
	EndFX();

	CStatic::OnDestroy();
}

void CCoolFXStatic::StartAnimation()
{
	bAnimate = TRUE;
}

void CCoolFXStatic::StopAnimation()
{
	bAnimate = FALSE;
	water.FlattenWater();	// flatten it so it appears we turned it off...
	bmpRenderTarget.Copy(bmpRenderSource);
	Invalidate();
}

int CCoolFXStatic::GetRender()
{
	int ret = RenderNothing;

	if(bRenderWater) { ret |= RenderWater; }
	if(bRenderFire) { ret |= RenderFire; }
	if(bRenderPlasma) { ret |= RenderPlasma; }

	return ret;
}

void CCoolFXStatic::SetRender(int which)
{
	bRenderWater = (which & RenderWater) ? TRUE : FALSE;
	bRenderFire = (which & RenderFire) ? TRUE : FALSE;
	bRenderPlasma = (which & RenderPlasma) ? TRUE : FALSE;
}

void CCoolFXStatic::SetFireAlpha(int alpha)
{
	fire.m_iAlpha = alpha;
}

void CCoolFXStatic::SetPlasmaAlpha(int alpha)
{
	plasma.m_iAlpha = alpha;
}

void CCoolFXStatic::GenerateOneRaindrop()
{
	if(intervalsPerRaindrop == 0 || rand() % intervalsPerRaindrop == 0) {
		water.HeightBlob(
			rand() % bmpRenderSource.GetWidth(),
			rand() % bmpRenderSource.GetHeight(),
			mouseMoveBlobRadius,
			mouseMoveBlobHeight,
			water.m_iHpage
		);
	}
}

void CCoolFXStatic::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case ANIMATION_TIMER_ID:
		if(bAnimate) {
			if(bRenderWater) {
				water.Render((DWORD*)bmpRenderSource.GetDIBits(), (DWORD*)bmpRenderTarget.GetDIBits());
			} else {
				bmpRenderTarget.Copy(bmpRenderSource);
			}
			
			if(bRenderFire) {
				fire.Render((DWORD*)bmpRenderTarget.GetDIBits(), bmpRenderSource.GetWidth(), bmpRenderSource.GetHeight());
			}

			if(bRenderPlasma) {
				plasma.Render((DWORD*)bmpRenderTarget.GetDIBits(), bmpRenderSource.GetWidth(), bmpRenderSource.GetHeight(), bmpRenderSource.GetWidth());
			}

			CClientDC dc(this);
			bmpRenderTarget.Draw(&dc, CPoint(0, 0));
		}

		if(bAnimate && bRenderWater && bRaindrop) {
			GenerateOneRaindrop();
		}

		break;
	}

	CStatic::OnTimer(nIDEvent);
}

void CCoolFXStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	bmpRenderTarget.Draw(&dc, CPoint(0, 0));
}

void CCoolFXStatic::OnMouseMove(UINT nFlags, CPoint point)
{
	if(bAnimate && bRenderWater) {
		if(nFlags & MK_LBUTTON) {
			water.HeightBlob(point.x, bmpRenderSource.GetHeight() - point.y, mouseClickBlobRadius, mouseClickBlobHeight, water.m_iHpage);
		} else {
			water.HeightBlob(point.x, bmpRenderSource.GetHeight() - point.y, mouseMoveBlobRadius, mouseMoveBlobHeight, water.m_iHpage);
		}
	}

	CStatic::OnMouseMove(nFlags, point);
}

void CCoolFXStatic::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(bAnimate && bRenderWater) {
		water.HeightBlob(point.x, bmpRenderSource.GetHeight() - point.y, mouseClickBlobRadius, mouseClickBlobHeight, water.m_iHpage);
	}

	CStatic::OnLButtonDown(nFlags, point);
}
