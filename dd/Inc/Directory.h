// Directory.h: interface for the CDirectory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTORY_H__3C9C7C30_E0D5_4F5A_9F82_E9B6173DEC31__INCLUDED_)
#define AFX_DIRECTORY_H__3C9C7C30_E0D5_4F5A_9F82_E9B6173DEC31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace Leaf
{
	namespace IO
	{
		class CDirectory  
		{
		public:
			CDirectory();
			virtual ~CDirectory();
			
		public:
			static CString  GetAppPath();
			static BOOL IsFileExists(LPCTSTR lpszFileName);
			static bool FolderExists(CString s);
			static bool CreateDir(CString p);
			static bool DeleteDirectory(TCHAR* sDirName); 
			static bool SelectMenu(HWND hWnd,TCHAR*pPath,TCHAR*pDisplayString);
		};
	}
}



#endif // !defined(AFX_DIRECTORY_H__3C9C7C30_E0D5_4F5A_9F82_E9B6173DEC31__INCLUDED_)
