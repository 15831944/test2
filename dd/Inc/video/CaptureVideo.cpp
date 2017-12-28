#include "stdafx.h"
#include "CaptureVideo.h"

#pragma comment(lib, "strmiids.lib")
CCaptureVideo::CCaptureVideo()
{
		CoInitialize(NULL);
		m_hWnd = NULL;
		m_pVW  = NULL;
		m_pMC  = NULL;
		m_pGB  = NULL;
		m_pBF  = NULL;
		m_pMux = NULL;
		m_pCapture = NULL;
}

CCaptureVideo::~CCaptureVideo()
{
	if (m_pMC)
	{
		m_pMC->Stop();
	}

	if (m_pVW)
	{
		m_pVW->put_Visible(OAFALSE);
		m_pVW->put_Owner(NULL);
	}

	SAFE_RELEASE(m_pCapture);
	SAFE_RELEASE(m_pMC);
	SAFE_RELEASE(m_pGB);
	SAFE_RELEASE(m_pBF);
	SAFE_RELEASE(m_pMux);
	CoUninitialize( );	
}

int CCaptureVideo::EnumDevices(HWND hWndList)
{
	int nID = 0;
	
	HRESULT hr = NULL;
	IPropertyBag* pBag = NULL;
	ULONG cFetched = 0;
	
	if(!hWndList)
	{
		return -1;
	}
	
	ICreateDevEnum *pCreateDevEnum;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void**)&pCreateDevEnum);
	if(hr != NOERROR)
	{
		return -1;
	}
	
	IEnumMoniker *pEm = NULL;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
	if(hr != NOERROR)
	{
		return -1;
	}
	
	pEm->Reset();
	
	IMoniker *pM = NULL;
	while(pEm->Next(1, &pM, &cFetched) == S_OK)
	{
		pBag = NULL;
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void**)&pBag);
		if(SUCCEEDED(hr))
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(L"FriendlyName", &var, NULL);
			if(hr == NOERROR)
			{
				nID++;
//				::SendMessage(hWndList, );
				SysFreeString(var.bstrVal);
			}
			pBag->Release();
		}
		pM->Release();
	}
	return nID;
}

HRESULT CCaptureVideo::InitCaptureGraphBuilder()
{
	HRESULT hr;
	
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void**)&m_pGB);
	if(FAILED(hr))
	{
		return hr;
	}
	
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC, IID_ICaptureGraphBuilder2, (void**)&m_pCapture);
	if(FAILED(hr))
	{
		return hr;
	}
	
	m_pCapture->SetFiltergraph(m_pGB);
	
	hr = m_pGB->QueryInterface(IID_IMediaControl,(void**)&m_pMC);
	if(FAILED(hr))
	{
		return hr;
	}
	
	hr = m_pGB->QueryInterface(IID_IVideoWindow,(LPVOID*)&m_pVW);
	if(FAILED(hr))
	{
		return hr;
	}
	
	return hr;
}

bool CCaptureVideo::BindFilter(int deviceId,IBaseFilter **pFilter)
{
	HRESULT hr;
	IPropertyBag* pBag = NULL;
	ULONG cFetched = 0;
	int	  nIndex = 0;
	
	if(deviceId < 0)
	{
		return false;
	}
	
	ICreateDevEnum *pCreateDevEnum;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, (void**)&pCreateDevEnum);
	if(hr != NOERROR)
	{
		return false;
	}
	
	IEnumMoniker *pEm = NULL;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory, &pEm, 0);
	if(hr != NOERROR)
	{
		return false;
	}
	
	pEm->Reset();
	
	IMoniker *pM = NULL;
	while(pEm->Next(1, &pM, &cFetched) == S_OK, nIndex <= deviceId)
	{
		pBag = NULL;
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag,(void**)&pBag);
		if(SUCCEEDED(hr))
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(L"FriendlyName",&var,NULL);
			if(hr == NOERROR)
			{
				if( nIndex == deviceId ) 
				{
					pM->BindToObject(0,0,IID_IBaseFilter,(void**)pFilter);
					SysFreeString(var.bstrVal);	
				}
				pBag ->Release();
			}
			pM->Release();
			nIndex++;
		}
	}
	
	return true;
}

