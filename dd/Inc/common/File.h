#if !defined(AFX_FILE_H__A330BBFD_83E8_46AC_9290_AB66DDBFDB3D__INCLUDED_)
#define AFX_FILE_H__A330BBFD_83E8_46AC_9290_AB66DDBFDB3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


namespace Leaf
{
	namespace IO
	{
		class FilePath
		{
		public:
			FilePath();
			~FilePath();

		protected:

		};

		class File  
		{
		public:
			File();
			virtual ~File();
			
		public:
			static bool IsDirExists(const char* pszFilePath);

			static CString GetTitle(const CString& strName);    //��ȡ�ļ�����������չ��
			static CString GetName(const CString& strName);     //��ȡ�ļ�����������չ��
			static CString GetExt(const CString& strName);      //��ȡ�ļ���չ���������� 
		};

		class Folder
		{
		public:
			Folder();
			~Folder();
		};
	}
}


#endif // !defined(AFX_FILE_H__A330BBFD_83E8_46AC_9290_AB66DDBFDB3D__INCLUDED_)
