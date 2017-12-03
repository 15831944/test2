// Picture.cpp: implementation of the CPicture class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Picture.h"

using namespace Leaf::IO;
CPicture::CPicture()
{
	m_IPicture	= NULL;
	m_Height	= 0;
	m_Width		= 0;
}

CPicture::~CPicture()
{
	FreeData();
}

void CPicture::FreeData()
{
	if (m_IPicture != NULL)
	{
		m_IPicture->Release();
		m_IPicture = NULL;
		m_Height = 0;
		m_Width  = 0;
	}
}

BOOL CPicture::LoadFromFile(LPCTSTR szFilePath)
{
	BOOL bResult = FALSE;
	HANDLE hFile = NULL; 
	BYTE   *pBuf = NULL;
	DWORD dwFileSize,dwByteRead; 
	hFile=CreateFile(szFilePath,
					 GENERIC_READ,   
					 FILE_SHARE_READ,
					 NULL,
					 OPEN_EXISTING,
					 FILE_ATTRIBUTE_NORMAL,
					 NULL); 
	if (hFile != INVALID_HANDLE_VALUE) 
	{
		dwFileSize=GetFileSize(hFile,NULL);									//获取文件字节数 
		if (dwFileSize != 0xFFFFFFFF)
		{
			pBuf = new BYTE[dwFileSize+1];
			memset(pBuf, 0x00, dwFileSize+1);

			ReadFile(hFile, pBuf, dwFileSize, &dwByteRead, NULL);
			if (LoadFromStream(pBuf, dwByteRead))
			{
				if (m_IPicture != NULL)
				{
					bResult = TRUE;
				}
				else
				{
					bResult = FALSE;
				}
			}
			delete[] pBuf;
			pBuf = NULL;
		}
	}
	CloseHandle(hFile);
	hFile = NULL;
	return (bResult);
}

BOOL CPicture::LoadFromResource(UINT ResourceName,LPCTSTR ResourceType)		//HMODULE hModule
{
	USES_CONVERSION;
	BOOL 	bResult = FALSE;
	HGLOBAL	hGlobal = NULL;
	HRSRC	hSource = NULL;
	LPVOID	lpVoid  = NULL;
	int		nSize   = 0;

	if (m_IPicture != NULL)
	{
		FreeData();
	}

	hSource = FindResource(AfxGetResourceHandle(), MAKEINTRESOURCE(ResourceName), ResourceType);  //T2CW //A2CW
	if (hSource != NULL)
	{
		hGlobal = LoadResource(AfxGetResourceHandle(), hSource);
		if (hGlobal != NULL)
		{
			lpVoid = LockResource(hGlobal);
			if (lpVoid != NULL)
			{
				nSize = (UINT)SizeofResource(AfxGetResourceHandle(), hSource);   //返回指定资源字节数大小
				if (LoadFromStream((BYTE*)hGlobal, nSize))
				{
					if (m_IPicture != NULL)
					{
						bResult = TRUE;
					}
					else
					{
						bResult = FALSE;
					}
				}
			}
		}
	}

	UnlockResource(hGlobal); 
	FreeResource(hGlobal);
	return (bResult);
}

BOOL CPicture::LoadFromStream(BYTE* pData,size_t nSize)
{
	BOOL bResult = FALSE;
	LPSTREAM pStream = NULL;													//IStream

	if (pData != NULL)
	{
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, nSize);					//分配可移动的内存
		void* pBuffer = GlobalLock(hGlobal);									//将该句柄转换为一个指针
		memcpy(pBuffer, pData, nSize);
		GlobalUnlock(hGlobal);

		HRESULT hr = CreateStreamOnHGlobal(hGlobal, TRUE, &pStream);			//从指定内存创建流对象;TRUE,hGlobal最终会自动释放 
		_ASSERTE(SUCCEEDED(hr) && pStream);
		if (hr != S_FALSE)
		{
			/*OleLoadPicture 函数实际上创建了一个IPicture类型的COM接口对象;OleCreatePictureIndirect*/
			hr = OleLoadPicture(pStream, nSize, FALSE, IID_IPicture, (LPVOID *)&m_IPicture);			
			_ASSERTE(SUCCEEDED(hr) && m_IPicture); 
			if (hr != E_NOINTERFACE)
			{
				bResult = TRUE;
			}
		}
	}

	pStream->Release();
	pStream = NULL;
	return (bResult);
}

BOOL CPicture::LoadFromStream(IStream* pStream)
{
	BOOL bResult = FALSE;
	if (pStream != NULL)
	{
		HRESULT hr = CreateStreamOnHGlobal(NULL, TRUE, &pStream);
		_ASSERTE(SUCCEEDED(hr) && pStream);
		if (hr != S_FALSE)
		{
			hr = OleLoadPicture(pStream, 0, FALSE, IID_IPicture, (LPVOID *)&m_IPicture);			
			_ASSERTE(SUCCEEDED(hr) && m_IPicture); 
			if (hr != E_NOINTERFACE)
			{
				bResult = TRUE;
			}
		}
	}

	pStream->Release();
	pStream = NULL;
	return (bResult);
}

