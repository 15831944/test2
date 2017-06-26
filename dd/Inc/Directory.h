#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__

using namespace std;
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
			static std::string		GetAppPath();

			static bool				IsDirExists(const char* pszDirName);

			static bool				CreateDirectory(const char* pszDirPath, bool bFlag = false);
			static bool				DeleteDirectory(const char* pszDirPath, bool bFlag = false); 

			static bool				CopyDirectory(const char* pszSrcDirPath, const char* pszDescDirPath);

			static bool				GetDirSize(const char* pszDirPath, v_uint64_t* pDirSize);
		protected:
			bool					EnumDirectory(const char* pszDirPath, std::list<std::string> &vecDirList, bool bFlag = false);
		};
	}
}

#endif 
