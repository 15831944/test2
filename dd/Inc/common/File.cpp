// File.cpp: implementation of the File class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "File.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

using namespace Leaf::IO;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

File::File()
{

}

File::~File()
{

}
/*
CString File::GetTitle(const CString& strName)
{
	int s = strName.ReverseFind('\\') + 1;
	int e = strName.ReverseFind('.');
	
	return strName.Mid(s,e - s);
}

CString File::GetName(const CString& strName)
{
	int i = strName.ReverseFind('\\') + 1;
	
	return strName.Mid(i);
}

CString File::GetExt(const CString& strName)
{
	int i = strName.ReverseFind('.') + 1;
	
	return strName.Mid(i);
}
*/