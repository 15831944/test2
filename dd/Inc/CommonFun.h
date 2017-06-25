// CommonFun.h: interface for the CCommonFun class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMONFUN_H__D8101BA0_F92E_41B6_BC95_1D1104487222__INCLUDED_)
#define AFX_COMMONFUN_H__D8101BA0_F92E_41B6_BC95_1D1104487222__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCommonFun  
{
public:
	CCommonFun();
	virtual ~CCommonFun();

public:
	bool		GetOSVersion();
	LONGLONG	GetUSTickCount();
	
	BOOL		IsAdmin(void); 
	int			RunAdmin(void);

	/*
	**	time_tתSYSTEMTIME
	*/
	SYSTEMTIME	TimetToSystemTime(time_t t);

	/*
	**	SYSTEMTIMEתtime_t
	*/
	time_t SystemTimeToTimet(SYSTEMTIME st);

	/*
	**	time_tתSYSTEMTIME
	*/
	SYSTEMTIME Time_tToSystemTime(time_t t);

	/*
	**	SYSTEMTIMEתtime_t
	*/
	time_t SystemTimeToTime_t( const SYSTEMTIME& st );
};

#endif // !defined(AFX_COMMONFUN_H__D8101BA0_F92E_41B6_BC95_1D1104487222__INCLUDED_)