void CCaptureVideo::ResizeVideoWindow()
{
	if(m_pVW)
	{
		CRect rect;
		::GetClientRect(m_hWnd, &rect);
		m_pVW->SetWindowPosition(0, 0, rect.right, rect.bottom);
	}
}


HRESULT CCaptureVideo::SetupVideoWindow()
{
	HRESULT hr;
	
	hr = m_pVW->put_Visible(OAFALSE);
	hr = m_pVW->put_Owner((OAHWND)m_hWnd);
	if(FAILED(hr))
	{
		return hr;
	}
	
	hr = m_pVW->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN);
	if(FAILED(hr))
	{
		return hr;
	}
	
	ResizeVideoWindow();
	
	hr = m_pVW->put_Visible(OATRUE);
	return hr;
}

HRESULT CCaptureVideo::PreviewImages(int iDeviceID , HWND hWnd)
{
	HRESULT hr ;
	
	hr = InitCaptureGraphBuilder();
	if(FAILED(hr))
	{
		return hr;
	}
	
	if(!BindFilter(iDeviceID, &m_pBF))
	{
		return S_FALSE;
	}
	
	hr = m_pGB->AddFilter(m_pBF, L"Capture Filter");
	hr = m_pCapture->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video, m_pBF, NULL, NULL);
	if(FAILED(hr))
	{
		return hr;
	}
	
	m_hWnd = hWnd;
	SetupVideoWindow();
	
	hr = m_pMC->Run();
	if(FAILED(hr))
	{
		return hr;
	}
	
	return S_OK;
}

HRESULT CCaptureVideo::CaptureImages(CString inFileName)
{
	HRESULT hr;
	
	m_pMC->Stop();
	
	hr = m_pCapture->SetOutputFileName(&MEDIASUBTYPE_Avi, inFileName.AllocSysString(), &m_pMux, NULL);
	
	hr = m_pCapture->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, m_pBF, NULL, m_pMux);
	
	m_pMux->Release();
	m_pMC->Run();
	return hr;
}

void CCaptureVideo::ConfigCameraPin(HWND hwndParent)
{
	HRESULT hr;
	IAMStreamConfig *pSC ;
	ISpecifyPropertyPages *pSpec ;	
	CAUUID cauuid ;
	
	m_pMC ->Stop();
	
	hr = m_pCapture->FindInterface(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Video,m_pBF,IID_IAMStreamConfig,(void**)&pSC);
	
	hr = pSC->QueryInterface(IID_ISpecifyPropertyPages,(void**)&pSpec);
	if(hr == S_OK)
	{
		hr = pSpec->GetPages(&cauuid);
		
		hr = OleCreatePropertyFrame(hwndParent,30,30,NULL,1,(IUnknown**)&pSC,cauuid.cElems,(GUID*)cauuid.pElems,0,0,NULL);
		
		CoTaskMemFree(cauuid.pElems);
		pSpec->Release();
		pSC->Release();
	}
	m_pMC->Run();
}

HRESULT CCaptureVideo::GetCaptureRatio(IBaseFilter* pCapFilter, ICaptureGraphBuilder2* pBuild)
{
	int nSize = 0;
	int nCount = 0;
	int nIndex = 0;
	
	HRESULT hr;
	SmartPtr<IAMStreamConfig> pam;
	
	hr = pBuild->FindInterface(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, pCapFilter, IID_IAMStreamConfig, reinterpret_cast<void**>(&pam));
	hr = pam->GetNumberOfCapabilities(&nCount, &nSize);
	
	if(sizeof(VIDEO_STREAM_CONFIG_CAPS) == nSize)
	{
		for(nIndex=0; nIndex<nCount; nIndex++)
		{
			AM_MEDIA_TYPE* pmmt;
			VIDEO_STREAM_CONFIG_CAPS scc; 
			
			hr = pam->GetStreamCaps(nIndex, &pmmt, reinterpret_cast<BYTE*>(&scc));
			if(pmmt->formattype == FORMAT_VideoInfo)
			{
				 VIDEOINFOHEADER* pvih = reinterpret_cast<VIDEOINFOHEADER*>(pmmt->pbFormat);
				 int nFrame = pvih->AvgTimePerFrame;	//采集的帧率
			}
		}		
	}
	
	return (hr);
}