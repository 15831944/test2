#ifndef		__PICTURE_H__
#define		__PICTURE_H__

#include  <atlconv.h>
#include <atlbase.h>
#define HIMETRIC_INCH 2540
namespace Leaf
{
	namespace IO
	{
		class CPicture  
		{
		public:
			CPicture();
			virtual ~CPicture();

		public:
			BOOL		LoadFromFile(LPCTSTR szFilePath);
			BOOL		LoadFromResource(UINT ResourceName,LPCTSTR ResourceType);
			BOOL		LoadFromStream(BYTE* pData,size_t nSize);
			BOOL		LoadFromStream(IStream* pStream);
			void		FreeData();


			BOOL		Show(CDC* pDC, CRect  DrawRect);
			BOOL		Show(CDC* pDC, CPoint pTop, CPoint pButtom, int nX, int nY);
			BOOL		ShowBitmapResource(CDC* pDC, const int BMPResource, CPoint LeftTop);

			CSize		GetImageSize(CDC* pDC);
		private:
			IPicture*	m_IPicture;
			LONG		m_Height;				//Í¼Æ¬µÄÊµ¼ÊÏñËØ
			LONG		m_Width; 
		};
	}
}

 
#endif