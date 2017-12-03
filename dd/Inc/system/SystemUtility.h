#ifndef __SYSTEMUTILITY_H__
#define __SYSTEMUTILITY_H__

using namespace std;
namespace Leaf
{
	namespace System
	{
		class CSystemUtility
		{
			public:
				CSystemUtility();
				~CSystemUtility();
			
			public:
				BOOL	EnableDebugPriv(LPCTSTR lpszPrivilegeName,BOOL bEnable);
		};
	}
}
#endif