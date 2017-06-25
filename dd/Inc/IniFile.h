#pragma once
#include "Directory.h"

#define  DefaultConfig  "Default.ini"
namespace Leaf
{
	namespace IO
	{
		class CIniFile 
		{
		public:
			CIniFile();
			virtual ~CIniFile();
			
		private:
			CString		m_sFilename;
			CString		m_sFilePath;
			
		public:
			void		Init(LPCTSTR m_sFilePathname);
			
			int			ReadInt(LPCTSTR m_sAPP,  LPCTSTR m_sKey);
			float		ReadFloat(LPCTSTR m_sApp,LPCTSTR m_sKey);
			long		ReadLong(LPCTSTR m_sAPP,  LPCTSTR m_sKey);
			bool		ReadBool(LPCTSTR m_sAPP,  LPCTSTR m_sKey);
			CString		ReadCString(LPCTSTR m_sApp,TCHAR* m_sKey);//LPCTSTR
			COLORREF	ReadRGB(LPCTSTR m_sApp, LPCTSTR m_sKey);
			
			
			//	void ReadArray(CString m_sApp,CString m_sKey,int* m_Val,long nums);
			//	void ReadArray(CString m_sApp,CString m_sKey,float* m_Val,long nums);
			//	void ReadArray(CString m_sApp,CString m_sKey,CString* m_Val,long nums);
			
			
			void Write(CString m_sApp,CString m_sKey,int m_Val);
			void Write(CString m_sApp,CString m_sKey,float m_Val);
			void Write(CString m_sApp,CString m_sKey,TCHAR* m_Val);//CString
			void Write(CString m_sApp,CString m_sKey,bool m_Val);
			void Write(CString m_sApp,CString m_sKey,COLORREF m_Val);
			
			//	void WriteArray(CString m_sApp,CString m_sKey,int* m_Val,long nums);
			//	void WriteArray(CString m_sApp,CString m_sKey,float* m_Val,long nums);
			//	void WriteArray(CString m_sApp,CString m_sKey,CString* m_Val,long nums);
		protected:
			COLORREF HexToRGB(const CString &cszHex);
			CString* SplitString(CString cszHex, char split, int& iSubStrs);
		};
	}
}



