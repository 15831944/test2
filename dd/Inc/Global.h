#ifndef ___GLOBAL_H___
#define ___GLOBAL_H___


#ifdef SAFE_RELEASE
#undef SAFE_RELEASE
#endif
#define SAFE_RELEASE(x) do{\
	if((x) != NULL)\
	{\
		while((x)->Release() != 0);\
		(x) = NULL;\
	}\
}while(0)
	
static HBITMAP StretchBitmap(HBITMAP hBitmap, int iWidth, int iHeight)
{
	HDC hdcScreen = ::GetDC(NULL);
	HDC hdcSource = ::CreateCompatibleDC(hdcScreen); 
	HDC hdcStretch = ::CreateCompatibleDC(hdcScreen); 
	::SelectObject(hdcSource, hBitmap);
	HBITMAP hbmStretch = ::CreateCompatibleBitmap(hdcScreen, iWidth, iHeight);
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hdcStretch, hbmStretch);

	BITMAP bm;
	::GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&bm);

	::SetStretchBltMode(hdcStretch, COLORONCOLOR);

	::StretchBlt(hdcStretch, 0, 0, iWidth, iHeight, 
		hdcSource, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

	::SelectObject(hdcStretch, hOldBmp);
	::DeleteDC(hdcSource);	
	::DeleteDC(hdcStretch);
	::ReleaseDC(NULL, hdcScreen);

	return hbmStretch;
}
#endif