// RandomFXStatic.cpp : implementation file
//

#include "stdafx.h"
#include "RandomFXStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRandomFXStatic

CRandomFXStatic::CRandomFXStatic(BOOL alwaysAnimate)
{
	this->alwaysAnimate = alwaysAnimate;
}

CRandomFXStatic::~CRandomFXStatic()
{
}

int CRandomFXStatic::GetHighestSetBit(int num)
{
	int bitPos = 0;

	for(bitPos = 0; bitPos <= sizeof(int) * 8; bitPos++) {
		int bitTest;
		bitTest = num >> bitPos;
		if(bitTest == 0) {
			break;
		}
	}

	return bitPos;
}

void CRandomFXStatic::InitFX(HBITMAP hBitmap)
{
	int randRange = GetHighestSetBit(RenderHighestBit);
	int randNum;

	if(alwaysAnimate) {
		randNum = rand() % randRange;
		SetRender(1 << randNum);
	} else {
		randNum = rand() % (randRange + 1);
		if(randNum == randRange) {
			SetRender(RenderNothing);
		} else {
			SetRender(1 << randNum);
		}
	}

	intervalsPerRaindrop = rand() % 26;
	mouseMoveBlobRadius = 3 + rand() % 8;
	mouseMoveBlobHeight = 30 + rand() % 71;
	mouseClickBlobRadius = 20 + rand() % 51;
	mouseClickBlobHeight = 200 + rand() % 801;
	SetFireAlpha(64 + rand() % 129);
	SetPlasmaAlpha(64 + rand() % 129);

	CCoolFXStatic::InitFX(hBitmap);
}

BEGIN_MESSAGE_MAP(CRandomFXStatic, CStatic)
	//{{AFX_MSG_MAP(CRandomFXStatic)
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRandomFXStatic message handlers

void CRandomFXStatic::OnTimer(UINT nIDEvent) 
{
	CCoolFXStatic::OnTimer(nIDEvent);
}

void CRandomFXStatic::OnMouseMove(UINT nFlags, CPoint point) 
{
	
	CCoolFXStatic::OnMouseMove(nFlags, point);
}

void CRandomFXStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
	CCoolFXStatic::OnLButtonDown(nFlags, point);
}
