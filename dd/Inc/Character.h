#ifndef __CHARACTER_H__
#define __CHARACTER_H__

// 
// 

using namespace std;
namespace Leaf
{
	namespace Character
	{
		class CConvert  
		{
		public:
			CConvert();
			virtual ~CConvert();
			
		public:
			//////////////////////////////////// 
			/*  
			A:      ANSI �ַ�����Ҳ���� MBCS
			W��OLE: ���ַ�����Ҳ���� UNICODE
			T:      �м�����T����������� _UNICODE����T��ʾW����������� _MBCS����T��ʾA
			C:      const ����д
			LPWSTR->LPTSTR:   W2T();
			LPTSTR->LPWSTR:   T2W();
			LPCWSTR->LPCSTR:  W2CA(); 
			LPCSTR->LPCWSTR:  A2CW();
			ANSI->UNICODE:    A2W();      LPCSTR->LPWSTR
			UNICODE->ANSI:    W2A();      LPCWSTR->LPSTR
			*/
			//////////////////////////////////// 
			/*
			CString  =  TCHAR
			CStringA =  char
			CStringW =  wchar_t
			
			CString-->LPCTSTR       LPCTSTR str1 = CString str2;
			CString-->LPTSTR        LPTSTR  str1 = (LPTSTR)(LPCTSTR)CString str2;
			CString-->char*         char pChar[100]; wcstombs(pChar,str,100);//wcstombs_s()��wcstombs()�İ�ȫ�汾
			CString-->LPCWSTR       LPCWSTR lpcwStr = strFileName.AllocSysString();//
			CString-->LPSTR         LPSTR lpStr = strFileName.GetBuffer();//LPSTR lpStr = (LPSTR)(LPCSTR)strFimeName;
			*/
			//////////////////////////////////// 
			static int  	UnicodeToANSI(char*    szDesc,  const wchar_t* szSrc);       	//wchar_t --> char
	        static int   	ANSIToUnicode(wchar_t* szDesc,  const char*    szSrc);        	//char    --> wchar_t 
			
			static int		UTF8ToUnicode(wchar_t* szDesc,  const char*    szSrc);			//UTF-8	  --> UCS2	
			static int		UnicodeToUTF8(char*    szDesc,  const wchar_t* szSrc);			//UCS2	  --> UTF-8
			

			static int		UTF8ToANSI(char* szDesc, const char* szSrc);
			static int		ANSIToUTF8(char* szDesc, const char* szSrc);
			////////////////////////////////////
			static int		StringToHexString(char* szDesc, const char* szSrc, int nLen, char chTag=0);
			static int      HexStringToBytes(unsigned char*	 szDesc, const char* szSrc,int nLen);			
			static int		BytesHexToString(char*  szDesc, const unsigned char* szSrc,int nLen);	

			//reverse 
		
		};
	}
}
#endif



// #ifdef __cplusplus
// extern "C"{
// #endif
// 
// 
// #ifdef __cplusplus
// }
// #endif