BOOL CPicture::Show(CDC* pDC, CRect DrawRect)
{
	BOOL bResult = FALSE;
	
	if (pDC !=NULL || m_IPicture !=NULL)
	{
		long Width  = 0;
		long Height = 0;
		m_IPicture->get_Width(&Width);									//OLE_XSIZE_HIMETRIC
		m_IPicture->get_Height(&Height);								//OLE_YSIZE_HIMETRIC

		HRESULT hr = m_IPicture->Render(pDC->m_hDC, 
										DrawRect.left,
										DrawRect.top,
										DrawRect.right  - DrawRect.left,
										DrawRect.bottom - DrawRect.top,
										0,
										Height,
										Width,
										-Height,						//负数，表示从最后一行读取，并显示在第一行
										&DrawRect);
		if (hr == S_OK)
		{
			bResult =TRUE;
		}
	}


	return bResult;
}

BOOL CPicture::Show(CDC* pDC, CPoint pTop, CPoint pButtom, int nX, int nY)
{
	BOOL bResult = FALSE;
	if (pDC !=NULL || m_IPicture !=NULL)
	{
		long Width  = 0;
		long Height = 0;
		m_IPicture->get_Width(&Width);
		m_IPicture->get_Height(&Height);

		if (nX == NULL) nX =0;
		if (nY == NULL) nY =0;
		//转换himetric距离为pixels距离，1英寸=25.4毫米
		nX = int(MulDiv(Width, pDC->GetDeviceCaps(LOGPIXELSX), HIMETRIC_INCH) * nX);
		nY = int(MulDiv(Height,pDC->GetDeviceCaps(LOGPIXELSY), HIMETRIC_INCH) * nY);

		CRect DrawRect(pTop.x, pTop.y, nX, nY);
		HRESULT hr = m_IPicture->Render(pDC->m_hDC,
										pTop.x,			//输出位置的起始x坐标
										pTop.y,			//输出位置的起始x坐标
										pButtom.x + nX,	//输出位置的宽度
										pButtom.y + nY,	//输出位置的高度 
										0,           
										Height,
										Width, 
										-Height,
										&DrawRect);
		if (hr == S_OK)
		{
			bResult = TRUE;
		}
	}

	return bResult;
}


BOOL CPicture::ShowBitmapResource(CDC* pDC, const int BMPResource, CPoint LeftTop)
{
	BOOL bResult=FALSE;
	if (pDC !=NULL)
	{
		CBitmap BMP;
		if (BMP.LoadBitmap(BMPResource))
		{
			BITMAP  BMPInfo;
			BMP.GetBitmap(&BMPInfo);

			CDC DCMemory;
			DCMemory.CreateCompatibleDC(pDC);

			CBitmap* pOldBitmap = DCMemory.SelectObject(&BMP);
			pDC->BitBlt(LeftTop.x, LeftTop.y, BMPInfo.bmWidth, BMPInfo.bmHeight, &DCMemory, 0, 0, SRCCOPY);
			DCMemory.SelectObject(pOldBitmap);

			bResult =TRUE;
		}
	}

	return bResult;
}

CSize CPicture::GetImageSize(CDC* pDC)
{
	CSize size;
	if (pDC !=NULL || m_IPicture !=NULL)
	{
		long Width  = 0;
		long Height = 0;
		m_IPicture->get_Width(&Width);			// 获取图像高度
		m_IPicture->get_Height(&Height);		// 获取图像宽度		
		
		int CurrentDPI_X = pDC->GetDeviceCaps(LOGPIXELSX);
		int CurrentDPI_Y = pDC->GetDeviceCaps(LOGPIXELSY);
		if (pDC->IsPrinting())
		{
			CurrentDPI_X = 96;
			CurrentDPI_Y = 96;
		}
		/*
			显示器上72磅的字在显示器上高度lfHeight是96个象素点;
			显示器分辨率96DPI   PointSize=72; 
			lfHeight = MulDiv(PointSize, GetDeviceCaps(hDC, LOGPIXELSY), 72); 
		*/
		// 转化单位为象素
		m_Width  = MulDiv(Width,  CurrentDPI_X, HIMETRIC_INCH);
		m_Height = MulDiv(Height, CurrentDPI_Y, HIMETRIC_INCH);
		
// 		size.cx = Width;
// 		size.cy = Height;
// 		pDC->HIMETRICtoDP(&size);

		size.cx = m_Width;
		size.cy = m_Height;

	}

	return size;
}