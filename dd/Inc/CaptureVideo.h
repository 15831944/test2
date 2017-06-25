#ifndef __CAPTUREVIDEO_H__
#define __CAPTUREVIDEO_H__

#include <atlbase.h>
#include <windows.h>
#include <DShow.h>
#include <qedit.h>

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }
#endif

class CCaptureVideo
{
public:
	CCaptureVideo();
	virtual ~CCaptureVideo();
	
public:
	int 					EnumDevices(HWND hWndList);
	HRESULT 				PreviewImages(int iDeviceID , HWND hWnd);
	HRESULT					CaptureImages(CString inFileName);
	void					ConfigCameraPin(HWND hwndParent);

protected:
	HRESULT					InitCaptureGraphBuilder();
	bool					BindFilter(int deviceId,IBaseFilter **pFilter);
	HRESULT					SetupVideoWindow();
	void					ResizeVideoWindow();

private:
	HWND					m_hWnd;

	IGraphBuilder 			*m_pGB;	
	ICaptureGraphBuilder2 	*m_pCapture;
	IMediaControl			*m_pMC;
	IVideoWindow			*m_pVW;	
	
	IBaseFilter				*m_pBF;
	IBaseFilter				*m_pMux;
};

#endif