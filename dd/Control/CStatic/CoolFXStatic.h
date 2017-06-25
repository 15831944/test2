#pragma once

#include "DIBSectionLite.h"
#include "CWaterRoutine.h"
#include "CFireRoutine.h"
#include "CPlasmaRoutine.h"

// CCoolFXStatic

class CCoolFXStatic : public CStatic
{
	DECLARE_DYNAMIC(CCoolFXStatic)

public:
	CCoolFXStatic();
	virtual ~CCoolFXStatic();

public:
	enum RenderWhich {
		RenderNothing = 0x000,
		RenderWater = 0x0001,
		RenderFire = 0x0002,
		RenderPlasma = 0x0004,
		RenderHighestBit = 0x0004
	};

	int mouseMoveBlobRadius;
	int mouseMoveBlobHeight;
	int mouseClickBlobRadius;
	int mouseClickBlobHeight;
	BOOL bRaindrop;
	UINT animationTimerInteval;
	UINT raindropTimerInteval;
	int intervalsPerRaindrop;

	void StartAnimation();
	void StopAnimation();
	int GetRender();
	void SetRender(int which);
	void SetFireAlpha(int alpha);
	void SetPlasmaAlpha(int alpha);
	HBITMAP SetBitmap(HBITMAP hBitmap);

protected:
	enum {
		ANIMATION_TIMER_ID = 20090707,
	};

	BOOL bAnimate;
	BOOL bRenderWater;
	BOOL bRenderFire;
	BOOL bRenderPlasma;
	CDIBSectionLite bmpRenderSource;
	CDIBSectionLite bmpRenderTarget;
	CWaterRoutine water;
	CFireRoutine fire;
	CPlasmaRoutine plasma;

	virtual void InitFX(HBITMAP hBitmap);
	virtual void EndFX();
	void LoadRenderBitmap(HBITMAP hBitmap);
	void GenerateOneRaindrop();

private:
	BOOL inited;
	UINT animationTimer;
	UINT raindropTimer;

protected:
	DECLARE_MESSAGE_MAP()

protected:
	virtual void PreSubclassWindow();

public:
	virtual BOOL Create(LPCTSTR lpszText, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


